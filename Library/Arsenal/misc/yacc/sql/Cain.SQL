Path: incas!unido!mcsun!uunet!cuc1!lcain
From: lcain@cuc1.UUCP (Leroy Cain)
Newsgroups: comp.databases
Subject: ISO/ANSI SQL Parser in LEX/YACC
Keywords: ISO ANSI SQL LEX YACC
Message-ID: <2137@cuc1.UUCP>
Date: 15 Sep 89 21:50:08 GMT
Organization: Columbia Union College; Takoma Park, MD 20912
Lines: 42
Posted: Fri Sep 15 22:50:08 1989


Hi Guys

The LEX/YACC parser for ANSI SQL is almost done.  What I am look for
now is several of you that are familiar the ANSI specification to
review my work before I release it, so that it will be as error free
as possible.

For the rest of you here are some highlights of this package.

This is an parser for ISO/ANSI SQL written useing LEX, YACC, and C
it provide syntax check and a frame for building a completed
query processor.
See	ANSI X3.135-1986 and ANSI X3.135.1-198x Addendum 1
	ISO 9075-1987(E) Addendum 1

Unlike the previous SQL parser I posted, this one can be process with
a normal YACC so everyone should be able to use it.

There are three parts:
	1. Module	-- This processes the module specification and
			produces function calls to which ever language
			is specificied.
	2. Embedded	-- This processes the embedded SQL specification and
			produces function calls to which ever language
			is specificied.
	3. Internal	-- This processes SQL command passed to the function
			interface.

Notes:
	In Module and Embedded you add the code to produce the function
	calls.
	Language specificied for use with Module and Embedded are C, COBOL,
	FORTRAN, Pascal, PL/1.
	C as a possible langauge for Module and Embedded is not specificied
	in the ANSI specs.  This is the only place I deveated. 


MS-DOS Just say NO!!!!!			      OS/2 Why????
Leroy Cain;      Columbia Union College;      Mathematical Sciences
Department
7600 Flower Ave. WH406;  	              Takoma Park, Md 20912
(301) 891-4172				      uunet!cucstud!lcain

