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
  char* str;
  struct symbol *s;		/* which symbol */
  struct symlist *sl;
  int fn;			/* which function */
}

/* declare tokens */
%token <d> DOUBLE 
%token <i> INT 
%token <str> STRING
%token <s> NAME
%token <fn> FUNC TYPE
/* %token EOL */

%token IF ELSE WHILE LET LOWER_THAN_ELSE FOR
%token BFS DFS NODES LEVELS NEIGHBOURS
%token INC DEC OR AND

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%nonassoc <fn> CMP
%nonassoc <fn> ASGN
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist translation_list translation_unit edge literal literal_list array
%type <sl> symlist

%start start_unit

%%

stmt: IF '(' exp ')' stmt %prec LOWER_THAN_ELSE   { $$ = newflow('I', $3, $5, NULL); }
   | IF '(' exp ')' stmt ELSE stmt  { $$ = newflow('I', $3, $5, $7); }
   | WHILE '(' exp ')' stmt           { $$ = newflow('W', $3, $5, NULL); }
   | FOR '(' exp ';' exp ';' exp ')' stmt { $$ = newfor('R',$3,$5,$7,$9);}
   | FOR '(' TYPE NAME ':' NAME ')' stmt { $$ = newfor_r('B', $3, $4, $6, $8);}
   | BFS '(' TYPE NAME ':' NAME ',' TYPE NAME ')' stmt { $$ = bfs(16, $3, $4, $6, $8, $9, $11); }
   | DFS '(' TYPE NAME ':' NAME ',' TYPE NAME ')' stmt { $$ = dfs(17, $3, $4, $6, $8, $9, $11); }
   | TYPE NAME '=' exp ';' { $$ = newinit($1,$2,$4);}
   | TYPE symlist ';' {  $$ = setType($1, $2);}
   | exp ';'
   | '{' list '}'  { $$ = $2; }
   | TYPE '<' NAME '>' symlist ';'  
   | TYPE '<' NAME '>' NAME '=' exp ';' 
;

list: stmt { $$ = newast('L',$1,NULL); }
   | stmt list { $$ = newast('L', $1, $2);}
;

edge: INT ':' INT         { $$ = newedge($1,$3);}
;

literal: edge                 
   | DOUBLE               { $$ = newdouble($1); }
   | INT                  { $$ = newint($1); }
   | STRING               { $$ = newstr($1); }
;

literal_list: literal
| literal ',' literal_list { $$ = newast('L', $1, $3); } 

array: '[' literal_list ']' {$$ = newarray($2);}

exp: exp CMP exp          { $$ = newcmp($2, $1, $3); }
   | exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '-' exp          { $$ = newast('-', $1,$3);}
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | exp '/' exp          { $$ = newast('/', $1,$3); }
   | '|' exp              { $$ = newast('|', $2, NULL); }
   | '(' exp ')'          { $$ = $2; }
   | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
   | literal
   | array
   | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
   | NAME                 { $$ = newref($1); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
   | NAME '(' explist ')' { $$ = newcall($1, $3); }
   | NAME ASGN exp       { $$ =  newasgn_ops($2,$1,$3); }
; 

explist: exp
 | exp ',' explist  { $$ = newast('L', $1, $3); }
;
symlist: NAME       { $$ = newsymlist($1, NULL); }
 | NAME ',' symlist { $$ = newsymlist($1, $3); }
;

translation_unit: stmt {$$=$1;}
  | LET NAME '(' symlist ')' '{' list '}' {
                        $$=$7;
                       dodef($2, $4, $7);
                      //  printf("Defined %s\n> ", $2->name); 
                      }
  | error {}
;
translation_list : translation_unit
  | translation_list translation_unit { $$ = newast('T', $1, $2); }
;
start_unit : translation_list { dumpast($1,0);}
%%
