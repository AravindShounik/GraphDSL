/* -*- c++ -*- */
%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>

#include "driver.hh"
#include "parser.hh"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;

// CHANGE: "Code run each time a pattern is matched" moved from its
// own block below (this change was not strictly necessary).
#define YY_USER_ACTION  loc.columns (yyleng);

// CHANGE: We must exclude unistd.h or the compiler will choke on the
// `isatty()` declaration emitted by `flex` having a different
// exception specifier from the one in `unistd.h`:
#define YY_NO_UNISTD_H

%}

/* Options: */
%option noyywrap nounput batch debug noinput

/* Regex abbreviations: */
id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t]
EXP	([Ee][-+]?[0-9]+)

%%

%{
    // Code run each time yylex is called.
    loc.step ();
%}

{blank}+   loc.step ();
[\n]+      loc.lines (yyleng); loc.step ();

"-"      return yy::parser::make_MINUS(loc);
"+"      return yy::parser::make_PLUS(loc);
"*"      return yy::parser::make_STAR(loc);
"/"      return yy::parser::make_SLASH(loc);
"("      return yy::parser::make_LPAREN(loc);
")"      return yy::parser::make_RPAREN(loc);
"="     return yy::parser::make_ASSIGN(loc);
"%"     return yy::parser::make_MOD(loc);
"|"     return yy::parser::make_B_OR(loc);
","     return yy::parser::make_COMMA(loc);
";"     return yy::parser::make_SEMI_COLON(loc);
":"     return yy::parser::make_COLON(loc);
"{"     return yy::parser::make_LBRACE(loc);
"}"     return yy::parser::make_RBRACE(loc);
"["     return yy::parser::make_LSB(loc);
"]"     return yy::parser::make_RSB(loc);


"&&" {return yy::parser::make_AND(loc); }
"||" {return yy::parser::make_OR(loc);}
"++" {return yy::parser::make_PP(loc);}
"--" {return yy::parser::make_MM(loc);}

 /* Assignment Ops */
"+="    {return yy::parser::make_PL_EQ(loc); }
"-="    {return yy::parser::make_MI_EQ(loc);}
"*="    {return yy::parser::make_MU_EQ(loc);}
"/="    {return yy::parser::make_DI_EQ(loc);}

 /* comparison ops */
">"     { return yy::parser::make_LESS(loc); }
"<"     { return yy::parser::make_GREATER(loc); }
"!="    { return yy::parser::make_NE(loc); }
"=="    { return yy::parser::make_EQ(loc); }
">="    { return yy::parser::make_GEQ(loc); }
"<="    { return yy::parser::make_LEQ(loc); }


"continue"     {return yy::parser::make_CONTINUE(loc);}
"BREAK"     {return yy::parser::make_BREAK(loc);}
"RETURN"     {return yy::parser::make_RETURN(loc);}


 /* type specifiers */
"void"     {return yy::parser::make_VOID(loc);}
"int"      {return yy::parser::make_INT(loc);}
"float"    {return yy::parser::make_FLOAT(loc);}
"char"    {return yy::parser::make_CHAR(loc);}
"string"    {return yy::parser::make_STRING(loc);}
"graph"    {return yy::parser::make_GRAPH(loc);}
"dgraph"    {return yy::parser::make_DGRAPH(loc);}
"node"    {return yy::parser::make_NODE(loc);}
"node_set"    {return yy::parser::make_NODE_SET(loc);}
"node_seq"    {return yy::parser::make_NODE_SEQ(loc);}
"node_prop"    {return yy::parser::make_NODE_PROP(loc);}
"edge_prop"    {return yy::parser::make_EDGE_PROP(loc);}
"edge_set"    {return yy::parser::make_EDGE_SET(loc);}
"edge_seq"    {return yy::parser::make_EDGE_SEQ(loc);}


 /* keywords */
"if"        { return yy::parser::make_IF(loc); }
"else"      { return yy::parser::make_ELSE(loc); }
"while"     { return yy::parser::make_WHILE(loc); }
"for"       { return yy::parser::make_FOR(loc);}
"BFS"       {return yy::parser::make_BFS(loc);}
"DFS"       {return yy::parser::make_DFS(loc);}
"nodes"     {return yy::parser::make_NODES(loc);}
"levels"    {return yy::parser::make_LEVELS(loc);}
"neighbours" {return yy::parser::make_NEIGHBOURS(loc);}


{int}      {
    errno = 0;
    long n = strtol (yytext, NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
        driver.error (loc, "integer is out of range");
    return yy::parser::make_NUMBER(n, loc);
}

[0-9]+"."[0-9]*{EXP}? |
"."[0-9]+{EXP}? { return yy::parser::make_DOUBLE(atof(yytext), loc); }

 /* strings */
\"(\\.|[^\\"])*\" {return yy::parser::make_STRING_LITERAL(yytext, loc);}

{id}       return yy::parser::make_IDENTIFIER(yytext, loc);

.          driver.error (loc, "invalid character");

<<EOF>>    return yy::parser::make_END(loc);
%%

// CHANGE: The "parts of the driver that need lexer data" have been
// moved to calc++-driver.cc (where they really belong) and access the
// new lexer object via its public interface.

// CHANGE: The linker will choke if there's no implementation of the
// default `yylex` even if it's never called.
int yyFlexLexer::yylex() {
    std::cerr << "'int yyFlexLexer::yylex()' should never be called." << std::endl;
    exit(1);
}
