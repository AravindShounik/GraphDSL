#include <vector>
#include <string>

#include <map>
#include "parser.hh"

struct context
{
  yy::location loc;
  std::vector<std::map<std::string, identifier>> scopes;
  std::vector<function> func_list;
  unsigned tempcounter = 0;
  function fun;
  std::vector<std::pair<yy::location, std::string>> error_list;

public:
  const identifier &define(const std::string &name, identifier &&f);
  node def(const std::string &name, type_name type);
  node defun(const std::string &name);
  node defparam(const std::string &name, type_name type);
  node temp();
  node use(const std::string &name);
  void add_function(std::string &&name, node &&code, type_name ret);
  void operator++(); // Enter scope
  void operator--(); // Exit scope
};