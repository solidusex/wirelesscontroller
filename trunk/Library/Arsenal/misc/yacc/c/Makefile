YFLAGS	= -dv
CFLAGS	= -O
LFLAGS	=

SRC	= gram.y scan.l main.c
OBJ	= gram.o scan.o main.o

$(BIN)/gcc :	$(OBJ)
	cc $(CFLAGS) $(OBJ)

scan.o	: y.tab.h

clean	:
	rm -f y.tab.h y.output *.o
