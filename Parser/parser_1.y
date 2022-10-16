%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "funcs_1.h"

int yylex();
%}


%union {
  struct Ast *a;
  double d;
  int i;
  char* str;
  int fn;			/* which function */
}

%token<d> D_CONSTANT
%token<i> I_CONSTANT 
%token<str> STRING FUNC


/* %token<a>  ENUMERATION_CONSTANT */
%token IF ELSE  LOWER_THAN_ELSE  BREAK CONTINUE RETURN
%token WHILE DO FOR
/* %token SWITCH CASE DEFAULT TYPEDEF_NAME STRUCT UNION ENUM SIZEOF NORETURN*/
%token<fn> INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP

%token<fn> MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN OR_ASSIGN XOR_ASSIGN

%token<fn> INT DOUBLE VOID CHAR BOOL 

%token CONST 


%token ELLIPSIS

%token<a> IDENTIFIER
%token BFS DFS NODES LEVELS NEIGHBOURS



%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right '='
%left OR_OP
%left AND_OP
%left '+' '-'
%left '*' '/' '%'
%nonassoc '|'

// unary minus nonassoc
%type<fn> assignment_operator '=' unary_operator
%type<a> unary_expression
%type<a> constant string type_name inclusive_or_expression exclusive_or_expression and_expression equality_expression relational_expression shift_expression additive_expression multiplicative_expression specifier_qualifier_list type_qualifier type_specifier 
%type<a> expression assignment_expression constant_expression conditional_expression logical_and_expression logical_or_expression cast_expression
%type<a> postfix_expression primary_expression

%type<a> statement  compound_statement expression_statement selection_statement iteration_statement jump_statement block_item_list block_item declaration
/* %type<a> labeled_statement */
%type<a> init_declarator_list init_declarator initializer
%type<a> designator_list designator designation argument_expression_list
%type<a> translation_unit external_declaration function_definition declaration_list declaration_specifiers declarator

%type<a> initializer_list 
%start translation_unit

%%

primary_expression
	: IDENTIFIER
	| constant
	| string
	| '(' expression ')' { $$ = $2; }
	;

constant
	: I_CONSTANT { $$ = newInt($1); }
	| D_CONSTANT { $$ = newDouble($1); }
	/* | ENUMERATION_CONSTANT { $$ = newInt($1); } */
	;

/* enumeration_constant		
	: IDENTIFIER
	; */

string
	: STRING { $$ = newStr($1); }
	| FUNC { $$ = newStr($1); }
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	/* | '(' type_name ')' '{' initializer_list '}' */
	/* | '(' type_name ')' '{' initializer_list ',' '}' */
	;

argument_expression_list
	: assignment_expression { $$ = $1; }
	| argument_expression_list ',' assignment_expression { $$ = append($1, $3); }
	;

unary_expression
	: postfix_expression 
	| INC_OP unary_expression { $$ = bnNode($2, NULL, INC_OP); }
	| DEC_OP unary_expression { $$ = bnNode($2, NULL, DEC_OP); }
	| unary_operator cast_expression { $$ = bnNode($2, NULL, $1); }
	/* | SIZEOF unary_expression { $$ = newast(UNARY_EXP, (ast*)$2, NULL, $1); } */
	/* | SIZEOF '(' type_name ')' { $$ = $3; } */
	;

unary_operator
	: '&' { $$ = 100; }
	| '*' { $$ = 101; }
	| '+' { $$ = 102; }
	| '-' { $$ = 103; }
	| '~' { $$ = 104; }
	| '!' { $$ = 105; }
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression { $$ = bnNode($2, $4, CAST_EXP); }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = bnNode($1, $3, MULTIPLY); }
	| multiplicative_expression '/' cast_expression { $$ = bnNode($1, $3, DIVIDE); }
	| multiplicative_expression '%' cast_expression { $$ = bnNode($1, $3, MOD); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = bnNode($1, $3, PLUS); }
	| additive_expression '-' multiplicative_expression { $$ = bnNode($1, $3, MINUS); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = bnNode($1, $3, LSHIFT); }
	| shift_expression RIGHT_OP additive_expression { $$ = bnNode($1, $3, RSHIFT); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = bnNode($1, $3, LESS); }
	| relational_expression '>' shift_expression { $$ = bnNode($1, $3, GREATER); }
	| relational_expression LE_OP shift_expression { $$ = bnNode($1, $3, LE); }
	| relational_expression GE_OP shift_expression { $$ = bnNode($1, $3, GE); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = bnNode($1, $3, EQ); }
	| equality_expression NE_OP relational_expression { $$ = bnNode($1, $3, NE); }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = bnNode($1, $3, U_AND); }
	;

exclusive_or_expression
	: and_expression { $$= $1; }
	| exclusive_or_expression '^' and_expression { $$ = bnNode($1, $3, XOR); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = bnNode($1, $3, U_OR); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = bnNode($1, $3, L_AND); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = bnNode($1, $3, L_OR); }
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = bnNode($1, $3, $2); }
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression { $$ = append($1, $2); }
	;

constant_expression
	: conditional_expression	{ $$ = $1; }
	;

declaration
	: declaration_specifiers ';' { $$ = $1; }
	| declaration_specifiers init_declarator_list ';' { }
	;

declaration_specifiers
	: type_specifier declaration_specifiers
	| type_specifier
	| type_qualifier declaration_specifiers
	| type_qualifier
	/* | function_specifier declaration_specifiers
	| function_specifier { $$ = $1; } */
	;

init_declarator_list
	: init_declarator { $$ = $1; }
	| init_declarator_list ',' init_declarator { $$ = append($1, $2); }
	;

init_declarator
	: declarator '=' initializer
	| declarator
	;

type_specifier
	: VOID { $$ = newType(T_VOID); }
	| CHAR { $$ = newType(T_CHAR); }
	| INT { $$ = newType(T_INT); }
	| DOUBLE { $$ = newType(T_DOUBLE); }
	| BOOL { $$ = newType(T_BOOL); }
	/* | struct_or_union_specifier { $$ = newType(T_STRUCT); } */
	/* | enum_specifier { $$ = newType(T_ENUM); } */
	/* | TYPEDEF_NAME		after it has been defined as such */
	;

/* struct_or_union_specifier
	: struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list ';'
	| specifier_qualifier_list struct_declarator_list ';'
	; */

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

/* struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: ':' constant_expression
	| declarator ':' constant_expression
	| declarator
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: enumeration_constant '=' constant_expression
	| enumeration_constant
	; */

type_qualifier
	: CONST { $$ = newType(T_CONST); }
	;

/* function_specifier
	: NORETURN
	; */

declarator
	: IDENTIFIER
	| '(' declarator ')' { $$ = $2; }
	| declarator '[' ']'
	/* | declarator '[' '*' ']' */
	| declarator '[' type_qualifier_list '*' ']'
	| declarator '[' type_qualifier_list assignment_expression ']'
	| declarator '[' type_qualifier_list ']'
	| declarator '[' assignment_expression ']'
	| declarator '(' parameter_list ')'
	| declarator '(' ')'
	| declarator '(' identifier_list ')'
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list abstract_declarator
	| specifier_qualifier_list
	;

abstract_declarator
	: direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' '*' ']'
	| '[' type_qualifier_list assignment_expression ']'
	| '[' type_qualifier_list ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

initializer
	: '{' initializer_list '}' { $$ = $2; }
	/* | '{' initializer_list ',' '}' { $$ = $2; } */
	| assignment_expression { $$ = $1; }
	;

initializer_list
	: initializer { $$ = $1; }
	/* : designation initializer { $$ = } */
	/* | initializer_list ',' designation initializer */
	| initializer_list ',' initializer { $$ = append($1, $3); }
	;

/* designation
	: designator_list '='
	;

designator_list
	: designator { $$ = $1; }
	| designator_list designator { $$ = append($1, $2); }
	;

designator
	: '[' constant_expression ']' { $$ = $2; }
	| '.' IDENTIFIER 
	; */

statement
	: compound_statement
	/* | labeled_statement */
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

/* labeled_statement
	: IDENTIFIER ':' statement { }
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	; */

compound_statement
	: '{' '}' { $$ = NULL; }
	| '{'  block_item_list '}' { $$ = $2; }
	;

block_item_list
	: block_item { $$ = $1; }
	| block_item_list block_item
	;

block_item
	: declaration { $$ = $1; }
	| statement { $$ = $1; }
	;

expression_statement
	: ';' { $$ = NULL; }
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement %prec LOWER_THAN_ELSE { $$ = newCond($3, $5, NULL); }
	| IF '(' expression ')' statement ELSE statement { $$ = newCond($3, $5, $7); }
	/* | SWITCH '(' expression ')' statement */
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = newLoop(WHILE_LOOP, NULL, NULL, $3, $5); }
	| DO statement WHILE '(' expression ')' ';' { $$ = newLoop(DOWHILE_LOOP, NULL, NULL, $5, $2); }
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = newLoop(FOR_LOOP, $3, $4, $5, $7); }
	| FOR '(' declaration expression_statement expression ')' statement { $$ = newLoop(FOR_LOOP, $3, $4, $5, $7); }
	;

jump_statement
	: CONTINUE ';' { $$ = newJump(CONTINUE, NULL); }
	/* : GOTO IDENTIFIER ';' */
	| BREAK ';' { $$ = newJump(BREAK, NULL); }
	| RETURN ';' { $$ = newJump(RETURN, NULL); }
	| RETURN expression ';' { $$ = newJump(RETURN, $2); }
	;

translation_unit
	: external_declaration { $$ = $1; }
	| translation_unit external_declaration { $$ = append($1, $2); }
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement { $$ = newFunc(); }
	| declaration_specifiers declarator compound_statement
	;

declaration_list
	: declaration { $$ = $1; }
	| declaration_list declaration { $$ = append($1, $2); }
	;

%%

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}