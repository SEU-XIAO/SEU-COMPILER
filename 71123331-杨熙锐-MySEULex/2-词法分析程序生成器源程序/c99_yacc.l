%{
#include <iostream>
#include <string>

// SeuYacc token definitions
#define IDENTIFIER 300
#define CONSTANT 301
#define STRING_LITERAL 302
#define SIZEOF 303
#define PTR_OP 304
#define INC_OP 305
#define DEC_OP 306
#define LEFT_OP 307
#define RIGHT_OP 308
#define LE_OP 309
#define GE_OP 310
#define EQ_OP 311
#define NE_OP 312
#define AND_OP 313
#define OR_OP 314
#define MUL_ASSIGN 315
#define DIV_ASSIGN 316
#define MOD_ASSIGN 317
#define ADD_ASSIGN 318
#define SUB_ASSIGN 319
#define LEFT_ASSIGN 320
#define RIGHT_ASSIGN 321
#define AND_ASSIGN 322
#define XOR_ASSIGN 323
#define OR_ASSIGN 324
#define TYPE_NAME 325
#define TYPEDEF 326
#define EXTERN 327
#define STATIC 328
#define AUTO 329
#define REGISTER 330
#define INLINE 331
#define RESTRICT 332
#define CHAR 333
#define SHORT 334
#define INT 335
#define LONG 336
#define SIGNED 337
#define UNSIGNED 338
#define FLOAT 339
#define DOUBLE 340
#define CONST 341
#define VOLATILE 342
#define VOID 343
#define BOOL 344
#define COMPLEX 345
#define IMAGINARY 346
#define STRUCT 347
#define UNION 348
#define ENUM 349
#define ELLIPSIS 350
#define CASE 351
#define DEFAULT 352
#define IF 353
#define ELSE 354
#define SWITCH 355
#define WHILE 356
#define DO 357
#define FOR 358
#define GOTO 359
#define CONTINUE 360
#define BREAK 361
#define RETURN 362

int line_num = 1;
int col_num = 1;

void printToken(int tokenId, const char* text) {
    printf("%d < %d , %d > %s\x06\n", tokenId, line_num, col_num, text);
}
%}

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+\.{DIGIT}*([eE][+-]?{DIGIT}+)?
STRING      L?\"[^\"]*\"
CHAR_CONST  \'[^\']\'

%%

int         { printToken(INT, "int"); return INT; }
void        { printToken(VOID, "void"); return VOID; }
return      { printToken(RETURN, "return"); return RETURN; }
if          { printToken(IF, "if"); return IF; }
else        { printToken(ELSE, "else"); return ELSE; }
while       { printToken(WHILE, "while"); return WHILE; }
for         { printToken(FOR, "for"); return FOR; }
break       { printToken(BREAK, "break"); return BREAK; }
continue    { printToken(CONTINUE, "continue"); return CONTINUE; }
typedef     { printToken(TYPEDEF, "typedef"); return TYPEDEF; }
extern      { printToken(EXTERN, "extern"); return EXTERN; }
static      { printToken(STATIC, "static"); return STATIC; }
auto        { printToken(AUTO, "auto"); return AUTO; }
register    { printToken(REGISTER, "register"); return REGISTER; }
inline      { printToken(INLINE, "inline"); return INLINE; }
restrict    { printToken(RESTRICT, "restrict"); return RESTRICT; }
char        { printToken(CHAR, "char"); return CHAR; }
short       { printToken(SHORT, "short"); return SHORT; }
long        { printToken(LONG, "long"); return LONG; }
signed      { printToken(SIGNED, "signed"); return SIGNED; }
unsigned    { printToken(UNSIGNED, "unsigned"); return UNSIGNED; }
float       { printToken(FLOAT, "float"); return FLOAT; }
double      { printToken(DOUBLE, "double"); return DOUBLE; }
const       { printToken(CONST, "const"); return CONST; }
volatile    { printToken(VOLATILE, "volatile"); return VOLATILE; }
bool        { printToken(BOOL, "bool"); return BOOL; }
complex     { printToken(COMPLEX, "complex"); return COMPLEX; }
imaginary   { printToken(IMAGINARY, "imaginary"); return IMAGINARY; }
struct      { printToken(STRUCT, "struct"); return STRUCT; }
union       { printToken(UNION, "union"); return UNION; }
enum        { printToken(ENUM, "enum"); return ENUM; }
case        { printToken(CASE, "case"); return CASE; }
default     { printToken(DEFAULT, "default"); return DEFAULT; }
switch      { printToken(SWITCH, "switch"); return SWITCH; }
do          { printToken(DO, "do"); return DO; }
goto        { printToken(GOTO, "goto"); return GOTO; }
sizeof      { printToken(SIZEOF, "sizeof"); return SIZEOF; }

{STRING}    { printToken(STRING_LITERAL, yytext); return STRING_LITERAL; }
{CHAR_CONST}  { printToken(CONSTANT, yytext); return CONSTANT; }
{FLOAT_CONST} { printToken(CONSTANT, yytext); return CONSTANT; }
{INT_CONST} { printToken(CONSTANT, yytext); return CONSTANT; }

{ID}        { printToken(IDENTIFIER, yytext); return IDENTIFIER; }

\+\+        { printToken(INC_OP, "++"); return INC_OP; }
--          { printToken(DEC_OP, "--"); return DEC_OP; }
&&          { printToken(AND_OP, "&&"); return AND_OP; }
\|\|        { printToken(OR_OP, "||"); return OR_OP; }
<=          { printToken(LE_OP, "<="); return LE_OP; }
>=          { printToken(GE_OP, ">="); return GE_OP; }
==          { printToken(EQ_OP, "=="); return EQ_OP; }
!=          { printToken(NE_OP, "!="); return NE_OP; }
->          { printToken(PTR_OP, "->"); return PTR_OP; }
<<          { printToken(LEFT_OP, "<<"); return LEFT_OP; }
>>          { printToken(RIGHT_OP, ">>"); return RIGHT_OP; }
\*=         { printToken(MUL_ASSIGN, "*="); return MUL_ASSIGN; }
/=          { printToken(DIV_ASSIGN, "/="); return DIV_ASSIGN; }
%=          { printToken(MOD_ASSIGN, "%="); return MOD_ASSIGN; }
\+=         { printToken(ADD_ASSIGN, "+="); return ADD_ASSIGN; }
-=          { printToken(SUB_ASSIGN, "-="); return SUB_ASSIGN; }
<<=         { printToken(LEFT_ASSIGN, "<<="); return LEFT_ASSIGN; }
>>=         { printToken(RIGHT_ASSIGN, ">>="); return RIGHT_ASSIGN; }
&=          { printToken(AND_ASSIGN, "&="); return AND_ASSIGN; }
^=          { printToken(XOR_ASSIGN, "^="); return XOR_ASSIGN; }
\|=         { printToken(OR_ASSIGN, "|="); return OR_ASSIGN; }
\(          { printToken(363, "("); return 363; }
\)          { printToken(364, ")"); return 364; }
\{          { printToken(365, "{"); return 365; }
\}          { printToken(366, "}"); return 366; }
\[          { printToken(367, "["); return 367; }
\]          { printToken(368, "]"); return 368; }
;           { printToken(369, ";"); return 369; }
,           { printToken(370, ","); return 370; }
\.          { printToken(371, "."); return 371; }
&           { printToken(372, "&"); return 372; }
\|          { printToken(373, "|"); return 373; }
\^          { printToken(374, "^"); return 374; }
~           { printToken(375, "~"); return 375; }
!           { printToken(376, "!"); return 376; }
\+          { printToken(377, "+"); return 377; }
-           { printToken(378, "-"); return 378; }
\*          { printToken(379, "*"); return 379; }
/           { printToken(380, "/"); return 380; }
%           { printToken(381, "%"); return 381; }
=           { printToken(382, "="); return 382; }
<           { printToken(383, "<"); return 383; }
>           { printToken(384, ">"); return 384; }
\?          { printToken(385, "?"); return 385; }
:           { printToken(386, ":"); return 386; }

\/\/[^\n]*              { /* single line comment - ignore */ }
\/\*([^*]|\*+[^/*])*\*+\/  { /* multi-line comment - ignore */ }

[ \t]+      { col_num += yyleng; }
\n          { line_num++; col_num = 1; }
\r          { /* ignore */ }

.           { fprintf(stderr, "Error: unexpected character '%s' at line %d\n", yytext, line_num); }

%%

int yywrap() {
    return 1;
}