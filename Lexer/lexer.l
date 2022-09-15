%{
    void Print_Operation(char* Token);
    void Comment();
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>

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


"auto"                  { Print_Operation("AUTO")  ; }
"break"                 { Print_Operation("BREAK") ; }

"char"                  { Print_Operation("CHAR")  ; }
"string"                { Print_Operation("STRING")  ; }
"const"                 { Print_Operation("CONST") ; }
"continue"              { Print_Operation("CONTINUE")  ; }



"else"                  { Print_Operation("ELSE")  ; }
"float"                 { Print_Operation("FLOAT")  ; }
"bool"                  { Print_Operation("BOOL")  ; }
"for"                   { Print_Operation("FOR")  ; }
"if"                    { Print_Operation("IF")  ; }
"int"                   { Print_Operation("INT")  ; }
"large"                 { Print_Operation("LARGE")  ; }

"return"                { Print_Operation("RETURN")  ; }
"small"                 { Print_Operation("SMALL")  ; }


"static"                { Print_Operation("STATIC")  ; }
"struct"                { Print_Operation("STRUCT")  ; }

"typedef"               { Print_Operation("TYPEDEF")  ; }
"void"                  { Print_Operation("VOID")  ; }
"while"                 { Print_Operation("WHILE")  ; }

"func"                  { Print_Operation("FUNCTION")  ; }
"Graph"                 { Print_Operation("GRAPH")  ; }
"dGraph"                { Print_Operation("DIRECTED_GRAPH")  ; }
"NodeSet"               { Print_Operation("NODE_SET") ;}
"NodeSeq"               { Print_Operation("NODE_SEQUENCE")  ; }
"NodeProp"              { Print_Operation("NODE_PROP"); }
"EdgeProp"              { Print_Operation("EDGE_PROP"); }
"Edge"                  { Print_Operation("EDGE")  ; }
"BFS"                   { Print_Operation("BFS"); }
"DFS"                   { Print_Operation("DFS"); }
"Nodes"                 { Print_Operation("NODES"); }
"Node"                  { Print_Operation("NODE")  ; }
"Levels"                { Print_Operation("LEVELS"); }
"Neighbours"            { Print_Operation("NEIGHBOURS");  }


"..."                   { Print_Operation("ELLIPSIS")       ; }
"@="                    { Print_Operation("APPEND_ASSIGN")       ; }
">>="                   { Print_Operation("RIGHT_SHIFT_ASSIGN")   ; }
"<<="                   { Print_Operation("LEFT_SHIF_ASSIGN")    ; }
"+="                    { Print_Operation("ADD_ASSIGN")     ; }
"-="                    { Print_Operation("SUB_ASSIGN")     ; }
"**="                   { Print_Operation("EXP_ASSIGN")     ; }
"*="                    { Print_Operation("MUL_ASSIGN")     ; }
"/="                    { Print_Operation("DIV_ASSIGN")     ; }
"%="                    { Print_Operation("MOD_ASSIGN")     ; }
"&="                    { Print_Operation("AND_ASSIGN")     ; }
"^="                    { Print_Operation("XOR_ASSIGN")     ; }
"|="                    { Print_Operation("OR_ASSIGN")     ; }
">>"                    { Print_Operation("RSHIFT_OP")     ; }
"<<"                    { Print_Operation("LSHIFT_OP")     ; }
"++"                    { Print_Operation("INC_OP")     ; }
"--"                    { Print_Operation("DEC_OP")     ; }
"->"                    { Print_Operation("PTR_OP")     ; }
"&&"                    { Print_Operation("AND_OP")     ; }
"||"                    { Print_Operation("OR_OP")     ; }
"<="                    { Print_Operation("LE_OP")     ; }
">="                    { Print_Operation("GE_OP")     ; }
"=="                    { Print_Operation("EQ_OP")     ; }
"!="                    { Print_Operation("NE_OP")     ; }
";"                     { Print_Operation("STM_DELIM")     ; }
"{"                     { Print_Operation("L_BRACE")     ; }
"}"                     { Print_Operation("R_BRACE")     ; }
":"                     { Print_Operation("COLON_OP")     ; }
"="                     { Print_Operation("ASSIGN")     ; }
"("                     { Print_Operation("L_PAREN")     ; }
")"                     { Print_Operation("R_PAREN")     ; }

"@"                     { Print_Operation("APPEND_OP"); }
"**"                    { Print_Operation("EXP_OP"); }
"["                     { Print_Operation("L_BRAKET");       ; }
"]"                     { Print_Operation("R_BRAKET");       ; }
"."                     { Print_Operation("DOT_OP");         ; }
","                     { Print_Operation("COMMA_OP");       ; }
"&"                     { Print_Operation("ADDRESS_OP");     ; }
"!"                     { Print_Operation("NOT_OP");         ; }
"~"                     { Print_Operation("BIT_COMPL_OP");   ; }
"-"                     { Print_Operation("SUBTRACT_OP");    ; }
"+"                     { Print_Operation("ADDITION_OP");    ; }
"*"                     { Print_Operation("MULTI_OP");       ; }
"/"                     { Print_Operation("DIV_OP");         ; }
"%"                     { Print_Operation("MOD_OP");         ; }
"<"                     { Print_Operation("LESSER_OP");      ; }
">"                     { Print_Operation("GREATER_OP");      ; }
"^"                     { Print_Operation("BIT_XOR_OP");     ; }
"|"                     { Print_Operation("BIT_OR_OP");      ; }
"?"                     { Print_Operation("COND_OP");        ; }




L?\"(\\.|[^\\"])*\"     { Print_Operation("STRING_LITERAL"); }
{L}({L}|{D})*           { Print_Operation("IDENTIFIER"); }
0[xX]{H}+{IS}?          { Print_Operation("HEXAL_CONST"); }
0{D}+{IS}?              { Print_Operation("OCTAL_CONST"); }
{D}+{IS}?               { Print_Operation("CONST"); }
'(\\.|[^\\'])+'         { Print_Operation("CONST"); }
L'(\\.|[^\\'])+'        { Print_Operation("CONST"); }
{D}+{E}{FS}?            { Print_Operation("CONST"); }
{D}*"."{D}+({E})?{FS}?  { Print_Operation("CONST"); }
{D}+"."{D}*({E})?{FS}?  { Print_Operation("CONST"); }

[ \t\v\f]               {; }

.                       { Print_Operation("INVALID TOKEN");  }


%%
void Print_Operation(char* Token)
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

int main()
{
   yylex();
   return 0;
}
