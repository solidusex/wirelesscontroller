%{
/******************************************************************************
		LEXICAL ANALYSER for ISO standard Pascal
		----------------------------------------

This lexical analyser satisfies the following requirements in British
Standards Institution Specification for Computer programming language Pascal
BS6192:1982 (ISO 7185:1983)

6.1.1	6.1.2	6.1.3	6.1.4	6.1.5	6.1.6	6.1.7
6.1.8	(except ^Z is considered to be a space)
6.1.9
******************************************************************************/

#include "y_tab.h"
int	character_no = -1;
int     linenumber = 1;


char	numbertext[80];
char    lastident[128];

%}

A	[Aa]
B	[Bb]
C	[Cc]
D	[Dd]
E	[Ee]
F	[Ff]
G	[Gg]
H	[Hh]
I	[Ii]
J	[Jj]
K	[Kk]
L	[Ll]
M	[Mm]
N	[Nn]
O	[Oo]
P	[Pp]
Q	[Qq]
R	[Rr]
S	[Ss]
T	[Tt]
U	[Uu]
V	[Vv]
W	[Ww]
X	[Xx]
Y	[Yy]
Z	[Zz]
%%
\n                              { linenumber++;         }
[ \t\32]			;
{A}{N}{D}			{ return(AND);		}
{A}{R}{R}{A}{Y}			{ return(ARRAY);	}
{B}{E}{G}{I}{N}			{ return(SBEGIN);	}
{C}{A}{S}{E}			{ return(CASE);		}
{C}{O}{N}{S}{T}			{ return(CONST);	}
{D}{I}{V}			{ return(DIV);		}
{D}{O}{W}{N}{T}{O}		{ return(DOWNTO);	}
{D}{O}				{ return(DO);		}
{E}{L}{S}{E}			{ return(ELSE);		}
{E}{N}{D}			{ return(END);		}
{F}{I}{L}{E}			{ return(SFILE);	}
{F}{O}{R}			{ return(FOR);		}
{F}{U}{N}{C}{T}{I}{O}{N}	{ return(FUNCTION);	}
{G}{O}{T}{O}			{ return(GOTO);		}
{I}{F}				{ return(IF);		}
{I}{N}				{ return(IN);		}
{L}{A}{B}{E}{L}			{ return(LABEL);	}
{M}{O}{D}			{ return(MOD);		}
{N}{I}{L}			{ return(NIL);		}
{N}{O}{T}			{ return(NOT);		}
{O}{F}				{ return(OF);		}
{O}{R}				{ return(OR);		}
{P}{A}{C}{K}{E}{D}		{ return(PACKED);	}
{P}{R}{O}{C}{E}{D}{U}{R}{E}	{ return(PROCEDURE);	}
{P}{R}{O}{G}{R}{A}{M}		{ return(PROGRAM);	}
{R}{E}{C}{O}{R}{D}		{ return(RECORD);	}
{R}{E}{P}{E}{A}{T}		{ return(REPEAT);	}
{S}{E}{T}			{ return(SET);		}
{T}{H}{E}{N}			{ return(THEN);		}
{T}{O}				{ return(TO);		}
{T}{Y}{P}{E}			{ return(TYPE);		}
{U}{N}{T}{I}{L}			{ return(UNTIL);	}
{V}{A}{R}			{ return(VAR);		}
{W}{H}{I}{L}{E}			{ return(WHILE);	}
{W}{I}{T}{H}			{ return(WITH);		}

[a-zA-Z][a-zA-Z0-9_]*		{ strcpy(lastident, yytext);
				  return(IDENTIFIER);
						/*if strict check no '_' */}
"<="				{ return(LE);	}
">="				{ return(GE);	}
"<>"				{ return(NE);	}
":="				{ return(BECOMES);	}
".."				{ return(DOTDOT);	}
"(."				{ return('[');	}
".)"				{ return(']');	}
"-"	|
"+"	|
"*"	|
"/"	|
"="	|
"<"	|
">"	|
"("	|
")"	|
"["	|
"]"	|
"."	|
","	|
";"	|
":"	|
"^"	{ return(yytext[0]); }
"@"	{ return('^');	}
[0-9]+("."[0-9]+)?[eE][+-]?[0-9]+	|
[0-9]+"."[0-9]+				{ strcpy(numbertext,yytext);
					  return(UNSIGNED_REAL);	}
[0-9]+	{ strcpy(numbertext,yytext); return(UNSIGNED_INT);	}

"{"	comment();
"(*"	comment();
'	{ strings(); return(STRING); }
"}"	yyerror("'}' not in comment");
.	{ char m[40];
	  sprintf(m,"Illegal character '\\%o'", (int)yytext[0]);
	  yyerror(m);
	}


%%
comment()
{
    char c, lastc=' ';
    while(c = input())
        {
	if (c == '\n') linenumber++;

        if(c == '}' || (lastc=='*' && c==')'))
	    break;
        else
	    lastc = c;
        }
}

char *laststring;
strings()
{
    char  *create_string();
    char  buf[256];
    char  c, *p = buf;
    while(c = input())
        switch(c) {
	    case '\'' : if((c = input()) == '\'')
			    *p++ = c;
			else
			{   unput(c); *p++ = '\0';
			    laststring = create_string(buf);
			    return;
			}
			break;
	    case '\n' :
	    case '\014' :
	    case '\015': yyerror("String not terminated");
			return;
	    default   : *p++ = c;
			break;
	}
}


int yywrap()

{
        return 1;
}
