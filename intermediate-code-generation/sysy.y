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
    ASTList   list;
}

/* Token 声明 */
%token <id>       IDENTIFIER
%token <intval>   INT_CONST
%token <fval>     FLOAT_CONST
%token            CONST INT FLOAT VOID
%token            IF ELSE WHILE DO FOR BREAK CONTINUE RETURN
%token            LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token            INC_OP DEC_OP RIGHT_OP LEFT_OP

/* 非终结符语义类型声明 */
%type  <ast>      CompUnit Decl ConstDecl VarDecl FuncDef
                  BType ConstDef VarDef ConstInitVal InitVal
                  FuncFParam Block BlockItem Stmt
                  Exp Cond LVal PrimaryExp UnaryExp
                  MulExp AddExp RelExp EqExp LAndExp LOrExp
                  ConstExp FuncType
                  ForStmt ExpOrEmpty CondOrEmpty

%type  <list>     ConstDefList VarDefList ConstInitValList
                  InitValList FuncFParams FuncRParams
                  BlockItemList ExpList ConstExpList

%start CompUnit

%%

/* ==================== */
/* 编译单元             */
/* ==================== */

CompUnit
    : CompUnit Decl
        {
            ASTNode *arr[2] = { $1, ast_ext_decl($2) };
            $$ = ast_compound(arr, 2);
        }
    | CompUnit FuncDef
        {
            ASTNode *arr[2] = { $1, $2 };
            $$ = ast_compound(arr, 2);
        }
    | Decl
        { $$ = ast_ext_decl($1); }
    | FuncDef
        { $$ = $1; }
    ;

/* ==================== */
/* 声明                 */
/* ==================== */

Decl
    : ConstDecl
        { $$ = $1; }
    | VarDecl
        { $$ = $1; }
    ;

ConstDecl
    : CONST BType ConstDefList ';'
        {
            ASTNode *typeNode = $2;
            $$ = ast_decl(&typeNode, 1, $3.items, $3.count);
        }
    ;

ConstDefList
    : ConstDefList ',' ConstDef
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    | ConstDef
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count = 1;
        }
    ;

BType
    : INT
        { $$ = ast_type_name("int"); }
    | FLOAT
        { $$ = ast_type_name("float"); }
    ;

ConstDef
    : IDENTIFIER ConstExpList '=' ConstInitVal
        {
            ASTNode *var = ast_var($1);
            $$ = ast_init_decl(var, $4);
        }
    ;

ConstExpList
    : ConstExpList '[' ConstExp ']'
        {
            $$ = ast_array($1, $3);
        }
    |
        { $$ = NULL; }
    ;

ConstInitVal
    : ConstExp
        { $$ = $1; }
    | '{' ConstInitValList '}'
        { $$ = ast_init_list($2.items, $2.count); }
    | '{' '}'
        { $$ = ast_init_list(NULL, 0); }
    ;

ConstInitValList
    : ConstInitValList ',' ConstInitVal
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    | ConstInitVal
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count = 1;
        }
    ;

VarDecl
    : BType VarDefList ';'
        {
            ASTNode *typeNode = $1;
            $$ = ast_decl(&typeNode, 1, $2.items, $2.count);
        }
    ;

VarDefList
    : VarDefList ',' VarDef
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    | VarDef
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count = 1;
        }
    ;

VarDef
    : IDENTIFIER ConstExpList
        { $$ = ast_init_decl(ast_var($1), NULL); }
    | IDENTIFIER ConstExpList '=' InitVal
        { $$ = ast_init_decl(ast_var($1), $4); }
    ;

InitVal
    : Exp
        { $$ = $1; }
    | '{' InitValList '}'
        { $$ = ast_init_list($2.items, $2.count); }
    | '{' '}'
        { $$ = ast_init_list(NULL, 0); }
    ;

InitValList
    : InitValList ',' InitVal
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    | InitVal
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count = 1;
        }
    ;

/* ==================== */
/* 函数定义             */
/* ==================== */

FuncDef
    : FuncType IDENTIFIER '(' FuncFParams ')' Block
        {
            ASTNode *plist = ast_param_list($4.items, $4.count);
            $$ = ast_func_type($2, plist, $1, $6);
        }
    | FuncType IDENTIFIER '(' ')' Block
        { $$ = ast_func_type($2, NULL, $1, $5); }
    ;

FuncType
    : VOID
        { $$ = ast_type_name("void"); }
    | INT
        { $$ = ast_type_name("int"); }
    | FLOAT
        { $$ = ast_type_name("float"); }
    ;

FuncFParams
    : FuncFParams ',' FuncFParam
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    | FuncFParam
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count = 1;
        }
    ;

FuncFParam
    : BType IDENTIFIER
        {
            ASTNode *specs[1] = { $1 };
            $$ = ast_param(specs, 1, ast_var($2));
        }
    | BType IDENTIFIER '[' ']' ConstExpList
        {
            ASTNode *specs[1] = { $1 };
            ASTNode *arr = ast_array(ast_var($2), NULL);
            $$ = ast_param(specs, 1, arr);
        }
    ;

/* ==================== */
/* 语句块               */
/* ==================== */

Block
    : '{' BlockItemList '}'
        { $$ = ast_compound($2.items, $2.count); }
    | '{' '}'
        { $$ = ast_compound(NULL, 0); }
    ;

BlockItemList
    : BlockItemList BlockItem
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $2;
            $$ = $1;
        }
    | BlockItem
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count = 1;
        }
    ;

BlockItem
    : Decl
        { $$ = $1; }
    | Stmt
        { $$ = $1; }
    ;

/* ==================== */
/* 语句                 */
/* ==================== */

Stmt
    : LVal '=' Exp ';'
        { $$ = ast_assign($1, $3); }
    | ExpOrEmpty ';'
        { $$ = ast_expr_stmt($1); }
    | Block
        { $$ = $1; }
    | IF '(' Cond ')' Stmt
        { $$ = ast_if($3, $5, NULL); }
    | IF '(' Cond ')' Stmt ELSE Stmt
        { $$ = ast_if($3, $5, $7); }
    | WHILE '(' Cond ')' Stmt
        { $$ = ast_while($3, $5); }
    | DO Stmt WHILE '(' Cond ')' ';'
        { $$ = ast_do_while($2, $5); }
    | FOR '(' ForStmt ';' CondOrEmpty ';' ForStmt ')' Stmt
        { $$ = ast_for($3, $5, $7, $9); }
    | BREAK ';'
        { $$ = ast_break(); }
    | CONTINUE ';'
        { $$ = ast_continue(); }
    | RETURN ExpOrEmpty ';'
        { $$ = ast_return($2); }
    ;

ExpOrEmpty
    : Exp
        { $$ = $1; }
    |
        { $$ = NULL; }
    ;

CondOrEmpty
    : Cond
        { $$ = $1; }
    |
        { $$ = NULL; }
    ;

ForStmt
    : ForStmt ',' LVal '=' Exp
        {
            ASTNode *assign = ast_assign($3, $5);
            ASTNode *arr[2] = { $1, assign };
            $$ = ast_compound(arr, 2);
        }
    | LVal '=' Exp
        { $$ = ast_assign($1, $3); }
    ;

/* ==================== */
/* 表达式               */
/* ==================== */

Exp
    : AddExp
        { $$ = $1; }
    ;

Cond
    : LOrExp
        { $$ = $1; }
    ;

LVal
    : IDENTIFIER ExpList
        {
            $$ = ast_var($1);
        }
    ;

ExpList
    : ExpList '[' Exp ']'
        {
            $$ = ast_binop('[', $1, $3);
        }
    |
        { $$ = NULL; }
    ;

PrimaryExp
    : '(' Exp ')'
        { $$ = $2; }
    | LVal
        { $$ = $1; }
    | INT_CONST
        { $$ = ast_int($1); }
    | FLOAT_CONST
        { $$ = ast_double($1); }
    ;

UnaryExp
    : PrimaryExp
        { $$ = $1; }
    | IDENTIFIER '(' FuncRParams ')'
        { $$ = ast_call($1, $3.items, $3.count); }
    | IDENTIFIER '(' ')'
        { $$ = ast_call($1, NULL, 0); }
    | INC_OP UnaryExp
        { $$ = ast_unop('+', $2); }
    | DEC_OP UnaryExp
        { $$ = ast_unop('-', $2); }
    | '+' UnaryExp
        { $$ = $2; }
    | '-' UnaryExp
        { $$ = ast_unop('-', $2); }
    | '!' UnaryExp
        { $$ = ast_unop('!', $2); }
    ;

FuncRParams
    : FuncRParams ',' Exp
        {
            $1.items = realloc($1.items, sizeof(ASTNode*) * ($1.count + 1));
            $1.items[$1.count++] = $3;
            $$ = $1;
        }
    | Exp
        {
            $$.items = malloc(sizeof(ASTNode*));
            $$.items[0] = $1;
            $$.count = 1;
        }
    ;

MulExp
    : UnaryExp
        { $$ = $1; }
    | MulExp '*' UnaryExp
        { $$ = ast_binop('*', $1, $3); }
    | MulExp '/' UnaryExp
        { $$ = ast_binop('/', $1, $3); }
    | MulExp '%' UnaryExp
        { $$ = ast_binop('%', $1, $3); }
    ;

AddExp
    : MulExp
        { $$ = $1; }
    | AddExp '+' MulExp
        { $$ = ast_binop('+', $1, $3); }
    | AddExp '-' MulExp
        { $$ = ast_binop('-', $1, $3); }
    ;

RelExp
    : AddExp
        { $$ = $1; }
    | RelExp '<' AddExp
        { $$ = ast_binop('<', $1, $3); }
    | RelExp '>' AddExp
        { $$ = ast_binop('>', $1, $3); }
    | RelExp LE_OP AddExp
        { $$ = ast_binop('l', $1, $3); }
    | RelExp GE_OP AddExp
        { $$ = ast_binop('g', $1, $3); }
    ;

EqExp
    : RelExp
        { $$ = $1; }
    | EqExp EQ_OP RelExp
        { $$ = ast_binop('e', $1, $3); }
    | EqExp NE_OP RelExp
        { $$ = ast_binop('!', $1, $3); }
    ;

LAndExp
    : EqExp
        { $$ = $1; }
    | LAndExp AND_OP EqExp
        { $$ = ast_binop('&', $1, $3); }
    ;

LOrExp
    : LAndExp
        { $$ = $1; }
    | LOrExp OR_OP LAndExp
        { $$ = ast_binop('|', $1, $3); }
    ;

ConstExp
    : AddExp
        { $$ = $1; }
    ;

%%
/* Error handling */
extern int yylineno;
void yyerror(const char *msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
}
