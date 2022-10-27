#pragma once

#ifndef YY_DECL
#define YY_DECL                                                         \
    yy::parser::symbol_type GrFlexLexer::yylex(lexcontext& ctx)
#endif

// We need this for yyFlexLexer. If we don't #undef yyFlexLexer, the
// preprocessor chokes on the line `#define yyFlexLexer yyFlexLexer`
// in `FlexLexer.h`:
#undef yyFlexLexer
#include <FlexLexer.h>

// We need this for the yy::parser::symbol_type:
#include "parser.hh"

class GrFlexLexer : public yyFlexLexer {
public:
    // Use the superclass's constructor:
    using yyFlexLexer::yyFlexLexer;

    // Provide the interface to `yylex`; `flex` will emit the
    // definition into `context.cc`:
    yy::parser::symbol_type yylex(lexcontext& ctx);

};
