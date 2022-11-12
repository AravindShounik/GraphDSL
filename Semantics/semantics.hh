#include <vector>
#include <map>
#include "types.h"

static std::map<std::string, function *> func_map;
std::vector<std::string> doSemantics(std::vector<common_list> &ast);
type_name doSemantics(const node &n);

struct Exception
{
  yy::location loc;
  std::string msg;
  Exception(yy::location _loc, std::string &&_msg) : loc(_loc), msg(std::move(_msg)) {}
  Exception(std::string &&_msg) : msg(std::move(_msg)) {}
};