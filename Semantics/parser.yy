%skeleton "lalr1.cc" /* -*- c++ -*- */
%require "3.0"
%defines
%define api.parser.class {parser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
class Driver;
}

// The parsing context.
%param { Driver& driver }

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
#include "driver.hh"
#define yylex driver.lexer.yylex
}

// Tokens:
%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  ASSIGN  "="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
  MOD "%"
  B_OR "|"
  COMMA ","
  SEMI_COLON ";"
  COLON ":"
  LBRACE "{"
  RBRACE "}"
  LSB "["
  RSB "]"
  AND "&&"
  OR "||"
  PP "++"
  MM "--"
  PL_EQ "+="
  MI_EQ "-="
  MU_EQ "*="
  DI_EQ "/="
  LESS "<"
  GREATER ">"
  NE "!="
  EQ "=="
  GEQ ">="
  LEQ "<="

  BREAK "break"
  CONTINUE "continue"
  RETURN "return"
  
  VOID "void"
  INT "int"
  FLOAT "float"
  CHAR "char"
  STRING "string"
  GRAPH "graph"
  DGRAPH "dgraph"
  NODE "node"
  NODE_SET "node_set"
  NODE_SEQ "node_seq"
  NODE_PROP "node_prop"
  EDGE_PROP "edge_prop"
  EDGE_SET "edge_set"
  EDGE_SEQ "edge_seq"
  IF "if"
  ELSE "else"
  WHILE "while"
  FOR "for"
  BFS "BFS"
  DFS "DFS"
  NODES "nodes"
  LEVELS "levels"
  NEIGHBOURS "neighbours"
;

// Use variant-based semantic values: %type and %token expect genuine types
%token <std::string> IDENTIFIER "identifier" STRING_LITERAL
%token <int> NUMBER "number"
%token <double> DOUBLE
%type  <int> expr
%type<std::string> identifier

/* Operator precedence */
%left  ','
%right '?' ':' '=' "+=" "-="
%left  "||"
%left  "&&"
%left  "==" "!="
%left  '+' '-'
%left  '*' '/' '%'
%right '&' "++" "--"
%left  '(' '['

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

// No %destructors are needed, since memory will be reclaimed by the
// regular destructors.
%printer { yyoutput << $$; } <*>;

// Grammar:
%%
%start program;

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
vardec1: identifier '=' initializer ';'
|        identifier ';'
;
initializer: expr
|            edge
|            '{' initializer_list '}'
;
initializer_list: initializer
|                 initializer_list ',' initializer
;
edge: NUMBER ':' NUMBER
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

expr: NUMBER
|     STRING_LITERAL
|     identifier
|     '(' exprs ')'
|     expr '[' exprs ']'
|     expr '(' ')'
|     expr '(' exprs ')'
|     expr '=' expr
|     expr '+' expr
|     expr '-' expr %prec '+'
|     expr '*' expr
|     expr '/' expr %prec '*'
|     expr '%' expr
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
typename: VOID
|         INT
|         CHAR
|         FLOAT
|         STRING
|         GRAPH
|         DGRAPH
|         NODE_PROP '<' identifier '>'
|         NODE_SET '<' identifier '>'
|         NODE_SEQ '<' identifier '>'
|         EDGE_PROP '<' identifier '>'
|         EDGE_SET '<' identifier '>'
|         EDGE_SEQ '<' identifier '>'
;
identifier: IDENTIFIER;

%%

// Register errors to the driver:
void yy::parser::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
