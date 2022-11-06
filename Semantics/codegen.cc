#include "codegen.hh"

static void InitializeModule()
{
  // Open a new context and module.
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("my cool jit", *TheContext);

  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
}

void doCodeGen(const std::vector<common_list> &ast)
{
  InitializeModule();

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
    return V;
  }

  case node_type::add:
  {
    Value *L = codegen(n.params[0]);
    Value *R = codegen(n.params[1]);

    if (!L || !R)
      return nullptr;
    return Builder->CreateFAdd(L, R, "addtmp");
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
    
  case node_type::comma:
    std::cout << "## comma type node\n";
    Value* v;
    for(auto& p : n.params)
      v = codegen(p);
    return v;

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
    NamedValues[std::string(Arg.getName())] = &Arg;

  if (Value *RetVal = codegen(f.code))
  {
    // Finish off the function.
    Builder->CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    verifyFunction(*F);
    return F;
  }

  // Error reading body, remove function.
  F->eraseFromParent();
  return nullptr;
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
