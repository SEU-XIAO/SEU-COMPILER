%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYSTYPE int
#include "y.tab.h"

int column = 0;
void count(void);
void comment(void);
%}

D       [0-9]
L       [a-zA-Z_]
H       [a-fA-F0-9]
E       [Ee][+-]?{D}+

%%

"/*"            { comment(); }
"//"[^\n]*      { }

"const"         { count(); return CONST; }
"int"           { count(); return INT; }
"float"         { count(); return FLOAT; }
"void"          { count(); return VOID; }
"if"            { count(); return IF; }
"else"          { count(); return ELSE; }
"while"         { count(); return WHILE; }
"do"            { count(); return DO; }
"for"           { count(); return FOR; }
"break"         { count(); return BREAK; }
"continue"      { count(); return CONTINUE; }
"return"        { count(); return RETURN; }

0[xX]{H}+          { count(); return INT_CONST; }
0[0-7]*            { count(); return INT_CONST; }
[1-9]{D}*          { count(); return INT_CONST; }
{D}+{E}            { count(); return FLOAT_CONST; }
{D}*"."{D}+{E}?   { count(); return FLOAT_CONST; }
{D}+"."{D}*{E}?   { count(); return FLOAT_CONST; }

{L}({L}|{D})*      { count(); return IDENTIFIER; }

">>"    { count(); return RIGHT_OP; }
"<<"    { count(); return LEFT_OP; }
"++"    { count(); return INC_OP; }
"--"    { count(); return DEC_OP; }
"->"    { count(); return PTR_OP; }
"&&"    { count(); return AND_OP; }
"||"    { count(); return OR_OP; }
"<="    { count(); return LE_OP; }
">="    { count(); return GE_OP; }
"=="    { count(); return EQ_OP; }
"!="    { count(); return NE_OP; }

";"     { count(); return ';'; }
"{"     { count(); return '{'; }
"}"     { count(); return '}'; }
","     { count(); return ','; }
":"     { count(); return ':'; }
"="     { count(); return '='; }
"("     { count(); return '('; }
")"     { count(); return ')'; }
"["     { count(); return '['; }
"]"     { count(); return ']'; }
"."     { count(); return '.'; }
"&"     { count(); return '&'; }
"!"     { count(); return '!'; }
"~"     { count(); return '~'; }
"-"     { count(); return '-'; }
"+"     { count(); return '+'; }
"*"     { count(); return '*'; }
"/"     { count(); return '/'; }
"%"     { count(); return '%'; }
"<"     { count(); return '<'; }
">"     { count(); return '>'; }
"^"     { count(); return '^'; }
"|"     { count(); return '|'; }
"?"     { count(); return '?'; }

[ \t\v\n\f]  { count(); }
.              { }

%%

int yywrap(void) {
    return 1;
}

void comment(void) {
    char c, prev = 0;
    while ((c = input()) != 0) {
        if (c == '/' && prev == '*')
            return;
        prev = c;
    }
    fprintf(stderr, "unterminated comment\n");
}

void count(void) {
    int i;
    for (i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n')
            column = 0;
        else if (yytext[i] == '\t')
            column += 8 - (column % 8);
        else
            column++;
    }
    ECHO;
}
