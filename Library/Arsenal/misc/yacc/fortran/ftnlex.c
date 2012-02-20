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

#include "ftn.h"
#include "fparse.h"
#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

extern FILE *ifile;

char stmtbuf[1321];	/* buffer a whole statement */
char linebuf[100];	/* buffer a line at a time */
char *lbcp;		/* start of text in linebuf; */
char *scp;		/* current location in stmtbuf */

long next_stno = -1;	/* statement number for next statement, from pre */
int lineno = 0;
enum contexts context;

/* first, we read in a statement */

/* After each statement is read, the read pointer is at the
   first line of the next statement because we needed to peek ahead and
   see if there was a continuation card.
*/

/* this reads a line, then looks to see if it's a continuation, and if
   not if there's a statement number.
   return values: -1 at EOF, 0 for first line, 1 for continuation */

int
rdstno()
{
	int flg;
	int colno;

	for(;;) {
		register char *cp;

		if(!fgets(linebuf, sizeof(linebuf), ifile))
			return -1;	/* EOF */
		lineno++;
		if(linebuf[0] == 'C' || linebuf[0] == 'c'
			|| linebuf[0] == '*')
			continue;	/* comment */
		/* check for totally blank line */
		/* and trim at column 72 */
		flg = 0;
		for(cp = linebuf, colno = 1; *cp; cp++, colno++) {
			if(*cp == '\n') {
				*cp = 0;
				break;
			}
			if(*cp == '\t' && colno < 5)
				colno = 5;	/* tab ahead */
			else if(*cp != ' ' && *cp != '\t')
				flg = 1;
			if(colno == 72) {
				cp[1] = 0;	/* white out seq cols */
				break;
			}
		}
		if(!flg)
			continue;	/* blank line comment */
		/* now, get the line number and comment flag */
		next_stno = 0;
		colno = 0;
		for(cp = linebuf; colno < 6; cp++, colno++) {
			if(isdigit(*cp))
				next_stno = 10*next_stno + *cp-'0';
			else if(*cp == '\t')
				colno = 5;
			else if(*cp != ' ')
				yyerror("Bad stmt label");
		}
		lbcp = cp;
		cp--;   /* point at continuation marker */
		return(*cp != ' ' && *cp != '\t' && *cp != '0');
	}
} /* rdstno */
		
int stmt_eof;

/* at prescan time quoted strings are pulled out and stashed here */
/* in the scanned statement, the literal string is replaced by a quote
   and a digit indicating which table entry it is */

char *string_tab[30];    /* quoted strings */
char **string_tabp = string_tab;

/* read and prescan a statement, pull out literal strings and squeeze out
   blanks.
   return 1 if statement read, 0 at eof */

int
rdstmt()
{
	char *cp;
	int c;
	int colno;
	int quoteflag = 0;	/* >0 means 3hfoo, -1 means 'foo' */
	int quotable = 0;       /* 1 if nnH allowed */
	char *quotep, *quotelim;
	
	/* make sure there's a line ready for us */
	if(next_stno < 0)
		stmt_eof = rdstno();

	if(stmt_eof < 0)
		return 0;

	/* at this point we might want to do something about the statement
	   number */
	
	/* now read and process lines until we find one that isn't a
	   continuation */
	
	cp = stmtbuf;
	do {
		char *icp;

		for(icp = lbcp; *icp; icp++) {

			c = *icp;
			/* process a card image */
			/* special case for literal strings, keep blanks */
			if(quoteflag) {
				if(quoteflag < 0 && c == '\'') {
					if(icp[1] != '\'') {
						*quotep = 0;
						string_tabp++;
						quoteflag = 0;
						continue;
					} else
						icp++;
				}

				if(quotep >= quotelim)
					yyerror("String too long");
				else
					*quotep++ = (char)c;
				if(quoteflag > 0)
					quoteflag--;
				if(quoteflag == 0) {
					*quotep = 0;
					string_tabp++;
					quoteflag = 0;
				}
				continue;
			}
			/* discard unquoted spaces */
			if(c == ' ' || c == '\t')
				continue;
			
			c = toupper(c);
			/* literal strings can only occur after (  = or / */
			/* consider  REAL*4HELLO */
			if(!quotable && (c == '=' || c == '/' || c == '('))
				quotable++;	/* could have string */

			/* check for quoted literal */
			if(c == '\'') {
				quoteflag = -1;
				*string_tabp = quotep = malloc(80);
				quotelim = quotep + 79;
				*cp++ = '\'';	/* string flag */
				*cp++ = '0'
				  + (string_tabp - string_tab);
				continue;
			}
			*cp = (char)c;
			/* check for counted (hollerith) literal */
			if(c == 'H' && quotable
			 && cp > stmtbuf && isdigit(cp[-1])) {
				char *tcp = cp-1;
				
				while(tcp > stmtbuf && isdigit(*tcp))
					tcp--;
				if(!isalnum(*tcp)) {	/* yes */
					tcp++;
					cp = tcp;	/* back over digs */
					quoteflag = 0;
					while(*tcp != 'H')
						quoteflag = quoteflag*10
							+ *tcp++ - '0';
					
					*string_tabp = quotep
					 = malloc(quoteflag+1);
					quotelim = quotep + quoteflag + 1;
					*cp++ = '\'';	/* string flag */
					*cp++ = '0'
					  + (string_tabp - string_tab);
					continue;
				}
			}
			cp++;
		} /* single line */
	} while((stmt_eof = rdstno()) == 1);
	if(quoteflag) {
		*quotep = 0;
		yyerror("Unterminated string");
	}
	*cp = 0;
	return 1;       /* found something */
} /* rdstmt */

/* prescan to see if this is an arithmetic statement */
/* returns 1 if it's an arithmetic stmt, 0 if not */
/* this hack involves looking for an equal sign not enclosed in parens
   and not followed by a comma not enclosed in parens.  Gross but effective.
 */

prescan()
{
	register char *cp;
	int parencount = 0;
	
	/* scan across counting parens and looking for an = */
	for(cp = scp; ; cp++) {
		switch(*cp) {
	case 0:		return 0;	/* no equal found */

	case '(':	parencount++;
			continue;

	case ')':	if(--parencount == 0) /* foo(a,...) = ... */
				if(cp[1] == '=')
					break;
				else
					return 0;	/* if(foo)... */
			continue;
	
	case '=':	if(parencount == 0)
				break;
	default:
			continue;       /* ignore anything else */
		}
		break;
	}

	/* found an equal, but might be a DO statement */
	/* now look for the comma which tells us it might be a DO loop */
	for(;;cp++) {
		switch(*cp) {
	case '(':	parencount++; break;
	case ')':	parencount--; break;
	case ',':	if(!parencount)
				return 0;
			break;
	case 0:		return 1;	/* it's an arith statement */
		} /* switch */
	} /* for */
} /* prescan */


/* keyword tables */

/* statement starting keywords */
kwdtab tab_stmt[] = {
	{ "CALL",	CALL,	0 },
	{ "COMMON",	COMMON, 0 },
	{ "CONTINUE",	CONTINUE,	0 },
	{ "DATA",	DATA, 0 },
	{ "DIMENSION",	DIMENSION,	0 },
	{ "DO",		DO,	0 },
	{ "ENDIF",	ENDIF,	0 },
	{ "END",	END, 0 },
	{ "ENTRY",	ENTRY,	0 },
	{ "EQUIVALENCE", EQUIVALENCE, 0 },
	{ "EXTERNAL",	EXTERNAL, 0 },
	{ "FORMAT",	FORMAT, 0 },
	{ "FUNCTION",	FUNCTION,	0 },
	{ "GOTO",	GOTO,	0 },
	{ "IF",		IF,	0 },
	{ "IMPLICIT",	IMPLICIT,	0 },
	{ "INTRINSIC",	INTRINSIC, 0 },
	{ "PROGRAM",	PROGRAM,	0 },
	{ "RETURN",	RETURN,	0 },
	{ "REWIND",	REWIND, 0 },
	{ "SAVE",	SAVE, 0 },
	{ "STOP",	STOP,	0 },
	{ "SUBROUTINE",	SUBROUTINE,	0 },
	{ "THEN",	THEN,	0 },
	NULL
};

/* type declarators */
kwdtab tab_type[] = {
	{ "DOUBLEPRECISION",	TYPE,	MTYPE(REAL, 8), },
	{ "REAL*8",	TYPE,	MTYPE(REAL, 8), },
	{ "REAL*4",	TYPE,	MTYPE(REAL, 4), },
	{ "REAL",	TYPE,	MTYPE(REAL, 4), },
	
	{ "INTEGER*4",	TYPE,	MTYPE(INTEGER, 4), },
	{ "INTEGER",	TYPE,	MTYPE(INTEGER, 4), },


	{ "LOGICAL*4",	TYPE,	MTYPE(LOGICAL, 4), },
	{ "LOGICAL",	TYPE,	MTYPE(LOGICAL, 4), },


	{ "DOUBLECOMPLEX",	TYPE,	MTYPE(COMPLEX, 16), },
	{ "COMPLEX*16",	TYPE,	MTYPE(COMPLEX, 16), },
	{ "COMPLEX*8",	TYPE,	MTYPE(COMPLEX, 8), },
	{ "COMPLEX",	TYPE,	MTYPE(COMPLEX, 4), },


	{ "CHARACTER",	TYPE,	MTYPE(CHAR, 1), },
	NULL
};

/* normal tokens */
kwdtab tab_toks[] = {
	{ "+",	PLUS,	0 },
	{ "-",	MINUS,	0 },
	{ "(",	OP,	0 },
	{ ")",	CP,	0 },
	{ "**",	POW,	0 },
	{ "*",	STAR,	0 },
	{ "//",	CAT,	0 },
	{ "/",	DIV,	0 },
	{ ",",	CM,	0 },
	{ "=",	EQ,	0 },
	{ ":",	COLON,	0 },
	{ ".NOT.",	NOT,	0 },
	{ ".AND.",	AND,	0 },
	{ ".OR.",	OR,	0 },
	{ ".EQV.",	EQV, 0 },
	{ ".NEQV.",	EQV, 1 },
	{ ".EQ.",	RELOP,	rel_eq },
	{ ".NE.",	RELOP,	rel_ne },
	{ ".LT.",	RELOP,	rel_lt },
	{ ".LE.",	RELOP,	rel_le },
	{ ".GT.",	RELOP,	rel_gt },
	{ ".GE.",	RELOP,	rel_ge },
	{ ".TRUE.",	CONST,	1 },
	{ ".FALSE.",	CONST,	0 },
	NULL
};


/* call this before parsing a statement */
/* returns 1 if there's a statement to parse */
/* also checks the statement type and sets the context appropriately */
lex0()
{
	if(!rdstmt())
		return 0;	/* EOF */
	scp = stmtbuf;
	if(prescan())
		context = cxt_norm;
	else
		context = cxt_stmt;
	return 1;
}

/* look to see if the next thing is a recognized keyword */
int
keyscan(tab)
register kwdtab *tab;
{
	while(tab->kwd) {
		int len = strlen(tab->kwd);
		
		if(!strncmp(scp, tab->kwd, len)) {
			scp += len;	/* skip over this */
			if(tab->ktok == CONST) {	/* hack */
				yylval.uuexp.c.t = MTYPE(LOGICAL, 4);
				yylval.uuexp.c.u.l = tab->klex;
			} else
			yylval.uuint = tab->klex;
			return tab->ktok;
		}
		tab++;
	}
	return 0;
} /* keyscan */

/* After all this setup, the lexer is quite simple.  It looks for the longest
   keyword legal in the current context or, failing that, for a number or
   name.  The various contexts are mostly set in the parser; the lexer resets
   the context to normal (name, number, or special character token) after
   each token. */

yylex()
 {
	int c;

	if(!*scp)
		return 0;	/* end of statement */

	switch(context) {
	case cxt_stmt:
		c = keyscan(tab_type);
		if(c)
			break;
		c = keyscan(tab_stmt);
		if(c)
			break;
		goto normal;	/* look for normal token */
	default:
		yyerror("Mystery context");
		context = cxt_norm;
	case cxt_norm:
	case cxt_do:
normal:
		c = keyscan(tab_toks);
		if(c)
			break;	/* found something */
		/* check for literal string */
		if(*scp == '\'') {
			char *str;

			c = CONST;
			scp++;
			str = string_tab[*scp++ - '0'];
			yylval.uuexp.c.t = MTYPE(CHAR, strlen(str));
			yylval.uuexp.c.u.c = str;
			break;
		}

		/* must be a number or name */
		if(isalpha(*scp)) {
			char *ocp = yylval.uuexp.n.name;

			yylval.uuexp.n.t = 0;
			while(isalnum(*scp)) {
				*ocp = *scp;
				ocp++;
				scp++;
			}
			*ocp = 0;
			c = NAME;
			break;
		} else {	/* constant */
			int dotseen = 0, expseen = 0;
			int mytype = MTYPE(INTEGER, 4);
			char *sbp;
			char sbuf[50];

			if(!isdigit(*scp) && *scp != '.') {
				yyerror("Unknown character");
				c = 0;
				break;
			}
			sbp = sbuf;
			for(;;) {
				if(isdigit(*scp)) {
					*sbp++ = *scp++;
					continue;
				}
				if(!dotseen && *scp == '.') {
					dotseen++;
					mytype = MTYPE(REAL, 4);
					*sbp++ = *scp++;
					continue;
				}
				if(!expseen && context != cxt_do
				 && (*scp == 'D' || *scp == 'E')) {
					expseen++;
					dotseen++;
					if(*scp == 'D')
						mytype = MTYPE(REAL, 8);
					else
						mytype = MTYPE(REAL, 4);
					*sbp++ = 'E';
					scp++;
					if(*scp == '+')
						scp++;
					else if(*scp == '-')
						*sbp++ = *scp++;
					continue;
				}
				break;  /* end of number */
			} /* for */
			*sbp = 0;
			yylval.uuexp.c.t = mytype;
			if(mytype == MTYPE(INTEGER, 4))
				yylval.uuexp.c.u.l = atol(sbuf);
			else
				yylval.uuexp.c.u.d = atof(sbuf);
			c = CONST;
			break;
		} /* name/const */
	} /* switch */
	context = cxt_norm;
	return c;
} /* yylex */

/* call this to clean up after lexing a statement */
/* It frees the entries in the string table, and emits the statement number
   for the next statement if there is one.
  */
lex1()
{
	while(string_tabp > string_tab)
		free(*--string_tabp);
	if(next_stno)
		emit(1, next_stno);
}
