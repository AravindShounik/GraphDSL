/* %token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN */


%union {
    int  info;
    long ival;
    double fval;
    char* text;
    bool bval;
    ast_node* ptr;
    expr_list* e_list;  // list of expressions
    lhs_list* l_list;   // list of lhs
    struct parse_temp_t pair;
}

%token T_PROC T_GRAPH T_NODE T_NODEPROP T_EDGE T_EDGEPROP T_LOCAL
%token T_NSET T_NORDER T_NSEQ T_ITEMS T_COLLECTION
%token T_MAP
%token T_DFS T_POST 
%token T_INT T_FLOAT T_BOOL T_DOUBLE  T_LONG
%token T_RETURN
%token T_BFS  T_RBFS T_FROM T_TO T_BACK
%token T_FOREACH T_FOR 
%token T_NODES T_EDGES T_NBRS T_IN_NBRS T_UP_NBRS T_DOWN_NBRS
%token T_COMMON_NBRS;
%token T_SUM T_PRODUCT T_MIN T_MAX T_COUNT T_ALL T_EXIST T_AVG
%token T_EMPTYLINE
%token T_AND T_OR T_EQ T_NEQ T_LE T_GE
%token T_IF  T_ELSE T_DO T_WHILE
%token T_PLUSEQ T_MULTEQ T_MINEQ T_MAXEQ T_PLUSPLUS T_MINUSMINUS T_ANDEQ T_OREQ
%token T_M_INF T_P_INF
%token T_DOUBLE_COLON T_RARROW
%token T_NIL

%token <text> ID
%token <text> USER_TEXT
%token <ival> INT_NUM
%token <fval> FLOAT_NUM
%token <bval> BOOL_VAL


%type <bval> opt_tp foreach_dir
%type <ptr> id lhs rhs expr bool_expr numeric_expr
%type <ptr> sent sent_block  sent_assignment sent_variable_decl sent_foreach sent_if 
%type <pair> foreach_header foreach_src
%type <pair> rhs_list2 lhs_list2
%type <ptr> foreach_filter
%type <ptr> sent_do_while sent_while sent_return sent_call
%type <ptr> sent_reduce_assignment  sent_defer_assignment
%type <ptr> sent_bfs bfs_filter bfs_navigator sent_dfs
%type <pair> bfs_reverse bfs_filters dfs_post
%type <ival> from_or_semi
%type <ptr> arg_decl typedecl property prim_type graph_type arg_target var_target
%type <ptr> edge_type node_type nodeedge_type set_type optional_bind key_type value_type map_type
%type <ptr> scala field map_access
%type <ptr> sent_argminmax_assignment
%type <pair>  iterator1
%type <ival> reduce_eq
%type <ival> reduce_op reduce_op2
%type <ival> minmax_eq
%type <bval> inf
%type <ptr>  built_in
%type <pair> bfs_header_format
%type <e_list>  arg_list expr_list 
%type <l_list>  lhs_list
%type <ptr>  expr_user sent_user

 /* operator precedence
  * Lower is higher
  */
%left '?'
%left ':'
%left T_OR
%left T_AND 
%left T_EQ T_NEQ
%left '<' '>'  T_LE T_GE
%left '+' '-'
%left '*' '/' '%'
%right NEG

%glr-parser 

%start translation_unit
%%

/* primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
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
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
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
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST
	| VOLATILE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
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
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	; */

typedecl    : prim_type
            | graph_type
            | property
            | nodeedge_type
            | set_type
            | map_type	
            ;		   

graph_type  : T_GRAPH 
            ;

property   : T_NODEPROP '<' prim_type ',' id '>'
           | T_NODEPROP '<' nodeedge_type ','  id '>'  
           | T_NODEPROP '<' set_type ',' id '>'
           | T_NODEPROP '<' prim_type '>' 
           | T_NODEPROP '<' nodeedge_type '>'  
           | T_NODEPROP '<' set_type '>'

           | T_EDGEPROP '<' prim_type ',' id '>'  
           | T_EDGEPROP '<' nodeedge_type ',' id '>'
           | T_EDGEPROP '<' set_type ','id '>' 
           | T_EDGEPROP '<' prim_type '>' 
           | T_EDGEPROP '<' nodeedge_type '>' 
           | T_EDGEPROP '<' set_type '>' 
           ;
/* 
iterator1   : T_NODES   
            | T_EDGES 
            | T_NBRS                        
            ;   */
sent_dfs   : T_DFS bfs_header_format bfs_filters sent_block dfs_post
;
              // GM_bfs(it, src,root,             (navigator, f_filter,b_filter), fw,bw,  tp)
sent_bfs    : T_BFS bfs_header_format bfs_filters sent_block bfs_reverse 
                ;
/* dfs_post     :                               
               | T_POST bfs_filter sent_block   
               | T_POST sent_block             
;
bfs_reverse  :                               
               | T_BACK bfs_filter sent_block  
               | T_BACK sent_block             
;*/

bfs_header_format :  '(' id ':' id opt_tp '.' T_NODES from_or_semi id ')'
; 
opt_tp       :                            
               | '^'                      
;
from_or_semi : T_FROM                
               | ';'                
;

/* bfs_filters   :                             
              |  bfs_navigator              
              |  bfs_filter                 
              |  bfs_navigator bfs_filter   
              |  bfs_filter bfs_navigator   

bfs_navigator :  '[' expr ']'                                          */

  /* bfs_filter  : '(' expr ')' */
%%
#include <stdio.h>

extern char yytext[];
extern int column;

int main()
{
    yyparse();
    return 1;
}

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}