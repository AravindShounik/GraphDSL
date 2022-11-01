#include <vector>
#include "types.h"

std::vector<std::string> doSemantics(const std::vector<common_list> &ast);
type_name doSemantics(const node &n);

struct Exception
{
  yy::location loc;
  std::string msg;
  Exception(yy::location _loc, std::string _msg) : loc(_loc), msg(_msg) {}
};