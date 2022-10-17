%skeleton "lalr1.cc" /* -*- c++ -*- */
%require "3.0"
%defines
%define api.parser.class {parser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

class Driver;

enum class id_type {
  function,
  parameter,
  variable
};

enum class type_name {
  INT,
  BOOL,
  FLOAT,
  CHAR,
  VOID,
  GRAPH,
  DGRAPH,
  NODE_SET,
  NODE_PROP,
  NODE_SEQ,
  EDGE_SET,
  EDGE_PROP,
  EDGE_SEQ,
  FUNC // for function type_name
};
struct identifier {
  id_type type;
  type_name v_type;
  std::size_t index = 0;
  std::string name;
  identifier() { }
  identifier(id_type _type, type_name _v_type, std::size_t _index, std::string _name) : type(_type), v_type(_v_type), index(_index), name(_name) { }
};

#define ENUM_NODES(f) \
  f(identifier) f(string) f(number) f(double_const) \
  f(add) f(neg) f(eq) \
  f(cor) f(cand) f(loop) \
  f(addrof) f(deref) \
  f(fcall) \
  f(copy) \
  f(comma) \
  f(mul) f(div) f(mod) \
  f(ret) f(nop) 


#define f(n) n,
enum class node_type { ENUM_NODES(f) };
#undef f

struct node;
typedef std::vector<struct node> node_vec; 
struct node
{
  node_type type;
  identifier ident = {};
  std::string strvalue{};
  int numvalue{};
  double doublevalue{};
  node_vec params;
  // define constructor and required functions
  template<typename... T>
  node(node_type t, T&&... args) : type(t), params{ std::forward<T>(args)... } {}

  node()  : type(node_type::nop)  {}
  node(const identifier& i) : type(node_type::identifier), ident(i)  {}
  node(identifier&& i)  : type(node_type::string), ident(std::move(i))  {}
  node(int v) : type(node_type::number), numvalue(v) {}
  node(double v) : type(node_type::double_const), doublevalue(v) {}
  node(std::string&& v) : type(node_type::string), strvalue(std::move(v)) {}

  node operator%=(node&& b) && {return node(node_type::copy, std::move(b), std::move(*this));}

};

#define f(p) \
template<typename ...T> \
inline node n_##p(T&& ...args) { return node(node_type::p, std::forward<T>(args)...);} 
ENUM_NODES(f)
#undef f

struct function 
{
  std::string name;
  type_name ret_type;
  unsigned num_params = 0;
  unsigned num_vars = 0;
  std::vector<type_name> param_types;
  node code;
  function(){}
};


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

struct context
{
    yy::location loc;
    std::vector<std::map<std::string, identifier>> scopes;
    std::vector<function> func_list;
    unsigned tempcounter = 0;
    function fun;
    std::vector<std::pair<yy::location,std::string>> error_list;
public:
    const identifier& define(const std::string& name, identifier&& f)
    {
        auto r = scopes.back().emplace(name, std::move(f));
        if(!r.second) error_list.emplace_back(loc, "Duplicate definition <"+name+">");
        return r.first->second;
    }
    node def(const std::string& name,type_name type)     { return define(name, identifier{id_type::variable,type, fun.num_vars++,   name}); }
    node defun(const std::string& name)   { return define(name, identifier{id_type::function, type_name::FUNC,  func_list.size(), name}); }
    node defparm(const std::string& name,type_name type) { return define(name, identifier{id_type::parameter,type, fun.num_params++, name}); }
    node temp()                           { return def("$I" + std::to_string(tempcounter++), type_name::INT); }
    node use(const std::string& name)
    {
        for(auto j = scopes.crbegin(); j != scopes.crend(); ++j)
        {
          auto i = j->find(name);
          if(i != j->end())
            return i->second;
        }
        error_list.emplace_back(loc, "Undefined identifier <"+name+">");
    }
    void add_function(std::string&& name, node&& code,type_name ret)
    {
        fun.code = n_comma(std::move(code), n_ret(0)); // Add implicit "return 0;" at the end
        fun.name = std::move(name);
        fun.ret_type = ret;
        func_list.push_back(std::move(fun));
        fun = {};
    }
    void operator ++() { scopes.emplace_back(); } // Enter scope
    void operator --() { scopes.pop_back();     } // Exit scope
};
#define M(x) std::move(x)
#define C(x) node(x)
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
%token <double> DOUBLE_CONST "double_const"
%type<std::string> identifier
%type<node> expr exprs stmt selection_stmt jump_stmt expression_stmt iteration_stmt vardec_stmt empty_stmt compound_stmt p_expr
%type<type_name> typename

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
/* %printer { yyoutput << $$; } <*>; */

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
|          RETURN expr ';'                  { $$ = n_ret(M($2));         }
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
selection_stmt: IF p_expr stmt %prec LOWER_THAN_ELSE  { $$ = n_cand(M($2), M($3)); }
|               IF p_expr stmt ELSE stmt   
;
iteration_stmt: WHILE p_expr stmt          { $$ = n_loop(M($2), M($3)); }
|               FOR '(' expr ';' expr ';' expr ')' stmt
|               FOR '(' typename identifier ':' identifier ')' stmt
|               BFS '(' typename identifier ':' identifier ')' stmt
|               DFS '(' typename identifier ':' identifier ')' stmt
;
p_expr: '(' expr ')'
;
exprs: expr                     { $$ = M($1); };
|      exprs ',' expr
;

expr: NUMBER                    { $$ = $1;    }
|     STRING_LITERAL            { $$ = M($1); }
|     identifier                // { $$ = ctx.use($1);   }
|     '(' exprs ')'             { $$ = M($2); }
|     expr '[' exprs ']'        { $$ = n_deref(n_add(M($1), M($3))); }
|     expr '(' ')'              { $$ = n_fcall(M($1)); }
|     expr '(' exprs ')'
|     expr '=' expr             { $$ = M($1) %= M($3); }
|     expr '+' expr             { $$ = n_add( M($1), M($3)); }
|     expr '-' expr %prec '+'   { $$ = n_add( M($1), n_neg(M($3))); }
|     expr '*' expr             { $$ = n_mul( M($1), M($3)); }
|     expr '/' expr %prec '*'   { $$ = n_div( M($1), M($3)); }
|     expr '%' expr             { $$ = n_mod( M($1), M($3));}
|     expr "+=" expr            //{ if(!$3.is_pure()) { $$ = ctx.temp() %= node_addrof(M($1)); $1 = node_deref($$.params.back()); } $$ = node_comma(M($$), M($1) %= node_add(C($1), M($3))); }
|     expr "-=" expr            //{ if(!$3.is_pure()) { $$ = ctx.temp() %= node_addrof(M($1)); $1 = node_deref($$.params.back()); } $$ = node_comma(M($$), M($1) %= node_add(C($1), node_neg(M($3)))); }
|     "++" expr                 //{ if(!$2.is_pure()) { $$ = ctx.temp() %= node_addrof(M($2)); $2 = node_deref($$.params.back()); } $$ = node_comma(M($$), M($2) %= node_add(C($2),  1l)); }
|     "--" expr %prec "++"      //{ if(!$2.is_pure()) { $$ = ctx.temp() %= node_addrof(M($2)); $2 = node_deref($$.params.back()); } $$ = node_comma(M($$), M($2) %= node_add(C($2), -1l)); }
|     expr "++"                 //{ if(!$1.is_pure()) { $$ = ctx.temp() %= node_addrof(M($1)); $1 = node_deref($$.params.back()); } auto i = ctx.temp(); $$ = node_comma(M($$), C(i) %= C($1), C($1) %= node_add(C($1),  1l), C(i)); }
|     expr "--" %prec "++"      //{ if(!$1.is_pure()) { $$ = ctx.temp() %= node_addrof(M($1)); $1 = node_deref($$.params.back()); } auto i = ctx.temp(); $$ = node_comma(M($$), C(i) %= C($1), C($1) %= node_add(C($1), -1l), C(i)); }
|     expr "||" expr            { $$ = n_cor( M($1), M($3)); }
|     expr "&&" expr            { $$ = n_cand(M($1), M($3)); }
|     expr "==" expr            { $$ = n_eq(  M($1), M($3)); }
|     expr "!=" expr %prec "==" { $$ = n_eq(n_eq(M($1), M($3)), 0); }
|     '&' expr                  { $$ = n_addrof(M($2)); }
|     '*' expr  %prec '&'       { $$ = n_deref(M($2));  }
|     '-' expr  %prec '&'       { $$ = n_neg(M($2));    }
|     '!' expr  %prec '&'       { $$ = n_eq(M($2), 0); }
|     expr '?' expr ':' expr    //{ auto i = ctx.temp(); $$ = node_comma(node_cor(node_cand(M($1), node_comma(C(i) %= M($3), 1l)), C(i) %= M($5)), C(i)); }
;
function: typename identifier '(' paramdecls ')' '{' stmt '}' 
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
identifier: IDENTIFIER               { $$ = M($1); };

%%

// Register errors to the driver:
void yy::parser::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
