%skeleton "lalr1.cc" /* -*- c++ -*- */
%require "3.2"
%defines
%define api.parser.class {gralgo}

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <map>
#include <list>
#include <regex>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
class calcxx_driver;
}

// The parsing context.
%param { calcxx_driver& driver }

// Location tracking
%locations
%initial-action
{
    // Initialize the initial location.
    @$.begin.filename = @$.end.filename = &driver.file;
};

// Enable tracing and verbose errors (which may be wrong!)
%define parse.trace
%define parse.error verbose

// Parser needs to know about the driver:
%code
{
#include "calc++-driver.hh"
#define yylex driver.lexer.yylex
}

// Tokens:
%define api.token.prefix {TOK_}
%token             END 0
%token             FOR "for" WHILE "while" IF "if" ELSE "else" INT "int" FLOAT "float" STRING "string" GRAPH "graph" NODEPROP "nodeprop" NODESET "nodeset" EDGEPROP "edgeprop" EDGESET "edgeset" BFS "bfs" DFS "dfs"
%token             OR "||"  AND "&&"  EQ "=="  NE "!="  PP "++"  MM "--"  PL_EQ "+="  MI_EQ "-="
%token             CONTINUE "continue" BREAK "break" RETURN "return" 
%left  ','
%right '?' ':' '=' "+=" "-="
%left  "||"
%left  "&&"
%left  "==" "!="
%left  '+' '-'
%left  '*'
%right '&' "++" "--"
%left  '(' '['
%token<long>        NUMCONST
%token<std::string> IDENTIFIER STRINGCONST
%type<std::string> identifier

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

program: declarations;
declarations: declarations declaration
|             %empty
;
declaration: vardec_stmt
|            function
;
stmt: compound_stmt '}'
|     selection_stmt
|     jump_stmt
|     expression_stmt
|     empty_stmt
|     vardec_stmt
|     iteration_stmt
;
expression_stmt: exprs ';'
;
jump_stmt: CONTINUE ';'
|          BREAK ';'
|          RETURN ';'
|          RETURN expr ';'
;
empty_stmt: ';'
;
vardec_stmt: typename vardec1
|            vardec_stmt ',' vardec1
;
vardec1: identifier '=' initializer
|        identifier
;
initializer: expr
|            edge
|            '{' initializer_list '}'
;
initializer_list: initializer
|                 initializer_list ',' initializer
;
edge: NUMCONST ':' NUMCONST
;

compound_stmt:  '{'
|               compound_stmt stmt
;
selection_stmt: IF p_expr stmt %prec LOWER_THAN_ELSE
|               IF p_expr stmt ELSE stmt 
;
iteration_stmt: WHILE p_expr stmt
|               FOR '(' expr ';' expr ';' expr ')' stmt
|               FOR '(' typename identifier ':' identifier ')' stmt
|               BFS '(' typename identifier ':' identifier ')' stmt
|               DFS '(' typename identifier ':' identifier ')' stmt
;
p_expr: '(' expr ')'
;
exprs: expr
|      exprs ',' expr
;

expr: NUMCONST
|     STRINGCONST
|     identifier
|     '(' exprs ')'
|     expr '[' exprs ']'
|     expr '(' ')'
|     expr '(' exprs ')'
|     expr '=' expr
|     expr '+' expr
|     expr '-' expr %prec '+'
|     expr '*' expr
/* |     expr '/' expr %prec '*'
|     expr '%' expr %prec '*' */
|     expr "+=" expr
|     expr "-=" expr
|     "++" expr
|     "--" expr %prec "++"
|     expr "++" 
|     expr "--" %prec "++"
|     expr "||" expr
|     expr "&&" expr
|     expr "==" expr
|     expr "!=" expr %prec "=="
|     '&' expr
|     '*' expr  %prec '&'
|     '-' expr  %prec '&'
|     '!' expr  %prec '&'
|     expr '?' expr ':' expr
;
function: typename identifier '(' paramdecls ')' stmt
;
paramdecls: paramdecl
|           %empty
;
paramdecl:  paramdecl ',' typename identifier
|           typename identifier
;
typename: INT
|         FLOAT
|         STRING
|         GRAPH
/* |         NODEPROP '<' identifier '>'
|         EDGEPROP '<' identifier '>'
|         NODESET '<' identifier '>'
|         EDGESET '<' identifier '>' */
;
identifier: IDENTIFIER;
%%

// Register errors to the driver:
void yy::gralgo::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
