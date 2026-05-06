%define parse.error verbose

%code requires {
	#include "ast.h"

	typedef struct {
		ASTNode **items;
		int       count;
  	} ASTList;

	extern ASTNode *ast_root;
}

%{#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
void yyerror(const char *msg);
%}

/* 联合体：所有语义值类型 */
%union {
    int       intval;
    float     fval;
    char     *id;
    ASTNode  *ast;
    ASTList   list;   /* 仅此一种列表类型 */
}

/* Token 声明 */
%token <id>       IDENTIFIER
%token <intval>   CONSTANT
%token <fval>     DCONSTANT
%token            PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP
%token            LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token            INT DOUBLE VOID
%token            IF ELSE WHILE DO FOR CONTINUE BREAK RETURN

/* 非终结符语义类型声明 */
%type  <ast>      primary_expression postfix_expression
                  unary_expression cast_expression
                  multiplicative_expression additive_expression
                  shift_expression relational_expression
                  equality_expression and_expression
                  exclusive_or_expression inclusive_or_expression
                  logical_and_expression logical_or_expression
                  conditional_expression assignment_expression
                  expression declaration declaration_specifiers
                  init_declarator declarator direct_declarator
                  parameter_declaration abstract_declarator
                  direct_abstract_declarator initializer
                  statement compound_statement
                  block_item expression_statement
                  selection_statement iteration_statement
                  jump_statement external_declaration
                  function_definition translation_unit type_specifier

%type  <list>     argument_expression_list init_declarator_list
                  parameter_list parameter_type_list
                  identifier_list initializer_list
                  block_item_list

%start translation_unit

%%

/* ---------------------------- */
/* Primary & Postfix Expressions */
/* ---------------------------- */

primary_expression
    : IDENTIFIER
        { $$ = ast_var($1); }
    | CONSTANT
        { $$ = ast_int($1); }
    | DCONSTANT
        { $$ = ast_double($1); }
    | '(' expression ')'
        { $$ = $2; }
    ;

postfix_expression
    : primary_expression
        { $$ = $1; }
    | postfix_expression '[' expression ']'
        { $$ = ast_binop('[', $1, $3); }
    | postfix_expression '(' ')'
        { $$ = ast_call($1->varname.c_str(), NULL, 0); }
    | postfix_expression '(' argument_expression_list ')'
        {
            $$ = ast_call($1->varname.c_str(),
                          $3.items,
                          $3.count);
        }
    | postfix_expression '.' IDENTIFIER
        { $$ = ast_binop('.', $1, ast_var($3)); }
    | postfix_expression PTR_OP IDENTIFIER
        { $$ = ast_binop('>', $1, ast_var($3)); }
    | postfix_expression INC_OP
        { $$ = ast_unop('+', $1); }
    | postfix_expression DEC_OP
        { $$ = ast_unop('-', $1); }
    ;

/* ---------------------------- */
/* Argument Expression List      */
/* ---------------------------- */

argument_expression_list
    : assignment_expression
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count    = 1;
        }
    | argument_expression_list ',' assignment_expression
        {
            /* $1 是 ASTList */
            $1.items = realloc($1.items,
                               sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count] = $3;
            $1.count++;
            $$ = $1;
        }
    ;

/* ---------------------------- */
/* Unary / Cast / Binary        */
/* ---------------------------- */

unary_expression
    : postfix_expression
        { $$ = $1; }
    | INC_OP unary_expression
        { $$ = ast_unop('+', $2); }
    | DEC_OP unary_expression
        { $$ = ast_unop('-', $2); }
    | '&' cast_expression
        { $$ = ast_unop('&', $2); }
    | '*' cast_expression
        { $$ = ast_pointer($2); }
    | '+' cast_expression
        { $$ = $2; }
    | '-' cast_expression
        { $$ = ast_unop('-', $2); }
    | '~' cast_expression
        { $$ = ast_unop('~', $2); }
    | '!' cast_expression
        { $$ = ast_unop('!', $2); }
    ;

cast_expression
    : unary_expression
        { $$ = $1; }
    ;

multiplicative_expression
    : cast_expression
        { $$ = $1; }
    | multiplicative_expression '*' cast_expression
        { $$ = ast_binop('*', $1, $3); }
    | multiplicative_expression '/' cast_expression
        { $$ = ast_binop('/', $1, $3); }
    | multiplicative_expression '%' cast_expression
        { $$ = ast_binop('%', $1, $3); }
    ;

additive_expression
    : multiplicative_expression
        { $$ = $1; }
    | additive_expression '+' multiplicative_expression
        { $$ = ast_binop('+', $1, $3); }
    | additive_expression '-' multiplicative_expression
        { $$ = ast_binop('-', $1, $3); }
    ;

shift_expression
    : additive_expression
        { $$ = $1; }
    | shift_expression LEFT_OP additive_expression
        { $$ = ast_binop('<', $1, $3); }
    | shift_expression RIGHT_OP additive_expression
        { $$ = ast_binop('>', $1, $3); }
    ;

relational_expression
    : shift_expression
        { $$ = $1; }
    | relational_expression '<' shift_expression
        { $$ = ast_binop('<', $1, $3); }
    | relational_expression '>' shift_expression
        { $$ = ast_binop('>', $1, $3); }
    | relational_expression LE_OP shift_expression
        { $$ = ast_binop('l', $1, $3); }
    | relational_expression GE_OP shift_expression
        { $$ = ast_binop('g', $1, $3); }
    ;

equality_expression
    : relational_expression
        { $$ = $1; }
    | equality_expression EQ_OP relational_expression
        { $$ = ast_binop('e', $1, $3); }
    | equality_expression NE_OP relational_expression
        { $$ = ast_binop('!', $1, $3); }
    ;

and_expression
    : equality_expression
        { $$ = $1; }
    | and_expression '&' equality_expression
        { $$ = ast_binop('&', $1, $3); }
    ;

exclusive_or_expression
    : and_expression
        { $$ = $1; }
    | exclusive_or_expression '^' and_expression
        { $$ = ast_binop('^', $1, $3); }
    ;

inclusive_or_expression
    : exclusive_or_expression
        { $$ = $1; }
    | inclusive_or_expression '|' exclusive_or_expression
        { $$ = ast_binop('|', $1, $3); }
    ;

logical_and_expression
    : inclusive_or_expression
        { $$ = $1; }
    | logical_and_expression AND_OP inclusive_or_expression
        { $$ = ast_binop('&', $1, $3); }
    ;

logical_or_expression
    : logical_and_expression
        { $$ = $1; }
    | logical_or_expression OR_OP logical_and_expression
        { $$ = ast_binop('|', $1, $3); }
    ;

conditional_expression
    : logical_or_expression
        { $$ = $1; }
    ;

/* ---------------------------- */
/* Assignment & Expression List */
/* ---------------------------- */

assignment_expression
    : conditional_expression
        { $$ = $1; }
    | unary_expression '=' assignment_expression
        { $$ = ast_assign($1, $3); }
    ;

expression
    : assignment_expression
        { $$ = $1; }
    | expression ',' assignment_expression
        {
            ASTNode *arr[2] = { $1, $3 };
            $$ = ast_compound(arr, 2);
        }
    ;

/* ---------------------------- */
/* Declarations & Types         */
/* ---------------------------- */

declaration
    : declaration_specifiers ';'
        {
            $$ = ast_decl($1->ds.specs, $1->ds.scount, NULL, 0);
        }
    | declaration_specifiers init_declarator_list ';'
        {
            $$ = ast_decl($1->ds.specs,
                          $1->ds.scount,
                          $2.items,
                          $2.count);
        }
    ;

declaration_specifiers
    : type_specifier
        {
            ASTNode **a = malloc(sizeof(ASTNode*));
            a[0] = $1;
            $$ = ast_decl_spec(a, 1);
        }
    | declaration_specifiers type_specifier
        {
            $1->ds.specs = realloc($1->ds.specs,
                                   sizeof(ASTNode*) * ($1->ds.scount + 1));
            $1->ds.specs[$1->ds.scount++] = $2;
            $$ = $1;
        }
    ;

/* Init-declarator 列表 */
init_declarator_list
    : init_declarator
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count    = 1;
        }
    | init_declarator_list ',' init_declarator
        {
            $1.items = realloc($1.items,
                               sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    ;

init_declarator
    : declarator
        { $$ = ast_init_decl($1, NULL); }
    | declarator '=' initializer
        { $$ = ast_init_decl($1, $3); }
    ;

/* Type-specifier */
type_specifier
    : VOID    { $$ = ast_type_name("void"); }
    | INT     { $$ = ast_type_name("int"); }
    | DOUBLE  { $$ = ast_type_name("double"); }
    ;

/* Declarators & Direct-declarators */
declarator
    : '*' declarator
        { $$ = ast_pointer($2); }
    | direct_declarator
        { $$ = $1; }
    ;

direct_declarator
    : '(' declarator ')'
        { $$ = $2; }
    | direct_declarator '[' assignment_expression ']'
        { $$ = ast_array($1, $3); }
    | direct_declarator '[' '*' ']'
        { $$ = ast_array($1, NULL); }
    | direct_declarator '[' ']'
        { $$ = ast_array($1, NULL); }
    | direct_declarator '(' parameter_type_list ')'
        {
            ASTNode *plist = ast_param_list($3.items, $3.count);
            $$ = ast_func_type($1->varname.c_str(), plist, NULL, NULL);
        }
    | direct_declarator '(' identifier_list ')'
        { $$ = ast_func_type($1->varname.c_str(), NULL, NULL, NULL); }
    | direct_declarator '(' ')'
        { $$ = ast_func_type($1->varname.c_str(), NULL, NULL, NULL); }
    | IDENTIFIER
        { $$ = ast_var($1); }
    ;
/* Parameter-type-list & parameter-list */
parameter_type_list
    : parameter_list
        { 
			$$.items = $1.items;
			$$.count = $1.count;
		}
    ;

parameter_list
    : parameter_declaration
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count    = 1;
        }
    | parameter_list ',' parameter_declaration
        {
            $1.items = realloc($1.items,
                               sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    ;

parameter_declaration
    : declaration_specifiers declarator
        { $$ = ast_param($1->ds.specs, $1->ds.scount, $2); }
    | declaration_specifiers abstract_declarator
        { $$ = ast_param($1->ds.specs, $1->ds.scount, $2); }
    | declaration_specifiers
        { $$ = ast_param($1->ds.specs, $1->ds.scount, NULL); }
    ;

/* Identifier-list */
identifier_list
    : IDENTIFIER
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = ast_var($1);
            $$.count    = 1;
        }
    | identifier_list ',' IDENTIFIER
        {
            $1.items = realloc($1.items,
                               sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = ast_var($3);
            $$ = $1;
        }
    ;

/* Abstract declarators */
abstract_declarator
    : '*'
        { $$ = ast_pointer(NULL); }
    | direct_abstract_declarator
        { $$ = $1; }
    | '*' direct_abstract_declarator
        { $$ = ast_pointer($2); }
    ;

direct_abstract_declarator
    : '(' abstract_declarator ')'
        { $$ = $2; }
    | '[' ']'
        { $$ = ast_array(NULL, NULL); }
    | '[' assignment_expression ']'
        { $$ = ast_array(NULL, $2); }
    | direct_abstract_declarator '[' ']'
        { $$ = ast_array($1, NULL); }
    | direct_abstract_declarator '[' assignment_expression ']'
        { $$ = ast_array($1, $3); }
    | '[' '*' ']'
        { $$ = ast_array(NULL, NULL); }
    | direct_abstract_declarator '[' '*' ']'
        { $$ = ast_array($1, NULL); }
    | '(' ')'
        { $$ = ast_func_type(NULL, NULL, NULL, NULL); }
    | '(' parameter_type_list ')'
        { $$ = ast_func_type(NULL, ast_param_list($2.items, $2.count), NULL, NULL); }
    | direct_abstract_declarator '(' ')'
        { $$ = ast_func_type(NULL, NULL, NULL, NULL); }
    | direct_abstract_declarator '(' parameter_type_list ')'
        { $$ = ast_func_type(NULL, ast_param_list($3.items, $3.count), NULL, NULL); }
    ;

/* Initializers & Initializer-list */
initializer
    : assignment_expression
        { $$ = $1; }
    | '{' initializer_list '}'
        { $$ = ast_init_list($2.items, $2.count); }
    | '{' initializer_list ',' '}'
        { $$ = ast_init_list($2.items, $2.count); }
    ;

initializer_list
    : initializer
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count    = 1;
        }
    | initializer_list ',' initializer
        {
            $1.items = realloc($1.items,
                               sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    ;

/* Statements */
statement
    : IDENTIFIER ':' statement     { $$ = ast_expr_stmt(NULL); }
    | compound_statement           { $$ = $1; }
    | expression_statement         { $$ = $1; }
    | selection_statement          { $$ = $1; }
    | iteration_statement          { $$ = $1; }
    | jump_statement               { $$ = $1; }
    ;

compound_statement
    : '{' '}'                      { $$ = ast_compound(NULL, 0); }
    | '{' block_item_list '}'      { $$ = ast_compound($2.items, $2.count); }
    ;

block_item_list
    : block_item
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count    = 1;
        }
    | block_item_list block_item
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $2;
            $$ = $1;
        }
    ;

block_item
    : declaration                   { $$ = $1; }
    | statement                     { $$ = $1; }
    ;

expression_statement
    : ';'                           { $$ = ast_expr_stmt(NULL); }
    | expression ';'                { $$ = ast_expr_stmt($1); }
    ;

selection_statement
    : IF '(' expression ')' statement
        { $$ = ast_if($3, $5, NULL); }
    | IF '(' expression ')' statement ELSE statement
        { $$ = ast_if($3, $5, $7); }
    ;

iteration_statement
    : WHILE '(' expression ')' statement
        { $$ = ast_while($3, $5); }
    | DO statement WHILE '(' expression ')' ';'
        { $$ = ast_do_while($2, $5); }
    | FOR '(' expression_statement expression_statement ')' statement
        { $$ = ast_for($3, $4, NULL, $6); }
    | FOR '(' expression_statement expression_statement expression ')' statement
        { $$ = ast_for($3, $4, $5, $7); }
    | FOR '(' declaration expression_statement ')' statement
        { $$ = ast_for(ast_ext_decl($3), $4, NULL, $6); }
    | FOR '(' declaration expression_statement expression ')' statement
        { $$ = ast_for(ast_ext_decl($3), $4, $5, $7); }
    ;

jump_statement
    : CONTINUE ';'                  { $$ = ast_continue(); }
    | BREAK ';'                     { $$ = ast_break(); }
    | RETURN ';'                    { $$ = ast_return(NULL); }
    | RETURN expression ';'         { $$ = ast_return($2); }
    ;

/* External Declarations & Translation Unit */
external_declaration
    : function_definition           { $$ = ast_ext_decl($1); }
    | declaration                   { $$ = ast_ext_decl($1); }
    ;

function_definition
    : declaration_specifiers declarator compound_statement
        {
            if ($2->type == AST_FUNC_TYPE) {
                $2->ft.ret_type = $1->ds.specs[0];
                $2->ft.body = $3;
                $$ = $2;
            } else {
                yyerror("Expected function declarator");
                $$ = NULL;
            }
        }
    ;

translation_unit
    : external_declaration
        {
            ASTNode **a = malloc(sizeof(ASTNode*));
            a[0] = $1;
            ast_root = ast_trans_unit(a, 1);
        }
    | translation_unit external_declaration
        {
            int old = ast_root->seq.count;
            ast_root->seq.list = realloc(ast_root->seq.list,
                                         sizeof(ASTNode*) * (old + 1));
            ast_root->seq.list[old] = $2;
            ast_root->seq.count++;
        }
    ;

%%
/* Error handling & main */
extern int yylineno;
void yyerror(const char *msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
}