/*
Parser
Version 1.0
1986 Columbia Union College
By Leroy G. Cain
*/

# include "ddf.h"
# include <stdio.h>
# define U(x) x

static char     *par_buf;
static char     *par_sbuf;

extern char *yysptr, yysbuf[];
extern int yytchar;
extern int yylineno;
extern int ddf_err;

static unsigned char    ptree[4096];
static unsigned char    *ptree_ptr;

parse ( ddf_run, str )
DDFRUN  *ddf_run;
char    *str;
{
register int    preturn;
int     fd;

        par_buf = str;
        par_sbuf = str;
        ptree_ptr = ptree;
        preturn = yyparse();
        ddf_run->par_buf = ptree;
        ddf_run->buf_len = ptree_ptr-ptree;
        return !preturn;
        /*
        if( (preturn=ddf_parser()) && type >0 )
                pcovert(ptree,type);
        return preturn;
        */
}

input()
{
        return
        (
                ( ( yytchar = ( yysptr > yysbuf ? U(*--yysptr) : *par_buf++ )
)
                == 10 ? (yylineno++, yytchar) : yytchar) == '\0' ? 0 :
yytchar
        );
}

unput(c)
int     c;
{
        yytchar = c;
        if (yytchar=='\n') yylineno--;
        *yysptr++ = yytchar;
}

output(c)
int     c;
{
}

parerror(err)
int     err;
{
        ddf_err=err;
}

putvar(s)
char    *s;
{
int     x;

        *ptree_ptr++ = strlen(s);
        for(;*s;*ptree_ptr++ = *s++);
}

putstr(s)
char    *s;
{
int     x;

        *ptree_ptr++ = x = strlen(s)-2;
        *(s+x+1)= '\0';
        for(s++;*s;*ptree_ptr++ = *s++);
}

puttok(n)
int     n;
{
        *ptree_ptr++ = n;
}

putint(s)
char    *s;
{
union
{
        long    num;
        unsigned char   n[4];
} cludge;

        cludge.num = atoi(s);
        *ptree_ptr++ = cludge.n[0];
        *ptree_ptr++ = cludge.n[1];
        *ptree_ptr++ = cludge.n[2];
        *ptree_ptr++ = cludge.n[3];
}

putreal(s)
char    *s;
{
union
{
        double  num;
        unsigned char   n[8];
} cludge;

        cludge.num = atof(s);
        *ptree_ptr++ = cludge.n[0];
        *ptree_ptr++ = cludge.n[1];
        *ptree_ptr++ = cludge.n[2];
        *ptree_ptr++ = cludge.n[3];
        *ptree_ptr++ = cludge.n[4];
        *ptree_ptr++ = cludge.n[5];
        *ptree_ptr++ = cludge.n[6];
        *ptree_ptr++ = cludge.n[7];
}

/* supplied by KMW */

yyerror (s)
char *s;
{
	fprintf (stderr, "%s\n", s);
}
