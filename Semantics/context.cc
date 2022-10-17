#include "context.hh"

const identifier &context::define(const std::string &name, identifier &&f)
{
  auto r = scopes.back().emplace(name, std::move(f));
  if (!r.second)
    error_list.emplace_back(loc, "Duplicate definition <" + name + ">");
  return r.first->second;
}
node context::def(const std::string &name, type_name type) { return define(name, identifier{id_type::variable, type, fun.num_vars++, name}); }
node context::defun(const std::string &name) { return define(name, identifier{id_type::function, type_name::FUNC, func_list.size(), name}); }
node context::defparam(const std::string &name, type_name type) { return define(name, identifier{id_type::parameter, type, fun.num_params++, name}); }
node context::temp() { return def("$I" + std::to_string(tempcounter++), type_name::INT); }
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
  fun.code = n_comma(std::move(code), n_ret(0)); // Add implicit "return 0;" at the end
  fun.name = std::move(name);
  fun.ret_type = ret;
  func_list.push_back(std::move(fun));
  fun = {};
}
void context::operator++() { scopes.emplace_back(); } // Enter scope
void context::operator--() { scopes.pop_back(); }     // Exit scope