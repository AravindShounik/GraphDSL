#include <vector>
#include <string>
#include "types.h"

#include <map>
#include "parser.hh"

struct context
{
  yy::location loc;
  std::vector<std::map<std::string, identifier>> scopes;
  std::vector<function> func_list;
  std::vector<node> global_var_list;
  unsigned tempcounter = 0;
  function fun;
  type_name temptype = type_name::INT;
  std::vector<std::pair<yy::location, std::string>> error_list;

public:
  const identifier &define(const std::string &name, identifier &&f);
  node def(const std::string &name);
  node defun(const std::string &name);
  node defparam(const std::string &name, type_name type);
  node temp();
  node use(const std::string &name);
  void add_function(std::string &&name, node &&code, type_name ret);
  void operator++(); // Enter scope
  void operator--(); // Exit scope

  void printFuncList();
  int convert_types_int(type_name T);
  int convert_id_types_int(id_type T);
  void dump_ast();
  void func1(function F);
  void func2(node N,int level);
  void func3(node N,int level);
};