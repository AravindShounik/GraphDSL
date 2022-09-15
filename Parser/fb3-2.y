/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb3-2.y,v 2.1 2009/11/08 02:53:18 johnl Exp $
 */
/* calculator with AST */

%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "fb3-2.h"
%}

%union {
  struct ast *a;
  double d;
  int i;
  struct symbol *s;		/* which symbol */
  struct symlist *sl;
  int fn;			/* which function */
}

/* declare tokens */
%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC TYPE
%token EOL

%token IF ELSE WHILE LET LOWER_THAN_ELSE FOR
%token BFS DFS NODES LEVELS NEIGHBOURS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%nonassoc <fn> CMP
%nonassoc <fn> ASSGN
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start calclist

%%

stmt: IF '(' exp ')' stmt %prec LOWER_THAN_ELSE   { $$ = newflow('I', $3, $5, NULL); }
   | IF '(' exp ')' stmt ELSE stmt  { $$ = newflow('I', $3, $5, $7); }
   | WHILE '(' exp ')' stmt           { $$ = newflow('W', $3, $5, NULL); }
   | FOR '(' exp ';' exp ';' exp ')' stmt { $$ = newfor('R',$3,$5,$7,$9);}
   | FOR '(' TYPE NAME ':' NAME ')' stmt { $$ = newfor_r('B', $3, $4, $6, $8);}
   | TYPE NAME '=' exp ';' { $$ = newinit($1,$2,$4);}
   | TYPE symlist ';' { $$ = newinit_d($1, $2);}
   | exp ';'
   | '{' list '}'  { $$ = $2; }
;

list: stmt { $$ = newast('L',$1,NULL); }
   | stmt list { $$ = newast('L', $1, $2);}
   ;

exp: exp CMP exp          { $$ = newcmp($2, $1, $3); }
   | exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '-' exp          { $$ = newast('-', $1,$3);}
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | exp '/' exp          { $$ = newast('/', $1,$3); }
   | '|' exp              { $$ = newast('|', $2, NULL); }
   | '(' exp ')'          { $$ = $2; }
   | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
   | NUMBER               { $$ = newnum($1); }
   | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
   | NAME                 { $$ = newref($1); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
   | NAME '(' explist ')' { $$ = newcall($1, $3); }
   | exp ASSGN exp        { $$ = newast($2,$1,$3); }
;

explist: exp
 | exp ',' explist  { $$ = newast('L', $1, $3); }
;
symlist: NAME       { $$ = newsymlist($1, NULL); }
 | NAME ',' symlist { $$ = newsymlist($1, $3); }
;

calclist: /* nothing */
  | calclist stmt EOL {
    if(debug) dumpast($2, 0);
   //   printf("= %4.4g\n> ", eval($2));
   //   treefree($2);
    }
  | calclist LET NAME '(' symlist ')' '=' list EOL {
                       dodef($3, $5, $8);
                       printf("Defined %s\n> ", $3->name); }

  | calclist error EOL { yyerrok; printf("> "); }
 ;
%%
