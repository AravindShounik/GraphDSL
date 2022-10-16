/* -*- c++ -*- */
%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>

#include "calc++-driver.hh"
#include "calc++-parser.hh"

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

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
"%" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
":" |
"{" |
"}" |
"[" |
"]" |
"(" |
")"     { return yytext[0]; }

"&&" {return yy::gralgo::make_AND(loc); }
"||" {return yy::gralgo::make_OR(loc);}
"++" {return yy::gralgo::make_PP(loc);}
"--" {return yy::gralgo::make_MM(loc);}

 /* Assignment Ops */
"+="    {return yy::gralgo::make_PL_EQ(loc); }
"-="    {return yy::gralgo::make_MI_EQ(loc);}
"*="    {return yy::gralgo::make_MU_EQ(loc);}
"/="    {return yy::gralgo::make_DI_EQ(loc);}

 /* comparison ops */
">"     { return yytext[0]; }
"<"     { return yytext[0]; }
"!="    { return yy::gralgo::make_NE(loc); }
"=="    { return yy::gralgo::make_EQ(loc); }
">="    { return yy::gralgo::make_GEQ(loc); }
"<="    { return yy::gralgo::make_LEQ(loc); }

 /* type specifiers */
 "void"     {return yy::gralgo::make_VOID(loc);}
 "int"      {return yy::gralgo::make_INT(loc);}
 "float"    {return yy::gralgo::make_FLOAT(loc);}
 "char"    {return yy::gralgo::make_CHAR(loc);}
 "string"    {return yy::gralgo::make_STRING(loc);}
 "graph"    {return yy::gralgo::make_GRAPH(loc);}
 "dgraph"    {return yy::gralgo::make_DGRAPH(loc);}
 "node"    {return yy::gralgo::make_NODE(loc);}
 "node_set"    {return yy::gralgo::make_NODE_SET(loc);}
 "node_seq"    {return yy::gralgo::make_NODE_SEQ(loc);}
 "node_prop"    {return yy::gralgo::make_NODE_PROP(loc);}
 "edge_prop"    {return yy::gralgo::make_EDGE_PROP(loc);}
 "edge_set"    {return yy::gralgo::make_EDGE_SET(loc);}
 "edge_seq"    {return yy::gralgo::make_EDGE_SEQ(loc);}


 /* keywords */
"if"        { return yy::gralgo::make_IF(loc); }
"else"      { return yy::gralgo::make_ELSE(loc); }
"while"     { return yy::gralgo::make_WHILE(loc); }
"for"       { return yy::gralgo::make_FOR(loc);}
"BFS"       {return yy::gralgo::make_BFS(loc);}
"DFS"       {return yy::gralgo::make_DFS(loc);}
"Nodes"     {return yy::gralgo::make_NODES(loc);}
"Levels"    {return yy::gralgo::make_LEVELS(loc);}
"Neighbours" {return yy::gralgo::make_NEIGHBOURS(loc);}



 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }

 /* names */
[a-zA-Z_][a-zA-Z0-9_]*  { return yy::gralgo::make_IDENTIFIER(yytext, loc); }

 /* int */
[0-9][0-9]*     { return yy::gralgo::make_INT(atoi(yytext), loc); }
 /* double */
[0-9]+"."[0-9]*{EXP}? |
"."[0-9]+{EXP}? { return yy::gralgo::make_DOUBLE(atof(yytext), loc); }

 /* strings */
\"(\\.|[^\\"])*\" {return yy::gralgo::make_STRING_LITERAL(yytext, loc);}

"//".*  {}
[ \n\t]   /* ignore white space */ 
\\\n    printf("c> "); /* ignore line continuation */
"/*"([^*]|\*+[^*/])*\**"*/" {}
.	{ yyerror("Mystery character %c\n", *yytext); }
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
