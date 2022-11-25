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

/* This Function does code generation for all the functions
 stored in "ast" */
void doCodeGen(const std::vector<common_list> &ast)
{
  InitializeModuleAndPassManager();

  AddBuiltInFuncs();

  for (auto &cn : ast)
  {
    if (cn.isFunc)
    {
      // std::cout << "## codegen.cc line 21\n";
      HandleFunction(cn.f);
    }
    else
    {
      HandleNode(cn.n);
    }
  }

  raw_ostream *out = &errs();
  std::error_code EC;
  out = new raw_fd_ostream("test.ll", EC);
  TheModule->print(*out, nullptr);
}

/* This function handles the code generation for nodes */
void HandleNode(const node &n)
{
  Value *ir = codegen(n);
}

/* This function handles the code generation for functions */
void HandleFunction(const function &f)
{
  codegen(f);
}

/* Util functions for code generation */
Type *convertType(type_name Ty)
{
  switch (Ty)
  {
  case type_name::INT:
    return Type::getInt32Ty(*TheContext);

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
  // std::cout << "## Entered function codegen func. line 103\n";
  std::vector<Type *> param_types(f.param_types.size(), nullptr);
  for (auto i = 0; i < f.param_types.size(); i++)
    param_types[i] = convertType(f.param_types[i]);

  FunctionType *FT = FunctionType::get(convertType(f.ret_type), param_types, false);
  funcList[f.name] = FT;

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
    auto Inst = BinaryOperator::CreateAdd(L, R, "addtmp");
    auto block = Builder->GetInsertBlock();
    block->getInstList().push_back(Inst);
    return Inst;
  }

  case node_type::mul:
  {
    Value *L = codegen(n.params[0]);
    Value *R = codegen(n.params[1]);

    if (!L || !R)
      return nullptr;
    auto Inst = BinaryOperator::CreateMul(L, R, "multmp");
    auto block = Builder->GetInsertBlock();
    block->getInstList().push_back(Inst);
    return Inst;
  }

  case node_type::div:
  {
    Value *L = codegen(n.params[0]);
    Value *R = codegen(n.params[1]);

    if (!L || !R)
      return nullptr;
    auto Inst = BinaryOperator::CreateSDiv(L, R, "multmp");
    auto block = Builder->GetInsertBlock();
    block->getInstList().push_back(Inst);
    return Inst;
  }

  case node_type::neg:
  {
    return Builder->CreateNeg(codegen(n.params[0]), "subtmp");
  }
  case node_type::ret:
  {
    Value *v = codegen(n.params[0]);
    return Builder->CreateRet(v);
  }

  case node_type::vardec:
  {
    for (auto &var : n.params)
    {

      if (var.params[0].ident.v_type == type_name::GRAPH)
      {
        /********preprocess**********/
        auto initlist = var.params[1].params;
        std::set<int> nodes;
        std::set<int> mm;
        for (auto &edge : initlist)
        {
          if (edge.type == node_type::edge)
          {
            auto v1 = edge.params[0].numvalue - 1, v2 = edge.params[1].numvalue - 1;
            // print(v1, v2);
            nodes.insert(v1);
            nodes.insert(v2);
          }
          else
            break;
        }
        int n_size = nodes.size();
        for (auto &edge : initlist)
        {
          if (edge.type == node_type::edge)
          {
            auto v1 = edge.params[0].numvalue - 1, v2 = edge.params[1].numvalue - 1;
            mm.insert(v1 * n_size + v2);
            mm.insert(v2 * n_size + v1);
          }
          else
            break;
        }
        print("n_size is :", n_size);

        /******************************/
        auto Ty = ArrayType::get(convertType(type_name::INT), n_size * n_size);

        auto v_name = var.params[0].ident.name;
        auto *arr = new GlobalVariable(*TheModule, Ty, false, GlobalValue::ExternalLinkage, 0, v_name);

        std::vector<llvm::Constant *> values;
        for (int i = 0; i < n_size * n_size; i++)
        {
          ConstantInt *c = ConstantInt::get(*TheContext, APInt(32, (mm.find(i) != mm.end() ? 1 : 0)));
          values.push_back(c);
        }

        llvm::Constant *init = llvm::ConstantArray::get(Ty, values);
        arr->setInitializer(init);

        graphList[v_name] = std::make_pair(arr, n_size);

        // std::vector<APInt *> indx = {ConstantInt::get(*TheContext, APInt(32, 0)), ConstantInt::get(*TheContext, APInt(32, 0))};
      }
      else
      {
        auto alloca = Builder->CreateAlloca(convertType(var.params[0].ident.v_type));

        NamedValues[var.params[0].ident.name] = alloca;

        if (var.params[0].type != node_type::nop)
        {
          Value *v = codegen(var.params[1]);
          auto store = Builder->CreateStore(v, alloca);
        }
      }
    }
    break;
  }

  case node_type::cond:
  {
    // return nullptr;
    Value *CondV = codegen(n.params[0]);
    if (!CondV)
      return nullptr;

    // Convert condition to a bool by comparing non-equal to 0
    CondV = Builder->CreateICmpNE(CondV, Builder->getInt32(0), "ifcond");

    Function *TheFunction = Builder->GetInsertBlock()->getParent();

    BasicBlock *ThenBB = BasicBlock::Create(*TheContext, "then", TheFunction);
    BasicBlock *ElseBB = BasicBlock::Create(*TheContext, "else", TheFunction);
    BasicBlock *MergeBB = BasicBlock::Create(*TheContext, "ifcont", TheFunction);

    Builder->CreateCondBr(CondV, ThenBB, ElseBB);

    Builder->SetInsertPoint(ThenBB);
    emit(n.params[1].params);
    Builder->CreateBr(MergeBB);

    Builder->SetInsertPoint(ElseBB);
    emit(n.params[2].params);
    Builder->CreateBr(MergeBB);

    Builder->SetInsertPoint(MergeBB);
    return CondV;
  }

  case node_type::loop:
  {
    Function *TheFunction = Builder->GetInsertBlock()->getParent();

    BasicBlock *LoopBB = BasicBlock::Create(*TheContext, "loop", TheFunction);
    BasicBlock *AfterBB = BasicBlock::Create(*TheContext, "afterloop", TheFunction);

    Builder->CreateBr(LoopBB);
    Builder->SetInsertPoint(LoopBB);
    emit(n.params[1].params);

    Value *CondV = codegen(n.params[0]);
    CondV = Builder->CreateICmpNE(CondV, Builder->getInt32(0), "ifcond");
    Builder->CreateCondBr(CondV, LoopBB, AfterBB);

    Builder->SetInsertPoint(AfterBB);

    return CondV;
  }
  case node_type::fcall:
  {
    auto &f = n.params[0];
    auto &params = n.params[1].params;

    auto &fname = f.ident.name;

    std::vector<Value *> Args;

    for (auto &p : params)
    {
      Args.push_back(codegen(p));
    }
    CallInst *CallFunc = CallInst::Create(TheModule->getOrInsertFunction(fname, funcList[fname]), Args, fname);
    Builder->GetInsertBlock()->getInstList().push_back(CallFunc);
    return CallFunc;
  }
  case node_type::comma:
  {
    // print(n.params.size());
    emit(n.params);
    break;
  }
  case node_type::asgn:
  {
    if (n.params[0].type == node_type::identifier)
    {
      Value *v = codegen(n.params[1]);
      Builder->CreateStore(v, NamedValues[n.params[0].ident.name]);
    }
    break;
  }
  case node_type::bfs:
  case node_type::dfs:
  {
    std::string fname = "main_" + toString(n.type);
    std::vector<Value *> Args;

    auto v_name = n.params[1].ident.name;
    auto g = graphList[v_name];

    int n_size = g.second;
    print(n_size);
    auto Ty = ArrayType::get(convertType(type_name::INT), n_size * n_size);

    auto arr = TheModule->getOrInsertGlobal(v_name, Ty);

    SmallVector<Value *, 2> idxs;

    // return nullptr;
    idxs.push_back(Builder->getInt32(0));
    idxs.push_back(Builder->getInt32(0));

    auto gepInst = Builder->CreateGEP(Ty, arr, idxs, "g_gep");

    Args.push_back(gepInst);
    Args.push_back(codegen(n_size));

    Args.push_back(codegen(1));

    auto ret_Ty = ArrayType::get(convertType(type_name::INT), n_size);

    auto *ret_arr = new GlobalVariable(*TheModule, ret_Ty, false, GlobalValue::CommonLinkage, 0);

    std::vector<llvm::Constant *> values(n_size, ConstantInt::get(*TheContext, APInt(32, 0)));

    llvm::Constant *init = llvm::ConstantArray::get(Ty, values);
    ret_arr->setInitializer(init);

    auto ret_gepInst = Builder->CreateGEP(ret_Ty, ret_arr, idxs, "ret_g_gep");
    Args.push_back(ret_gepInst);

    // CallInst::Create(TheModule->getOrInsertFunction(fname, funcList[fname]), Args);

    Builder->CreateCall(TheModule->getOrInsertFunction(fname, funcList[fname]), Args);
  }

  default:
    break;
  }
  return nullptr;
}

void emit(const node_vec &stmts)
{
  for (auto &stmt : stmts)
  {
    print(stmt.type, stmt.params.size());
    codegen(stmt);
  }
}

Type *createGraph()
{
  StringRef Name = "graph";
  std::vector<Type *> v = {convertType(type_name::INT), convertType(type_name::INT)};
  return StructType::create(*TheContext, v, Name);
}

/* This Function adds built in functions 
  so that user can use them.
*/
void AddBuiltInFuncs()
{
  unsigned n_args;
  std::string fname;
  std::vector<Type *> param_types;
  FunctionType *FT;
  Function *F;

  /*foo func*/
  n_args = 2;
  fname = "foo";
  param_types.clear();
  param_types.push_back(convertType(type_name::INT));
  param_types.push_back(convertType(type_name::INT));

  FT = FunctionType::get(convertType(type_name::INT), param_types, false);
  funcList[fname] = FT;
  F = Function::Create(FT, Function::ExternalLinkage, fname, TheModule.get());

  /*BFS func*/
  n_args = 4;
  fname = "main_bfs";
  param_types.clear();

  auto int_ptr = PointerType::getInt32PtrTy(*TheContext);

  param_types.push_back(int_ptr);
  param_types.push_back(convertType(type_name::INT));
  param_types.push_back(convertType(type_name::INT));
  param_types.push_back(int_ptr);

  FT = FunctionType::get(convertType(type_name::VOID), param_types, false);
  funcList[fname] = FT;
  F = Function::Create(FT, Function::ExternalLinkage, fname, TheModule.get());

  /*DFS func*/
  n_args = 4;
  fname = "main_dfs";
  funcList[fname] = FT;
  F = Function::Create(FT, Function::ExternalLinkage, fname, TheModule.get());
}
