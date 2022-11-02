#include <iostream>
#include "context.hh"
#include "semantics.hh"
#include "location.hh"
#include "types.h"
#include "codegen.hh"

static lexcontext ctx;

extern yy::location getLoc()
{
  return ctx.loc;
}

int main()
{
  yy::parser parser(ctx);
  parser.parse();

  if (ctx.error_list.size())
  {
    for (auto &v : ctx.error_list)
      ctx.error(v.first, v.second);
  }
  else
  {
    // ctx.dump_ast();
  }

  std::vector<common_list> ast = std::move(ctx.storage);

  doSemantics(ast);

  doCodeGen(ast);
  return 0;
}
