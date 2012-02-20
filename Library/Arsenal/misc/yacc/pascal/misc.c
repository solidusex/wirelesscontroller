#include <stdio.h>


char  *create_string(s)
char	*s;
{
    char *p = (char *) malloc(strlen(s) + 1);
    if(p==NULL) internal_error("Cannot malloc in create-string");
    strcpy(p,s);
    return p;
}

int max(a,b)
int	a,b;
{
    return  a>b ? a : b;
}
