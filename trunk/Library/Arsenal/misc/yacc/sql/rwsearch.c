# include <ctype.h>
rwsearch( str )
char    *str;
{
int     x;
int     mid;
int     low=0;
int     high=RWORDS - 1;

        upshift(str);
        while(low <= high)
        {
                mid = (low+high)/2;
                if( !(x=strcmp(str, rwords[mid])) )
                        return(rnums[mid]);
                else if( x<0 ) /* if lesser */
                        high = mid-1;
                else if( x>0 ) /* if greater */
                        low = mid+1;
        }
        return(IDENTIFIER);
}

upshift(str)
char    *str;
{
        for(;*str;str++)
                *str = (isupper(*str))? *str : toupper(*str);
}
