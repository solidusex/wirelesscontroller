# Makefile for Data sublanguages
# written 1985 by Leroy Cain
# modified 1989 by Klaus Meyer-Wegener

ALL: tpar

tpar : tpar.c parser.c y.tab.o
	cc -o tpar tpar.c parser.c y.tab.o -ll

y.tab.o: y.tab.c lex.yy.c parser.h gtok.h
	cc -c y.tab.c

y.tab.c: dsl.y
	yacc -vd dsl.y

lex.yy.c: dsl.l
	lex dsl.l
	./ed0

parser.h: y.tab.h tmprws.h phm
	./ed1
	sort +2 -3 y.h | ./phm
	./ed2 `wc y.h`

phm: phm.c
	cc -o phm phm.c

tf: tf.l
	lex -t tf.l > tf.yy.c
	cc -o tf tf.yy.c

test: tf vtest2 tpar
	tf < vtest2 | tpar
