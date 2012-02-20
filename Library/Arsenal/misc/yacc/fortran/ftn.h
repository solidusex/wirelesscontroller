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


/* some headers for a Fortran parser */

typedef unsigned char uchar;
typedef unsigned short type;	/* stores a Fortran type, high byte type, */
				/* low byte length */

/* binary expression */
typedef struct _binexp {
	type t;
	int expop;
	union _expr *el;
	union _expr *er;
} binexp;

/* Fortran constant */
typedef struct _const {
	type t;
	union {
		long l;
		double d;
		char *c;
	} u;
} constant;

/* name reference */
typedef struct _name {
	type t;
	char name[32];
} name;

/* more or less generic expression */
typedef union _expr {
	struct _binexp b;
	struct _const c;
	struct _name n;
} expr;

/* The Fortran lexical analyzer is very context dependent, here we list the
   various contexts that it knows about.
 */

enum contexts {
	cxt_stmt = 0,	/* beginning of statement */
	cxt_norm,	/* normal in an expression */
	cxt_do,		/* DO stmt seen */
	cxt_type,	/* type seen */
} context;

/* keyword lookup table */
typedef struct _kwdtab {
	char *kwd;	/* text of the keyword */
	int ktok;	/* token code */
	int klex;	/* lexical value */
} kwdtab;


/* types */
#define TY_NONE		0	/* no type */
#define TY_CHAR		1
#define	TY_LOGICAL	2
#define TY_INTEGER	3
#define	TY_REAL		4
#define TY_COMPLEX	5

#define MTYPE(ty, len) ((TY_##ty)<<8|(len))
#define TYTYPE(x) ((x)>>8)	/* type part of a type */
#define TYLEN(x) ((x)&0377)	/* length part of a type */

/* relops */
enum relops {
	rel_eq = 1,
	rel_ne,
	rel_lt,
	rel_le,
	rel_gt,
	rel_ge
};

/* some random stuff */
extern int lineno;


/* some prototypes */
void yyerror(char *);
void emit(int,...);
