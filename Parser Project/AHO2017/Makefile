GCC = gcc -Wall -pedantic -g -pg
OBJECTS = lex.yy.o parser.o emitter.o symbol.o init.o error.o main.o

asu : $(OBJECTS)
	$(GCC) $(OBJECTS) -o aho
lex.yy.o : global.h lex.yy.c
	$(GCC) -c lex.yy.c -lfl
parser.o : global.h parser.c
	$(GCC) -c parser.c
emitter.o : global.h emitter.c
	$(GCC) -c emitter.c
symbol.o : global.h symbol.c
	$(GCC) -c symbol.c
init.o : global.h init.c
	$(GCC) -c init.c
error.o : global.h error.c
	$(GCC) -c error.c
main.o : global.h main.c
	$(GCC) -c main.c
lex.yy.c : global.h i2p.l
	flex i2p.l

clean:
	-rm -f $(OBJECTS) lex.yy.c aho
