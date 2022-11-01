#include <iostream>
#include "context.hh"
#include "semantics.hh"

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

  std::vector<common_list> ast = std::move(ctx.storage);
  
  // doSemantics(ast);
  return 0;
}
