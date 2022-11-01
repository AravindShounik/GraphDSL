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
  Function *ir = codegen(f);
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

  default:
    break;
  }
  return nullptr;
}

Function *codegen(const function &f)
{
  return nullptr;
}
