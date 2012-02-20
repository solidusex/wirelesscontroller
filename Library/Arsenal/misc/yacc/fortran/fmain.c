/*************************************************************************
*                                                                        *
*     Fortran 77 Subset Parser - November 1988                           *
*     Copyright 1988 - John R. Levine.  All rights reserved.             *
*     Permission is hereby granted to make copies in modified or         *
*     unmodified form so long as this copyright notice is preserved      *
*     and such copies are not made for direct commercial advantage.      *
*                                                                        *
*     Any other use such as incorporation in whole or in part in a       *
*     product offered for sale requires separate permission.             *
*                                                                        *
*     John R. Levine                                                     *
*     P.O. Box 349                                                       *
*     Cambridge MA 02238-0349                                            *
*                                                                        *
*     Internet/uucp: Levine@yale.edu    MCI Mail:  103-7498              *
*                                                                        *
*************************************************************************/

/* simple main program that parses a statement at a time and emits Lisp
   expressions corresponding to the parsed tokens.
 */

#include <stdio.h>
#include <stdarg.h>
#include "ftn.h"
#include "fparse.h"

FILE *ifile;
FILE *ofile = stdout;
extern yydebug;

main(ac, av)
char **av;
{
	if(av[1][0] == '-') {
		yydebug++;
		av++;
		ac--;
	}

	ifile = fopen(av[1], "r");
	if(!ifile) {
		perror(av[1]);
		return 1;
	}
	if(ac > 2) {
		ofile = fopen(av[2], "w");
		if(!ofile) {
			perror(av[2]);
			return 1;
		}
	}

	while(lex0()) {		/* prescan a statement */
		yyparse();	/* then parse it */
		lex1();		/* then clean it up */
	}
	return 0;
}

char *relops[] = {
	"???", 	"EQ", "NE", "LT", "LE", "GT", "GE" 
};

/*VARARGS*/
void
emit(int tok,...)
{
	va_list vp;
	int ty;
	char *s;
	
	switch(tok) {
	case 0:		s = ""; break;
	case 1:		s = "STMT"; break;
	case AND:	s = "AND"; break;
	case CALL:	s = "CALL"; break;
	case CAT:	s = "CAT"; break;
	case CCON:	s = "CCON"; break;
	case CM:	s = "CM"; break;
	case COLON:	s = "COLON"; break;
	case COMMON:	s = "COMMON"; break;
	case CONTINUE:	s = "CONTINUE"; break;
	case CP:	s = "CP"; break;
	case DIV:	s = "DIV"; break;
	case DO:	s = "DO"; break;
	case END:	s = "END"; break;
	case EQ:	s = "EQ"; break;
	case EQV:	s = "EQV"; break;
	case FUNCTION:	s = "FUNCTION"; break;
	case GOTO:	s = "GOTO"; break;
	case ICON:	s = "ICON"; break;
	case IF:	s = "IF"; break;
	case MINUS:	s = "MINUS"; break;
	case NAME:	s = "NAME"; break;
	case NOT:	s = "NOT"; break;
	case OP:	s = "OP"; break;
	case OR:	s = "OR"; break;
	case PLUS:	s = "PLUS"; break;
	case POW:	s = "POW"; break;
	case RCON:	s = "RCON"; break;
	case RELOP:	s = "RELOP"; break;
	case RETURN:	s = "RETURN"; break;
	case STAR:	s = "STAR"; break;
	case SUBROUTINE:	s = "SUBROUTINE"; break;
	case TO:	s = "TO"; break;
	case TYPE:	s = "TYPE"; break;
	case UMINUS:	s = "UMINUS"; break;
	default:	s = "???"; break;
	} /* codes */

	fprintf(ofile, "(%s", s);
	
	va_start(vp, tok);
	switch(tok) {
	case FUNCTION:
		ty = va_arg(vp, type);
		s = va_arg(vp, char*);
		fprintf(ofile, " %d %d %s", TYTYPE(ty), TYLEN(ty), s);
		break;
	case CALL:
	case NAME:
	case SUBROUTINE:
	case TO:
		s = va_arg(vp, char*);
		if(!s || !*s)
			s = "Blank";
		fprintf(ofile, " %s", s);
		break;
	case TYPE:
		ty = va_arg(vp, type);
		fprintf(ofile, " %d %d", TYTYPE(ty), TYLEN(ty));
		break;
	case ICON:
	case DO:
	case GOTO:
	case 1:	/* hack for *NNN statement numbers in call statements */
		fprintf(ofile, " %ld", va_arg(vp, long));
		break;
	case CCON:
		fprintf(ofile, " \"%s\"", va_arg(vp, char *));
		break;
	case RCON:
		fprintf(ofile, " %g", va_arg(vp, double));
		break;
	case EQV:
		fprintf(ofile, " %sEQV", va_arg(vp, int)? "N": "");
		break;
	case RELOP:
		fprintf(ofile, " %s", relops[va_arg(vp, int)]);
		break;
	}
	fprintf(ofile, ")\n");
	va_end(vp);
} /* emit */
