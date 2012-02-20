/*
Distributed data base Facilitator
Parser
Version 1.0
Copyright 1986 Columbia Union College
By Leroy G. Cain
*/
%{
#include "string.h"
#include "parser.h"
#include "rwsearch.c"
%}
D       [0-9]
E       [Ee][-+]?{D}+
%%
[a-zA-Z]+   
{
int     rw;

        if((rw= rwsearch(yytext)) == IDENTIFIER )
        {
                yylval.nsbuf = strcpy(scratch,yytext);
        }
                return rw;
}

"$"[a-zA-Z_][a-zA-Z0-9_#@]* return( PARM );

[a-zA-Z_][a-zA-Z0-9_#@]* {   
	yylval.nsbuf = strcpy (scratch, yytext);   /* KMW */
	return IDENTIFIER ;
}

\"[^\"]*        |
\'[^\']*        
{
        if(yytext[yyleng-1] ==  '\\')
                yymore();
        else
        {
                yytext[yyleng++] = input();
                yytext[yyleng] = '\0';
                return( STRING );
        }
}

{D}+    return ( INTEGER );

{D}+"."{D}*({E})?       |
{D}+"."{D}+({E})?       |
{D}+{E} return ( REAL );

":"     return ':' ;
";"     return ';' ;
".*"    return ALLFIELDS ;
"."     return '.' ;
","     return ',' ;
"!"     return NOT ;
"!="    return NE ;
"<="    return LE ;
">="    return GE ;
"<"     return LT ;
"!<"    return NLT ;
">"     return GT ;
"!>"    return NGT ;
"("     return '(' ;
")"     return ')' ;
">>"    return RIGHTSHIFT ;
"<<"    return LEFTSHIFT ;
"|"     return '|' ; /* Bit or */
"||"    return E_OR ; /* or */
"^"     return '^' ; /* Bit ex-or */
"&"     return '&' ; /* Bit and */
"&&"    return E_AND ; /* and */
"~"     return '~' ; /* Ones compliment */
"`"     return '`' ; /* Sematic control */
"]"     return ']' ;
"["     return '[' ;
"="     return EQ ;
"+"     return '+' ;
"-"     return '-' ;
"*"     return '*' ;
"**"    return PWR ;
"/"     return '/' ;
"%"     return '%' ; /* Modulus */
"?"     return '?' ;
[/] return( ILLEGAL );
[ \n\t\r] ;
%%
