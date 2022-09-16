/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb3-2.l,v 2.1 2009/11/08 02:53:18 johnl Exp $
*/
/* recognize tokens for the calculator */

%option noyywrap nodefault yylineno
%{
# include <string.h>
# include "fb3-2.h"
# include "fb3-2.tab.h"
%}

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
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
"(" |
")"     { return yytext[0]; }

 /* Assignment Ops */
"+="    {yylval.fn = 1;   return ASGN;}
"-="    {yylval.fn = 2;   return ASGN;}
"*="    {yylval.fn = 3;   return ASGN;}
"/="    {yylval.fn = 4;   return ASGN;}

 /* comparison ops */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"!="    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

 /* type specifiers */
 "void"     {yylval.fn = 1; return TYPE;}
 "int"      {yylval.fn = 2; return TYPE;}
 "large"    {yylval.fn = 3; return TYPE;}
 "float"    {yylval.fn = 4; return TYPE;}
 "char"     {yylval.fn = 5; return TYPE;}
 "string"   {yylval.fn = 6; return TYPE;}
 "Graph"    {yylval.fn = 7; return TYPE;}
 "dGraph"   {yylval.fn = 8; return TYPE;}
 "NodeSet"  {yylval.fn = 9; return TYPE;}
 "NodeSeq"  {yylval.fn = 10;return TYPE;}
 "NodeProp" {yylval.fn = 11;return TYPE;}
 "EdgeProp" {yylval.fn = 12;return TYPE;}
 "small"    {yylval.fn = 13;return TYPE;}
 "Node"     {yylval.fn = 14;return TYPE;}

 /* keywords */
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR;}
"let"       { return LET;}
"BFS"       {return BFS;}
"DFS"       {return DFS;}
"Nodes"     {return NODES;}
"Levels"    {return LEVELS;}
"Neighbours" {return NEIGHBOURS;}


 /* built in functions */
"sqrt"  { yylval.fn = B_sqrt; return FUNC; }
"exp"   { yylval.fn = B_exp; return FUNC; }
"log"   { yylval.fn = B_log; return FUNC; }
"print" { yylval.fn = B_print; return FUNC; }

 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }

 /* names */
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.s = lookup(yytext); return NAME; }

 /* int */
[1-9][0-9]*     {yylval.i= atoi(yytext); return INT;}
 /* double */
[0-9]+"."[0-9]*{EXP}? |
"."[0-9]+{EXP}? { yylval.d = atof(yytext); return DOUBLE; }

 /* strings */
\"(\\.|[^\\"])*\" {yylval.str = (char*)malloc(sizeof(char)*yyleng);
                    strcpy(yylval.str,yytext);
                    return STRING; }

"//".*  
[ \n\t]   /* ignore white space */ 
\\\n    printf("c> "); /* ignore line continuation */
.	{ yyerror("Mystery character %c\n", *yytext); }
%%
