%{
    void Print_Operation(char* Token);
    void Comment();
    #include <stdio.h>
    #include <stdlib.h>

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
