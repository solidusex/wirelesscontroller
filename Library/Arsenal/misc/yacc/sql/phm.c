#include <stdio.h>

main()
{
char	st[256];
char	j0, j1[32];
char	token[32];
int	num;
int	n=0;
FILE	*words;
FILE	*nums;

	words=fopen("rwords","w");
	nums=fopen("rnums","w");
	while ( gets(st)!=NULL)
	{
		sscanf(st,"%c %s %s %d ",&j0,j1,token,&num);
		fprintf(words,"\"%s\"%s",token,(n==5)? ",\n": ", ");
		fprintf(nums,"%d%s",num,(n==5)? ",\n": ", ");
		n=(n==5) ? 0 : ++n;
	}
	fprintf(words,"\n");
	fprintf(nums,"\n");
	exit(0);
}
