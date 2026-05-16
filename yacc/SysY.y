%token IDENTIFIER INT_CONST FLOAT_CONST
%token CONST INT FLOAT VOID
%token IF ELSE WHILE DO FOR BREAK CONTINUE RETURN
%token LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token INC_OP DEC_OP

%start CompUnit

%%

CompUnit
    : CompUnit Decl
    | CompUnit FuncDef
    | Decl
    | FuncDef
    ;

Decl
    : ConstDecl
    | VarDecl
    ;

ConstDecl
    : CONST BType ConstDefList ';'
    ;

ConstDefList
    : ConstDefList ',' ConstDef
    | ConstDef
    ;

BType
    : INT
    | FLOAT
    ;

ConstDef
    : IDENTIFIER ConstExpList '=' ConstInitVal
    ;

ConstExpList
    : ConstExpList '[' ConstExp ']'
    |
    ;

ConstInitVal
    : ConstExp
    | '{' ConstInitValList '}'
    | '{' '}'
    ;

ConstInitValList
    : ConstInitValList ',' ConstInitVal
    | ConstInitVal
    ;

VarDecl
    : BType VarDefList ';'
    ;

VarDefList
    : VarDefList ',' VarDef
    | VarDef
    ;

VarDef
    : IDENTIFIER ConstExpList
    | IDENTIFIER ConstExpList '=' InitVal
    ;

InitVal
    : Exp
    | '{' InitValList '}'
    | '{' '}'
    ;

InitValList
    : InitValList ',' InitVal
    | InitVal
    ;

FuncDef
    : FuncType IDENTIFIER '(' FuncFParams ')' Block
    | FuncType IDENTIFIER '(' ')' Block
    ;

FuncType
    : VOID
    | INT
    | FLOAT
    ;

FuncFParams
    : FuncFParams ',' FuncFParam
    | FuncFParam
    ;

FuncFParam
    : BType IDENTIFIER
    | BType IDENTIFIER '[' ']' ConstExpList
    ;

Block
    : '{' BlockItemList '}'
    | '{' '}'
    ;

BlockItemList
    : BlockItemList BlockItem
    | BlockItem
    ;

BlockItem
    : Decl
    | Stmt
    ;

Stmt
    : LVal '=' Exp ';'
    | ExpOrEmpty ';'
    | Block
    | IF '(' Cond ')' Stmt
    | IF '(' Cond ')' Stmt ELSE Stmt
    | WHILE '(' Cond ')' Stmt
    | DO Stmt WHILE '(' Cond ')' ';'
    | FOR '(' ForStmt ';' CondOrEmpty ';' ForStmt ')' Stmt
    | BREAK ';'
    | CONTINUE ';'
    | RETURN ExpOrEmpty ';'
    ;

ExpOrEmpty
    : Exp
    |
    ;

CondOrEmpty
    : Cond
    |
    ;

ForStmt
    : ForStmt ',' LVal '=' Exp
    | LVal '=' Exp
    ;

Exp
    : AddExp
    ;

Cond
    : LOrExp
    ;

LVal
    : IDENTIFIER ExpList
    ;

ExpList
    : ExpList '[' Exp ']'
    |
    ;

PrimaryExp
    : '(' Exp ')'
    | LVal
    | INT_CONST
    | FLOAT_CONST
    ;

UnaryExp
    : PrimaryExp
    | IDENTIFIER '(' FuncRParams ')'
    | IDENTIFIER '(' ')'
    | INC_OP UnaryExp
    | DEC_OP UnaryExp
    | '+' UnaryExp
    | '-' UnaryExp
    | '!' UnaryExp
    ;

FuncRParams
    : FuncRParams ',' Exp
    | Exp
    ;

MulExp
    : UnaryExp
    | MulExp '*' UnaryExp
    | MulExp '/' UnaryExp
    | MulExp '%' UnaryExp
    ;

AddExp
    : MulExp
    | AddExp '+' MulExp
    | AddExp '-' MulExp
    ;

RelExp
    : AddExp
    | RelExp '<' AddExp
    | RelExp '>' AddExp
    | RelExp LE_OP AddExp
    | RelExp GE_OP AddExp
    ;

EqExp
    : RelExp
    | EqExp EQ_OP RelExp
    | EqExp NE_OP RelExp
    ;

LAndExp
    : EqExp
    | LAndExp AND_OP EqExp
    ;

LOrExp
    : LAndExp
    | LOrExp OR_OP LAndExp
    ;

ConstExp
    : AddExp
    ;

%%
