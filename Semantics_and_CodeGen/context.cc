#include "context.hh"

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
  fun.param_names.push_back(name);
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
  return identifier(id_type::function, type_name::FUNC, 0, name);
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

void lexcontext::func1(function F)
{
  std::cout << "Function Name    : " << F.name << std::endl;
  std::cout << "Return Type      : " << toString(F.ret_type) << std::endl;
  std::cout << "No of Paramaters : " << F.num_params << std::endl;
  std::cout << "No of Variables  : " << F.num_vars << std::endl;

  if (F.num_params > 0)
  {
    unsigned index_parameters = 0;
    std::cout << "\nParameter types   :\n";
    while (index_parameters < F.num_params)
    {
      std::cout << "  " << toString(F.param_types[index_parameters]) << ": " << F.param_names[index_parameters] << std::endl;
      index_parameters++;
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

  switch (N.type)
  {

  case node_type::identifier:
    std::cout << "(" << toString(N.ident.type) << "," << toString(N.ident.v_type) << ")" << N.ident.name << std::endl;
    break;

  case node_type::string:
    std::cout << "(string)" << N.strvalue << std::endl;
    break;

  case node_type::number:
    std::cout << "(int)" << N.numvalue << std::endl;
    break;

  case node_type::double_const:
    std::cout << "(double)" << N.doublevalue << std::endl;
    break;

  case node_type::add:
    std::cout << "+" << std::endl;
    level++;
    break;

  case node_type::neg:
    std::cout << "neg" << std::endl;
    level++;
    break;

  case node_type::eq:
    std::cout << "==" << std::endl;
    level++;
    break;

  case node_type::cor:
    std::cout << "(or)" << std::endl;
    level++;
    break;

  case node_type::cand:
    std::cout << "(and)" << std::endl;
    level++;
    break;

  case node_type::cond:
    // Need to be written
    break;

  case node_type::addrof:
    std::cout << " (address) " << std::endl;
    break;

  case node_type::deref:
    std::cout << "(de-referencing) " << std::endl;
    break;

  case node_type::fcall:
    // Need to be Done
    break;

  case node_type::copy:
    std::cout << "=" << std::endl;
    level++;
    break;

  case node_type::comma:
    std::cout << "," << std::endl;
    break;

  case node_type::init_list:
    std::cout << ("List") << std::endl;
    break;

  case node_type::mul:
    std::cout << "*" << std::endl;
    level++;
    break;

  case node_type::div:
    std::cout << "/" << std::endl;
    level++;
    break;

  case node_type::mod:
    std::cout << "%" << std::endl;
    level++;
    break;

  case node_type::ret:
    std::cout << "return" << std::endl;
    break;

  case node_type::br:
    std::cout << "break" << std::endl;
    break;

  case node_type::cont:
    std::cout << "continue" << std::endl;
    break;

  case node_type::nop:
    break;

  case node_type::edge:
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
  std::cout << "All declarations:\n";

  for (auto &decl : storage)
  {
    if (decl.isFunc)
      func1(decl.f);
    else
      func2(decl.n, 0);
    std::cout << "\n";
  }
}

void lexcontext::error(const yy::location &l, const std::string &m)
{
  std::cerr << l.begin.line << ":" << l.begin.column << " error: " << m << std::endl;
}

void lexcontext::error(const std::string &m)
{
  std::cerr << m << std::endl;
}