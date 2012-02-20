##########################################################################
#     Fortran 77 Subset Parser - November 1988                           #
#     Copyright 1988 - John R. Levine.  All rights reserved.             #
#     Permission is hereby granted to make copies in modified or         #
#     unmodified form so long as this copyright notice is preserved      #
#     and such copies are not made for direct commercial advantage.      #
#                                                                        #
#     Any other use such as incorporation in whole or in part in a       #
#     product offered for sale requires separate permission.             #
#                                                                        #
#     John R. Levine                                                     #
#     P.O. Box 349                                                       #
#     Cambridge MA 02238-0349                                            #
#                                                                        #
#     Internet/uucp: Levine@yale.edu    MCI Mail:  103-7498              #
#                                                                        #
##########################################################################

CFLAGS=-g
CC=gcc
YFLAGS=-vdlt
OBJS=fparse.o ftnlex.o fmain.o

ftn:	$(OBJS)
	${CC} $(CFLAGS) -o $@ $(OBJS)

fparse.o:	fparse.c ftn.h

fparse.c fparse.h:	fparse.y
		yacc $(YFLAGS) fparse.y
		mv y.tab.c fparse.c
		mv y.tab.h fparse.h

ftnlex.o:	ftnlex.c fparse.h ftn.h

fmain.o:	fmain.c fparse.h ftn.h

#%.o:	%.c
#	${CC} -c ${CFLAGS} $<
