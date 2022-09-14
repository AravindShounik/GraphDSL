%{
    void  Print_Operation(char* Token);
    void Comment();
    #include <stdio.h>
    #include <stdlib.h>
    #include "parser.tab.h"

%}

D                       [0-9]
L                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
FS                      (f|F|l|L)
IS                      (u|U|l|L)*
%%

\n                          { yylineno++; }
"/*"([^*]|\*+[^*/])*\**"*/" { Comment() ; }
"//"[^\r\n]*$               {; }


"auto"                  {   return AUTO  ; }
"break"                 {   return BREAK ; }

"char"                  {   return CHAR ; }
"string"                {   return STRING ; }
"const"                 {   return CONST ; }
"continue"              {   return CONTINUE  ; }



"else"                  {   return ELSE  ; }
"float"                 {   return FLOAT  ; }
"bool"                  {   return BOOL  ; }
"for"                   {   return FOR  ; }
"if"                    {   return IF ; }
"int"                   {   return INT  ; }
"large"                 {   return LARGE  ; }
"return"                {   return RETURN ; }
"small"                 {   return SMALL  ; }
"static"                {   return STATIC ; }
"struct"                {   return STRUCT  ; }

"typedef"               {   return TYPEDEF  ; }
"void"                  {   return VOID  ; }
"while"                 {   return WHILE  ; }

"func"                  {   return FUNCTION  ; }
"Graph"                 {   return GRAPH  ; }
"dGraph"                {   return DIRECTED_GRAPH  ; }
"NodeSet"               {   return NODE_SET ;}
"NodeSeq"               {   return NODE_SEQUENCE  ; }
"NodeProp"              {   return NODE_PROP ; }
"EdgeProp"              {   return EDGE_PROP ; }
"Edge"                  {   return EDGE  ; }
"BFS"                   {   return BFS; }
"DFS"                   {   return DFS ; }
"Nodes"                 {   return NODES ; }
"Node"                  {   return NODE ; }
"Levels"                {   return LEVELS ; }
"Neighbours"            {   return NEIGHBOURS  ;  }

"..."                   {   return ELLIPSIS       ; }
"@="                    {   return APPEND_ASSIGN       ; }
">>="                   {   return RIGHT_SHIFT_ASSIGN  ; }
"<<="                   {   return LEFT_SHIF_ASSIGN    ; }
"+="                    {   return ADD_ASSIGN     ; }
"-="                    {   return SUB_ASSIGN    ; }
"**="                   {   return EXP_ASSIGN     ; }
"*="                    {   return MUL_ASSIGN     ; }
"/="                    {   return DIV_ASSIGN     ; }
"%="                    {   return MOD_ASSIGN    ; }
"&="                    {   return AND_ASSIGN     ; }
"^="                    {   return XOR_ASSIGN     ; }
"|="                    {   return OR_ASSIGN     ; }
">>"                    {   return RSHIFT_OP     ; }
"<<"                    {   return LSHIFT_OP     ; }
"++"                    {   return INC_OP     ; }
"--"                    {   return DEC_OP    ; }
"->"                    {   return PTR_OP     ; }
"&&"                    {   return AND_OP     ; }
"||"                    {   return OR_OP    ; }
"<="                    {   return LE_OP     ; }
">="                    {   return GE_OP     ; }
"=="                    {   return EQ_OP     ; }
"!="                    {   return NE_OP     ; }
";"                     {   return STM_DELIM     ; }
"{"                     {   return L_BRACE    ; }
"}"                     {   return R_BRACE     ; }
":"                     {   return COLON_OP     ; }
"="                     {   return ASSIGN     ; }
"("                     {   return L_PAREN     ; }
")"                     {   return R_PAREN     ; }

"@"                     {   return APPEND_OP; }
"**"                    {   return EXP_OP; }
"["                     {   return L_BRAKET       ; }
"]"                     {   return R_BRAKET       ; }
"."                     {   return DOT_OP;         ; }
","                     {   return COMMA_OP;       ; }
"&"                     {   return ADDRESS_OP;     ; }
"!"                     {   return NOT_OP;         ; }
"~"                     {   return BIT_COMPL_OP   ; }
"-"                     {   return SUBTRACT_OP;    ; }
"+"                     {   return ADDITION_OP;    ; }
"*"                     {   return MULTI_OP      ; }
"/"                     {   return DIV_OP;         ; }
"%"                     {   return MOD_OP;         ; }
"<"                     {   return LESSER_OP;      ; }
">"                     {   return GREATER_OP;      ; }
"^"                     {   return BIT_XOR_OP;     ; }
"|"                     {   return BIT_OR_OP;      ; }
"?"                     {   return COND_OP;        ; }




L?\"(\\.|[^\\"])*\"     {   return STRING_LITERAL; }
{L}({L}|{D})*           {   return IDENTIFIER; }
0[xX]{H}+{IS}?          {   return HEXAL_CONST; } 
0{D}+{IS}?              {   return OCTAL_CONST; }  
{D}+{IS}?               {   return CONST; }  
'(\\.|[^\\'])+'         {   return CONST; }  
L'(\\.|[^\\'])+'        {   return CONST; }  
{D}+{E}{FS}?            {   return CONST; }
{D}*"."{D}+({E})?{FS}?  {   return CONST; }
{D}+"."{D}*({E})?{FS}?  {   return CONST; }

[ \t\v\f]               {; }

.                       {   return INVALID_TOKEN;  }


%%
void    Print_Operation(char* Token)
{ 
    fprintf(yyout,
            "%d : '%s' : %d : '%s'\n"
            ,  yylineno , Token , yyleng , yytext
          );
}

void Comment()
{
  for(int i = 0 ; i < yyleng ;i++)
  {
    if(yytext[i] == '\n') yylineno++;
  }

}

int yywrap(void)
{
  return 1;
}

