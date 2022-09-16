/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb3-2.h,v 2.1 2009/11/08 02:53:18 johnl Exp $
 */
/*
 * Declarations for a calculator fb3-1
 */

/* symbol table */
struct symbol
{ /* a variable name */
  int type;
  char *name;
  double value;
  struct ast *func;     /* stmt for the function */
  struct symlist *syms; /* list of dummy args */
};

struct symbol *lookup(char *);

/* list of symbols, for an argument list */
struct symlist
{
  struct symbol *sym;
  struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

/* node types
 *  + - * / |
 *  0-7 comparison ops, bit coded 04 equal, 02 less, 01 greater
 *  M unary minus
 *  L statement list
 *  I IF statement
 *  W WHILE statement
 *  N symbol ref
 *  = assignment
 *  S list of symbols
 *  F built in function call
 *  C user function call
 */

enum bifs
{ /* built-in functions */
  B_sqrt = 1,
  B_exp,
  B_log,
  B_print
};

/* nodes in the Abstract Syntax Tree */
/* all have common initial nodetype */

struct ast
{
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct fncall
{               /* built-in function */
  int nodetype; /* type F */
  struct ast *l;
  enum bifs functype;
};

struct ufncall
{                /* user function */
  int nodetype;  /* type C */
  struct ast *l; /* list of arguments */
  struct symbol *s;
};

struct flow
{
  int nodetype;     /* type I or W */
  struct ast *cond; /* condition */
  struct ast *tl;   /* then or do list */
  struct ast *el;   /* optional else list */
};

struct for_loop
{
  int nodetype;
  struct ast *init;
  struct ast *cond;
  struct ast *inc;
  struct ast *stmt;
};

struct rfor_loop
{
  int nodetype;
  struct symbol *d;
  struct symbol *v;
  struct ast *stmt;
};

struct bfs
{
  int nodetype;
  struct symbol *d;
  struct symbol *g;
  struct symbol *stSym;
  struct ast *stmt;
};

struct dfs
{
  int nodetype;
  struct symbol *d;
  struct symbol *g;
  struct symbol *stSym;
  struct ast *stmt;
};

struct doubleval
{
  int nodetype; /* type D */
  double number;
};
struct intval
{
  int nodetype; /* type I */
  int number;
};

struct edgeval
{
  int nodetype; /* type E */
  int source;
  int dest;
};

struct strval
{
  int nodetype; /* type S */
  char *s;
};

struct arrayval
{
  int nodetype;  /* type A */
  struct ast *l; /* list of literals */
};
struct funcval
{
  int nodetype;
  struct symbol *f;
};

struct symref
{
  int nodetype; /* type N */
  struct symbol *s;
};

struct symasgn
{
  int nodetype; /* type = */
  struct symbol *s;
  struct ast *v; /* value */
};

struct syminit
{
  int nodetype;
  struct symbol *s;
  struct ast *v;
};

/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newinit(int inittype, struct symbol *s, struct ast *v);
struct ast *newdouble(double d);
struct ast *newint(int i);
struct ast *newedge(int s, int d);
struct ast *newstr(char *s);
struct ast *newdef(struct symbol *f);
struct ast *newarray(struct ast *l);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);
struct ast *newfor(int nodetype, struct ast *init, struct ast *cond, struct ast *inc, struct ast *stmt);
struct ast *rangefor(int nodetype, int typename, struct symbol *d, struct symbol *v, struct ast *stmt);
struct ast *newasgn_ops(int nodetype, struct symbol *l, struct ast *r);
struct ast *dfs(int nodetype, int typename_d, struct symbol *d, struct symbol *g, struct symbol *stSym, struct ast *stmt);
struct ast *bfs(int nodetype, int typename_d, struct symbol *d, struct symbol *g, struct symbol *stSym, struct ast *stmt);

struct ast *settype(int inittype, struct symlist *sl);

/* define a function */
void dodef(int type, struct symbol *name, struct symlist *syms, struct ast *stmts);

/* evaluate an AST */
double eval(struct ast *);

/* delete and free an AST */
void treefree(struct ast *);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

extern int debug;
void dumpast(struct ast *a, int level);

/* Maping Assignment Operators */
char *map_asgn_op(char ch);
char *map_logical_op(int val);