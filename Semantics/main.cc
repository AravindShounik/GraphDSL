#include <iostream>
#include "context.hh"

int main()
{
  lexcontext ctx;
  yy::parser parser(ctx);
  parser.parse();

  if (ctx.error_list.size())
  {
    for (auto &v : ctx.error_list)
      ctx.error(v.first, v.second);
  }
  else
    ctx.dump_ast();
  return 0;
}
