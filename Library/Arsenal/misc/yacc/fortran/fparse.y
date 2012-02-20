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


%{
#include "ftn.h"
%}
%union {
	expr uuexp;
	long uulong;
	int uuint;
	type uutype;
}
/* generic tokens */
%token PLUS MINUS OP CP STAR POW DIV CAT CM EQ COLON
%token NOT AND OR
%token <uuint> RELOP EQV
%token <uuexp> NAME CONST ICON RCON LCON CCON

/* a zillion keywords */
%token IF THEN ELSE ELSEIF ENDIF DO GOTO ASSIGN TO CONTINUE STOP
%token <uuint> RDWR
%token OPEN CLOSE BACKSPACE REWIND ENDFILE FORMAT
%token PROGRAM FUNCTION SUBROUTINE ENTRY END CALL RETURN
%token <uutype> TYPE DIMENSION
%token COMMON EQUIVALENCE EXTERNAL PARAMETER INTRINSIC IMPLICIT
%token SAVE DATA

%left EQV
%left OR
%left AND
%nonassoc NOT
%nonassoc RELOP
%left CAT
%left PLUS MINUS
%left STAR DIV
%right POW
%nonassoc UMINUS

%type <uutype> opttype

%%

statement:	s	{ emit(0); }
	;

s:		PROGRAM NAME
	;

s:		opttype FUNCTION NAME { emit(FUNCTION, $1, $3.n.name); }
			OP funargs CP
	;

opttype:	/* empty */ { $$ = 0; }
	|	TYPE
	;

funargs:	funarg
	|	funargs CM funarg
	;

funarg:		NAME	{ emit(NAME, $1.n.name); }
	|	STAR	{ emit(STAR); }
	;

s:		ENTRY NAME
	|	ENTRY NAME OP funargs CP
	;

s:		SUBROUTINE NAME { emit(SUBROUTINE, $2.n.name); }
	|	SUBROUTINE NAME { emit(SUBROUTINE, $2.n.name); }
			OP funargs CP
	;

/* we give dimension and explicit type statements the same syntax here
   because I'm lazy.  This allows e.g. 
	   DIMENSION FOO
   which is easier to kick out semantically
 */

s:		DIMENSION { emit(TYPE, 0); } arydcllist
	|	TYPE { emit(TYPE, $1); } arydcllist
	;

arydcllist:	arydcl
	|	arydcllist CM arydcl
	;

arydcl:		NAME { emit(NAME, $1.n.name); } OP dclsublist CP
		{ emit(CP); }
	|	NAME { emit(NAME, $1.n.name); emit(CP); }
	;

dclsublist:	dclsub
	|	dclsublist CM { emit(CP); } dclsub
	;

dclsub:		exp
	|	exp COLON { emit(COLON); } exp
	|	STAR
	|	exp COLON STAR { emit(COLON); emit(STAR); }
	;

s:		COMMON { emit(COMMON); } commonlist
	;

commonlist:	arydcl
	|	commonlist CM arydcl
	|	blockname
	|	commonlist optcomma blockname
	;

optcomma:	CM
	|	/* nothing */
	;

/* note here that the // for blank common looks a lot like the catenation
   operator.  Fortunately, there's no semantic ambiguity */

blockname:	DIV NAME DIV { emit(TO, $2.n.name); }
	|	CAT { emit(TO, ""); }	/* blank common */
	;

s:		EQUIVALENCE quivlist
	;

quivlist:	quiv
	|	quivlist CM quiv
	;

quiv:		OP arydcllist CP
	;

s:		IMPLICIT impllist
	;

impllist:	impldcl
	|	impllist CM impldcl
	;

impldcl:	TYPE OP implletlist CP
	;

implletlist:	impllet
	|	implletlist CM impllet
	;

/* the NAMEs here actually have to be single letters, but it's easier to
   sort this out semantically than to make the parser only allow single
   letters for this one case */

impllet:	NAME
	|	NAME MINUS NAME
	;

exp:		NAME { emit(NAME, $1.n.name); }
	|	CONST {
			switch(TYTYPE($1.c.t)) {
			case TY_INTEGER:
				emit(ICON, $1.c.u.l);	break;
			case TY_REAL:
				emit(RCON, $1.c.u.d);	break;
			case TY_LOGICAL:
				emit(ICON, $1.c.u.l);	break;
			case TY_CHAR:
				emit(CCON, $1.c.u.c);	break;
			default:
				yyerror("Unsupported constant type");
				break;
			}
		}			

	|	OP exp CP
	|	exp PLUS exp { emit(PLUS); }
	|	exp MINUS exp { emit(MINUS); }
	|	exp STAR exp { emit(STAR); }
	|	exp DIV exp { emit(DIV); }
	|	exp POW exp { emit(POW); }
	|	exp CAT exp { emit(CAT); }
	|	exp RELOP exp { emit(RELOP, $2); }
	|	NOT exp { emit(NOT); }
	|	exp AND exp { emit(AND); }
	|	exp OR exp { emit(OR); }
	|	exp EQV exp { emit(EQV, $2); }
	|	MINUS exp	%prec UMINUS  { emit(UMINUS); }
	|	OP exp CM exp CP	/* complex constant, sort of */
	|	aryref
	
aryref:		NAME OP { emit(OP); emit(NAME, $1.n.name); } explist CP
			{ emit(CP); }
	;
		
explist:	exp
	|	explist CM { emit(CM); } exp
	;

/* assignment statement or arithmetic statement function, they're
	syntactically the same */

s:		lhs EQ exp { emit(EQ); }
	;

lhs:		NAME { emit(NAME, $1.n.name); }
	|	aryref
	;

s:		do CONST NAME EQ {
			emit(DO, $2.c.u.l);
			emit(NAME, $3.n.name);
		}
		exp CM { emit(CM); } exp optstep
	;

/* hack - normally you can parse statement numbers as numeric constants
	easily enough, except in a case like
		DO 10 E5 = 1,1000
	where 10E5 looks like a real number.  cxt_do tells the lexer only
	to recognize an integer here.
 */

do:		DO { context = cxt_do; }
	;

optstep:	CM { emit(CM); } exp
	|	/* empty */
	;

s:		CONTINUE { emit(CONTINUE); }
	;


s:		if exp ifcp s
	|	if exp ifcp CONST CM CONST CM CONST {
			emit(ICON, $4.c.u.l);
			emit(ICON, $6.c.u.l);
			emit(ICON, $8.c.u.l);
		}
	;

if:		IF OP	{ emit(IF); }
	;

	/* check ahead for target of IF statement */
	/* we have to use the same prescan to tell how to lex the target
	   statement of the IF.  Arithmetic IFs work OK because three
	   integers separated by commas don't look like an assignment
	   statement. */
	
ifcp:		CP {	if(prescan())
				context = cxt_norm;
			else
				context = cxt_stmt;
			emit(CP);
		}
	;

/* regular, assigned, and computed GOTO */

s:		GOTO CONST { emit(GOTO, $2.c.u.l); }
	|	GOTO NAME { emit(GOTO, 0L); emit(NAME, $2.n.name); }
		optstmtlist
	|	GOTO OP { emit(GOTO, 0L); } stmtlist CP { emit(CP); }
		optcomma exp
	;

optstmtlist:	CM OP stmtlist CP
	|	/* empty */
	;

stmtlist:	CONST { emit(ICON, $1.c.u.l); }
	|	stmtlist CM CONST { emit(ICON, $3.c.u.l); }
	;

s:		STOP
	;

s:		CALL NAME { emit(CALL, $2.n.name); }
	|	CALL NAME { emit(CALL, $2.n.name); } OP cexplist CP
	;

cexplist:	cexp
	|	cexplist CM { emit(CM); } cexp
	;

cexp:		exp
	|	STAR CONST { emit(1, $2.c.u.l); }
	;

s:		RETURN { emit(RETURN); }
	|	RETURN { emit(RETURN); } exp
	;
s:		END { emit(END); }
	;

%%

/* your standard error routine */
void yyerror(char *s)
{
	printf("%d: %s\n", lineno, s);
}
