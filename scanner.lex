%{
    /* Declarations Section */
    #include <iostream>
    #include <stdio.h>
    #include "output.hpp"
    #include "parser.tab.hpp"
    extern int yylineno;
    extern char* yytext;
    extern int yylex(); 
    extern void new_table();
    using namespace std;

%}

%option nounput
%option yylineno
%option noyywrap
digit   ([0-9])
letter  ([a-zA-Z])
white_space ([\t\n\r ])
char    ([^\"\r\n\\]|\\\"|\\[\x20-\x7F]|\\\\)
equality (==|!=)
relation (<|>|<=|>=)
binop ([+*/-])
%%

void return VOID;
int return INT;
byte return BYTE;
b return B;
bool return BOOL;
and return AND;
or return OR;
not return NOT;
true return TRUE;
false return FALSE;
return return RETURN;
if {
    new_table();
    return IF;
    }
else {
    new_table();
    return ELSE;
    }
while {new_table();
    return WHILE;}
break return BREAK;
continue return CONTINUE;
switch {return SWITCH;
    }
case return CASE;
default return DEFAULT;
: return COLON;
; return SC;
, return COMMA;
\( return LPAREN;
\) return RPAREN;
\{ {
    new_table();
    return LBRACE;}
\} return RBRACE;
\/\/.* 
{white_space}*
[a-zA-Z][a-zA-Z0-9]* { 
    yylval = new Node();
    yylval->id = yytext;
    //printf((dynamic_cast<Id*>(yylval)->id).c_str()); 
    return ID; }
[1-9]+{digit}* {
    yylval = new Node();
    yylval->value = atol(yytext);
    return NUM; }
0 {
    yylval = new Node();
    yylval->value = 0;
    return NUM; }
\"{char}+\" {
                yylval = new Node();
                yylval->id = yytext;
                return STRING;
                }
{relation} {
    yylval = new Node();
    yylval->type = string(yytext);
    return RELATION;
}
{equality} {
    yylval = new Node();
    yylval->type = string(yytext);
    return EQUALITY;
}
= return ASSIGN;
\+ return ADD;
\- return SUB;
\/ return DIV;
\* return MUL; 
(.|\n) {output::errorLex(yylineno);exit(0);};


%%