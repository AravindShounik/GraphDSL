#include "codegen.hh"

static void InitializeModuleAndPassManager(void)
{
  // Open a new module.
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("gralgo", *TheContext);
  // TheModule->setDataLayout(T)

  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);

  // Create a new pass manager attached to it.
  TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());

  // Promote allocas to registers.
  TheFPM->add(createPromoteMemoryToRegisterPass());

  // Do simple peephole optimizations and bit-twiddling optimizations.
  TheFPM->add(createInstructionCombiningPass());
  
  // Eliminate Common SubExpressions.
  TheFPM->add(createGVNPass());

  // Simplify the control flow graph (deleting unreachable blocks, etc).
  TheFPM->add(createCFGSimplificationPass());

  TheFPM->doInitialization();
}

static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, Type *Ty, StringRef VarName)
{
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(Ty, nullptr, VarName);
}

void doCodeGen(const std::vector<common_list> &ast)
{
  InitializeModuleAndPassManager();

  for (auto &cn : ast)
  {
    if (cn.isFunc)
    {
      std::cout << "## codegen.cc line 21\n";
      HandleFunction(cn.f);
    }
    else
    {
      HandleNode(cn.n);
    }
  }
  TheModule->print(errs(), nullptr);
}

void HandleNode(const node &n)
{
  Value *ir = codegen(n);
}

void HandleFunction(const function &f)
{
  if (auto *FnIR = codegen(f))
  {
    fprintf(stderr, "Read function definition:\n");
    fprintf(stderr, "\n");
  }
  else
  {
    std::cout << "## Codegen flopped :/\n";
  }
}

/* Util functions for code generation */
Type *convertType(type_name Ty)
{
  switch (Ty)
  {
  case type_name::INT:
    return Type::getInt64Ty(*TheContext);

  case type_name::FLOAT:
    return Type::getDoubleTy(*TheContext);

  case type_name::BOOL:
    return Type::getInt1Ty(*TheContext);

  case type_name::VOID:
    return Type::getVoidTy(*TheContext);

  default:
    break;
  }
  return nullptr;
}


Function *codegen(const function &f)
{
  std::cout << "## Entered function codegen func. line 103\n";
  std::vector<Type *> param_types(f.param_types.size(), nullptr);
  for (auto i = 0; i < f.param_types.size(); i++)
    param_types[i] = convertType(f.param_types[i]);

  FunctionType *FT = FunctionType::get(convertType(f.ret_type), param_types, false);

  Function *F = Function::Create(FT, Function::ExternalLinkage, f.name, TheModule.get());

  // Set names for all arguments
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(f.param_names[Idx++]);

  // Create a new basic block to start insertion into.
  BasicBlock *BB = BasicBlock::Create(*TheContext, "entry", F);
  Builder->SetInsertPoint(BB);

  // Record the function arguments in the NamedValues map.
  NamedValues.clear();
  for (auto &Arg : F->args())
  {
    // Create an alloca for this variable.
    AllocaInst *Alloca = CreateEntryBlockAlloca(F, Arg.getType(), Arg.getName());

    // Store the initial value into the alloca.
    Builder->CreateStore(&Arg, Alloca);

    // Add arguments to variable symbol table.
    NamedValues[std::string(Arg.getName())] = Alloca;
  }
  emit(f.code.params);
  // if (Value *RetVal = codegen(f.code))
  // {
  //   // Finish off the function.
  //   Builder->CreateRet(RetVal);

  //   // Validate the generated code, checking for consistency.
  //   verifyFunction(*F);

  //   // Run the optimizer on the function.
  //   TheFPM->run(*F);
  //   return F;
  // }

  // // Error reading body, remove function.
  // F->eraseFromParent();
  // return nullptr;
  return F;
}


Value *codegen(const node &n)
{
  switch (n.type)
  {
  case node_type::number:
    return ConstantInt::get(*TheContext, APInt(32, n.numvalue, true));

  case node_type::double_const:
    return ConstantFP::get(*TheContext, APFloat(n.doublevalue));

  case node_type::string:

    break;

  case node_type::identifier:
  {
    Value *V = NamedValues[n.ident.name];
    if (!V)
      fprintf(stderr, "Error: Unknown variable name\n");

    // Load the value.
    return Builder->CreateLoad(convertType(n.ident.v_type), V, n.ident.name.c_str());
  }

  case node_type::add:
  {
    Value *L = codegen(n.params[0]);
    Value *R = codegen(n.params[1]);

    if (!L || !R)
      return nullptr;
    auto Inst = BinaryOperator::CreateAdd(L,R,"addtmp");
    auto block = Builder->GetInsertBlock();
    block->getInstList().push_back(Inst);
    return Inst;
  }

  case node_type::neg:
  {
    Value *L = codegen(0);
    Value *R = codegen(n.params[0]);

    if (!L || !R)
      return nullptr;
    return Builder->CreateFSub(L, R, "subtmp");
  }
  case node_type::ret:
    return codegen(n.params[0]);

  case node_type::vardec:
  {
    for(auto& var:n.params){
      Value* v=codegen(var.params[0]);
      auto alloca = Builder->CreateAlloca(convertType(var.params[1].ident.v_type));
      NamedValues[var.params[1].ident.name] = alloca;
      auto store = Builder->CreateStore(v,alloca);
    }
  }

  default:
    break;
  }
  return nullptr;
}

void emit(const node_vec &stmts){
  for(auto& stmt:stmts){
    codegen(stmt);
  }
}