#include <ctype.h>
#include <stdio.h>
#include "ddf.h"

int     ddf_err;

main (argc,argv)
int     argc;
char    *argv[];
{
int     x = 0;
FILE    *fd;
char    s[1024];
DDFRUN  partree;

        fd = fopen ("pt_file","w");
        for (printf ("%d>>", x++); getqu (s) && parse (&partree, s) > 0; x++)
        {
                fwrite (partree.par_buf, partree.buf_len, 1, fd);
                printf ("%d>>", x);
        }
}

/*   old version; no longer used
getq(s)
char    *s;
{
        for(; (*s=getchar()) != EOF && *s != ';' ; s++);
        if(*s == EOF )
                return 0;
        else
        {
                *++s = '\0';
                return 1;
        }
}
*/

getqu (s)
char    *s;
{
static int      getqtab [3] [5] =
	{
		{0,1,0,(int)'e',0},
		{1,1,2,1,1},
		{2,0,1,1,1}
	};
int     tk;
int     st = 0;

        *s = '\0';
        while ( (tk = getqt (s)) != EOF )
        {
                if (tk == 3 && !st)
                {
                        return 1;
                }
                else
                        st = getqtab[st] [tk];
        }
        return 0;
}

getqt (s)
char    *s;
{
int     c;
int     value;
char    buf[256];
char    *sbuf=buf;

        if(isspace( (c=getchar()) ))
                value=0;
        else if( isalpha(c))
        {
                for(*buf=(islower(c)) ?toupper(c):c; isalpha( (c=getchar()) )
&&
                        c != EOF ; *++sbuf = (islower(c)) ?toupper(c):c);
                *++sbuf ='\0';
                if(!strcmp(buf,"END"))
                        value=2;
                else if(!strcmp(buf,"STORE"))
                        value=1;
                else
                        value=4;
                ungetc(c,stdin);
                strcat(s,buf);
                return value;
        }
        else if(c==';')
                value=3;
        else if(c == EOF)
                value = EOF;
        else
                value= 4;
        *sbuf = c;
        *++sbuf ='\0';
        strcat(s,buf);
        return value;
}
