#include "context.hh"
#define stringify(name) #name

std::string Type_Names[] =
    {
        "INT",
        "BOOL",
        "FLOAT",
        "CHAR",
        "VOID",
        "STRING",
        "GRAPH",
        "DGRAPH",
        "NODE_SET",
        "NODE_PROP",
        "NODE_SEQ",
        "EDGE_SET",
        "EDGE_PROP",
        "EDGE_SEQ",
        "FUNC"};

std::string ID_Types[] =
    {
        "FUNCTION",
        "PARAMETER",
        "VARIABLE"};

const identifier &context::define(const std::string &name, identifier &&f)
{
  auto r = scopes.back().emplace(name, std::move(f));
  if (!r.second)
    error_list.emplace_back(loc, "Duplicate definition <" + name + ">");
  return r.first->second;
}

node context::def(const std::string &name)
{
  return define(name, identifier{id_type::variable, temptype, fun.num_vars++, name});
}

node context::defun(const std::string &name)
{
  return define(name, identifier{id_type::function, type_name::FUNC, func_list.size(), name});
}

node context::defparam(const std::string &name, type_name type)
{
  fun.param_types.push_back(type);
  return define(name, identifier{id_type::parameter, type, fun.num_params++, name});
}

node context::temp()
{

  return def("$I" + std::to_string(tempcounter++));
}

node context::use(const std::string &name)
{
  for (auto j = scopes.crbegin(); j != scopes.crend(); ++j)
  {
    auto i = j->find(name);
    if (i != j->end())
      return i->second;
  }
  error_list.emplace_back(loc, "Undefined identifier <" + name + ">");
  return {};
}

void context::add_function(std::string &&name, node &&code, type_name ret)
{
  fun.code = std::move(code);
  fun.name = std::move(name);
  fun.ret_type = ret;
  //   std::cout << "Return Type      : " << Type_Names[context::convert_types_int(fun.ret_type)] << std::endl;
  // std::cout << context::convert_types_int(ret) << "\n";
  func_list.push_back(std::move(fun));
  fun = {};
}

void context::operator++() { scopes.emplace_back(); } // Enter scope
void context::operator--() { scopes.pop_back(); }     // Exit scope

void context::printFuncList()
{
  int i = 1;
  auto o = [&](type_name t)
  { return t == type_name::INT; };
  for (auto &f : func_list)
  {
    std::cout << "Function Number: " << i++ << "\n";
    std::cout << "Function Name: " << f.name << "\n";
    std::cout << "Return Type: " << (o(f.ret_type) ? "INT" : "OTHER") << "\n";

    std::cout << "No. of params: " << f.num_params << "\n";

    int j = 1;
    for (auto &t : f.param_types)
    {
      std::cout << "Param-" << j++ << " Type: " << (o(t) ? "INT" : "OTHER") << "\n";
    }
    std::cout << "No. of local variables: " << f.num_vars << "\n";
    std::cout << "\n";
  }
}

int context::convert_types_int(type_name T)
{
  if (T == type_name::INT)
  {
    return 0;
  }

  if (T == type_name::BOOL)
  {
    return 1;
  }

  if (T == type_name::FLOAT)
  {
    return 2;
  }

  if (T == type_name::CHAR)
  {
    return 3;
  }

  if (T == type_name::VOID)
  {
    return 4;
  }

  if (T == type_name::STRING)
  {
    return 5;
  }

  if (T == type_name::GRAPH)
  {
    return 6;
  }

  return 8;
}

int context::convert_id_types_int(id_type T)
{
  if (T == id_type::function)
  {
    return 0;
  }

  if (T == id_type::parameter)
  {
    return 1;
  }

  if (T == id_type::variable)
  {
    return 2;
  }

  return 3;
}

void context::func1(function F)
{
  std::cout << "Function Name    : " << F.name << std::endl;
  std::cout << "Return Type      : " << Type_Names[context::convert_types_int(F.ret_type)] << std::endl;
  std::cout << "No of Paramaters : " << F.num_params << std::endl;
  std::cout << "No of Variables  : " << F.num_vars << std::endl;

  if (F.num_params > 0)
  {
    unsigned index_parameters = 0;
    std::cout << "\nParameter types   :\n";
    while (index_parameters < F.num_params)
    {
      std::cout << "  " << Type_Names[context::convert_types_int(F.param_types[index_parameters++])] << std::endl;
    }
  }

  node code = F.code;
  std::cout << "\nCode dump:\n";
  context::func2(code, 0);
}

void context::func3(node N, int level)
{
  int index_params = 0;
  while (index_params < N.params.size())
  {
    func2(N.params[index_params++], level);
  }
}

void context::func2(node N, int level)
{
  printf("%*s", 2 * level, "");

  switch (int(N.type))
  {

  case 0:
    std::cout << "(" << ID_Types[context::convert_id_types_int(N.ident.type)] << "," << Type_Names[context::convert_types_int(N.ident.v_type)] << ")" << N.ident.name << std::endl;
    break;

  case 1:
    std::cout << "(string)" << N.strvalue << std::endl;
    break;

  case 2:
    std::cout << "(int)" << N.numvalue << std::endl;
    break;

  case 3:
    std::cout << "(double)" << N.doublevalue << std::endl;
    break;

  case 4:
    std::cout << "+" << std::endl;
    level++;
    break;

  case 5:
    std::cout << "neg" << std::endl;
    level++;
    break;

  case 6:
    std::cout << "==" << std::endl;
    level++;
    break;

  case 7:
    std::cout << "(or)" << std::endl;
    level++;
    break;

  case 8:
    std::cout << "(and)" << std::endl;
    level++;
    break;

  case 9:
    // Need to be written
    break;

  case 10:
    std::cout << " (address) " << std::endl;
    break;

  case 11:
    std::cout << "(de-referencing) " << std::endl;
    break;

  case 12:
    // Need to be Done
    break;

  case 13:
    std::cout << "=" << std::endl;
    level++;
    break;

  case 14:
    // std::cout << "," << std::endl;
    break;

  case 15:
    std::cout << ("List") << std::endl;
    break;

  case 16:
    std::cout << "*" << std::endl;
    level++;
    break;

  case 17:
    std::cout << "/" << std::endl;
    level++;
    break;

  case 18:
    std::cout << "%" << std::endl;
    level++;
    break;

  case 19:
    std::cout << "return" << std::endl;
    break;

  case 20:
    std::cout << "break" << std::endl;
    break;

  case 21:
    std::cout << "continue" << std::endl;
    break;

  case 22:
    break;
  
  case 23:
    std::cout << "edge" << std::endl;
    level++;
    break;

  default:
    break;
  }

  context::func3(N, level);
}

void context::dump_ast()
{
  // printf("%*s", 2 * level, ""); /* indent to this level */
  // level++;

  std::cout << "--------------------------------------------------\n";
  for (auto &f : func_list)
  {
    context::func1(f);
    std::cout << "--------------------------------------------------\n";
  }
}