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

const identifier &lexcontext::define(const std::string &name, identifier &&f)
{
  auto r = scopes.back().emplace(name, std::move(f));
  if (!r.second)
    error_list.emplace_back(loc, "Duplicate definition <" + name + ">");
  return r.first->second;
}

node lexcontext::def(const std::string &name)
{
  return define(name, identifier{id_type::variable, temptype, fun.num_vars++, name});
}

node lexcontext::defun(const std::string &name)
{
  return define(name, identifier{id_type::function, type_name::FUNC, temporary++, name});
}

node lexcontext::defparam(const std::string &name, type_name type)
{
  fun.param_types.push_back(type);
  return define(name, identifier{id_type::parameter, type, fun.num_params++, name});
}

node lexcontext::temp()
{

  return def("$I" + std::to_string(tempcounter++));
}

node lexcontext::use(const std::string &name)
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

void lexcontext::add_function(std::string &&name, node &&code, type_name ret)
{
  fun.code = std::move(code);
  fun.name = std::move(name);
  fun.ret_type = ret;
  //   std::cout << "Return Type      : " << Type_Names[lexcontext::convert_types_int(fun.ret_type)] << std::endl;
  // std::cout << lexcontext::convert_types_int(ret) << "\n";
  storage.push_back(std::move(fun));
  fun = {};
}

void lexcontext::add_decl(node &&decl)
{
  storage.push_back(std::move(decl));
  storage.back().isFunc = false;
}

void lexcontext::operator++() { scopes.emplace_back(); } // Enter scope
void lexcontext::operator--() { scopes.pop_back(); }     // Exit scope


int lexcontext::convert_types_int(type_name T)
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

int lexcontext::convert_id_types_int(id_type T)
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

void lexcontext::func1(function F)
{
  std::cout << "Function Name    : " << F.name << std::endl;
  std::cout << "Return Type      : " << Type_Names[lexcontext::convert_types_int(F.ret_type)] << std::endl;
  std::cout << "No of Paramaters : " << F.num_params << std::endl;
  std::cout << "No of Variables  : " << F.num_vars << std::endl;

  if (F.num_params > 0)
  {
    unsigned index_parameters = 0;
    std::cout << "\nParameter types   :\n";
    while (index_parameters < F.num_params)
    {
      std::cout << "  " << Type_Names[lexcontext::convert_types_int(F.param_types[index_parameters++])] << std::endl;
    }
  }

  node code = F.code;
  lexcontext::func2(code, 0);
}

void lexcontext::func3(node N, int level)
{
  int index_params = 0;
  while (index_params < (int)N.params.size())
  {
    func2(N.params[index_params++], level);
  }
}

void lexcontext::func2(node N, int level)
{
  printf("%*s", 2 * level, "");

  switch (int(N.type))
  {

  case 0:
    std::cout << "(" << ID_Types[lexcontext::convert_id_types_int(N.ident.type)] << "," << Type_Names[lexcontext::convert_types_int(N.ident.v_type)] << ")" << N.ident.name << std::endl;
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

  lexcontext::func3(N, level);
}

void lexcontext::dump_ast()
{
  // printf("%*s", 2 * level, ""); /* indent to this level */
  // level++;
  // std::cout << "--------------------------------------------------\n";
  // std::cout << "Global declarations:\n";
  // std::cout << "--------------------------------------------------\n";
  // for(auto& n: global_var_list)
  // {
  //   func2(n, 0);
  // }
  // std::cout << "\n\n";
  // std::cout << "--------------------------------------------------\n";
  // std::cout << "Function Declarations\n";
  // std::cout << "--------------------------------------------------\n";
  // for (auto &f : func_list)
  // {
  //   lexcontext::func1(f);
  //   std::cout << "--------------------------------------------------\n";
  // }

  std::cout << "All declarations:\n";

  for(auto& decl : storage)
  {
    if(decl.isFunc)
      func1(decl.f);
    else
      func2(decl.n, 0);
    std::cout << "\n";
  }
}

void lexcontext::error (const yy::location& l, const std::string& m)
{
    std::cerr << l.begin.line <<":" << l.begin.column << " error: " << m << std::endl;
}

void lexcontext::error (const std::string& m)
{
    std::cerr << m << std::endl;
}