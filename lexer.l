%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"
    void yyerror(const char *);
%}

%x c_comments
number                  [1-9][0-9]*|0
name                    [a-zA-Z][a-zA-Z0-9]*

%%
"/*"                    { BEGIN(c_comments); }

"boolean"               { return t_bool_type; }
"integer"               { return t_int_type; }
"none"                  { return t_none_type; }
"print"                 { return t_print; }
"return"                { return t_return; }
"if"                    { return t_if; }
"else"                  { return t_else; }
"while"                 { return t_while; }
"new"                   { return t_new; }
"equals"                { return t_equals; }
"and"                   { return t_and; }
"or"                    { return t_or; }
"not"                   { return t_not; }
"true"                  { return t_true; }
"false"                 { return t_false; }
"extends"               { return t_extends; }
"do"                    { return t_do; }

">="                    { return t_geq; }
"->"                    { return t_arrow; }
";"                     { return ';'; }
","                     { return ','; }
"("                     { return '('; }
")"                     { return ')'; }
"}"                     { return '}'; }
"{"                     { return '{'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
">"                     { return '>'; }
"="                     { return '='; }

{name}                  { yylval.base_char_ptr = strdup(yytext); return t_id; }
{number}"."[0-9]+       { yylval.base_int = atoi(yytext); return t_number; }
{number}                { yylval.base_int = atoi(yytext); return t_number; }
"."                     { return '.'; }

<c_comments>"*/"        { BEGIN(INITIAL); }
<c_comments><<EOF>>     { yyerror("dangling comment"); }
<c_comments>[ \t\n]+    { /* do nothing */ }
<c_comments>.           { /* do nothing */ }

[ \t\n]+                { /* do nothing */ }

.                       { yyerror("invalid character"); }

%%
int yywrap(void) {
  return 1;
}
