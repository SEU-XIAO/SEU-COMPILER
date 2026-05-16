%{
#include <iostream>
#include <string>

// Token types
enum TokenType {
    TOK_EOF = 0,
    TOK_INT = 1,
    TOK_VOID = 2,
    TOK_RETURN = 3,
    TOK_IF = 4,
    TOK_ELSE = 5,
    TOK_WHILE = 6,
    TOK_FOR = 7,
    TOK_BREAK = 8,
    TOK_CONTINUE = 9,
    TOK_IDENTIFIER = 100,
    TOK_NUMBER = 101,
    TOK_STRING = 102,
    TOK_CHAR = 103,
    TOK_PLUS = 200,
    TOK_MINUS = 201,
    TOK_MUL = 202,
    TOK_DIV = 203,
    TOK_ASSIGN = 204,
    TOK_EQ = 205,
    TOK_LT = 206,
    TOK_GT = 207,
    TOK_LE = 208,
    TOK_GE = 209,
    TOK_NE = 210,
    TOK_AND = 211,
    TOK_OR = 212,
    TOK_INC = 213,
    TOK_DEC = 214,
    TOK_LPAREN = 300,
    TOK_RPAREN = 301,
    TOK_LBRACE = 302,
    TOK_RBRACE = 303,
    TOK_LBRACKET = 304,
    TOK_RBRACKET = 305,
    TOK_SEMICOLON = 306,
    TOK_COMMA = 307,
    TOK_COMMENT = 400
};

int line_num = 1;
%}

/* Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+\.{DIGIT}*([eE][+-]?{DIGIT}+)?
STRING      L?\"[^\"]*\"
CHAR_CONST  \'[^\']\'

%%

 /* Keywords */
int         { std::cout << "TOK_INT" << std::endl; return TOK_INT; }
void        { std::cout << "TOK_VOID" << std::endl; return TOK_VOID; }
return      { std::cout << "TOK_RETURN" << std::endl; return TOK_RETURN; }
if          { std::cout << "TOK_IF" << std::endl; return TOK_IF; }
else        { std::cout << "TOK_ELSE" << std::endl; return TOK_ELSE; }
while       { std::cout << "TOK_WHILE" << std::endl; return TOK_WHILE; }
for         { std::cout << "TOK_FOR" << std::endl; return TOK_FOR; }
break       { std::cout << "TOK_BREAK" << std::endl; return TOK_BREAK; }
continue    { std::cout << "TOK_CONTINUE" << std::endl; return TOK_CONTINUE; }

 /* Constants */
{STRING}    { std::cout << "TOK_STRING:" << yytext << std::endl; return TOK_STRING; }
{CHAR_CONST}  { std::cout << "TOK_CHAR:" << yytext << std::endl; return TOK_CHAR; }
{FLOAT_CONST} { std::cout << "TOK_NUMBER:" << yytext << std::endl; return TOK_NUMBER; }
{INT_CONST} { std::cout << "TOK_NUMBER:" << yytext << std::endl; return TOK_NUMBER; }

 /* Identifiers (must be after keywords for priority) */
{ID}        { std::cout << "TOK_IDENTIFIER:" << yytext << std::endl; return TOK_IDENTIFIER; }

 /* Operators */
\+\+        { std::cout << "TOK_INC" << std::endl; return TOK_INC; }
--          { std::cout << "TOK_DEC" << std::endl; return TOK_DEC; }
&&          { std::cout << "TOK_AND" << std::endl; return TOK_AND; }
\|\|        { std::cout << "TOK_OR" << std::endl; return TOK_OR; }
<=          { std::cout << "TOK_LE" << std::endl; return TOK_LE; }
>=          { std::cout << "TOK_GE" << std::endl; return TOK_GE; }
==          { std::cout << "TOK_EQ" << std::endl; return TOK_EQ; }
!=          { std::cout << "TOK_NE" << std::endl; return TOK_NE; }
\+          { std::cout << "TOK_PLUS" << std::endl; return TOK_PLUS; }
-           { std::cout << "TOK_MINUS" << std::endl; return TOK_MINUS; }
\*          { std::cout << "TOK_MUL" << std::endl; return TOK_MUL; }
/           { std::cout << "TOK_DIV" << std::endl; return TOK_DIV; }
=           { std::cout << "TOK_ASSIGN" << std::endl; return TOK_ASSIGN; }
<           { std::cout << "TOK_LT" << std::endl; return TOK_LT; }
>           { std::cout << "TOK_GT" << std::endl; return TOK_GT; }

 /* Delimiters */
\(          { std::cout << "TOK_LPAREN" << std::endl; return TOK_LPAREN; }
\)          { std::cout << "TOK_RPAREN" << std::endl; return TOK_RPAREN; }
\{          { std::cout << "TOK_LBRACE" << std::endl; return TOK_LBRACE; }
\}          { std::cout << "TOK_RBRACE" << std::endl; return TOK_RBRACE; }
\[          { std::cout << "TOK_LBRACKET" << std::endl; return TOK_LBRACKET; }
\]          { std::cout << "TOK_RBRACKET" << std::endl; return TOK_RBRACKET; }
;           { std::cout << "TOK_SEMICOLON" << std::endl; return TOK_SEMICOLON; }
,           { std::cout << "TOK_COMMA" << std::endl; return TOK_COMMA; }

 /* Comments */
\/\/[^\n]*              { /* single line comment - ignore */ }
\/\*([^*]|\*+[^/*])*\*+\/  { /* multi-line comment - ignore */ }

 /* Whitespace */
[ \t\n\r]+  { /* ignore whitespace */ }

 /* Error */
.           { std::cerr << "Error: unexpected character '" << yytext << "' at line " << yy_line_num << std::endl; }

%%

int yywrap() {
    return 1;
}
