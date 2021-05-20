CFLAGS = -o t
OFLAGS = -g -c -Og

all: t

t: test.o list.o stack.o
	gcc $(CFLAGS) test.o list.o stack.o

test.o: test.c list.h stack.h
	gcc $(OFLAGS) test.c

list.o: list.c list.h
	gcc $(OFLAGS) list.c

stack.o: stack.c stack.h
	gcc $(OFLAGS) stack.c

clean:
	rm -f *.o *.s t