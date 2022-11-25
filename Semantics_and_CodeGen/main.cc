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
    return 0;
  }
  // else
  // {
    // ctx.dump_ast();
  // }

  std::vector<common_list> ast = std::move(ctx.storage);
  std::vector<std::string> errors = doSemantics(ast);
  if(errors.size()){
    return 0;
  }

  doCodeGen(ast);
  return 0;
}
