CFLAGS = -o t
OFLAGS = -g -c -Og

all: t

t: test.o list.o
	gcc $(CFLAGS) test.o list.o

test.o: test.c list.h
	gcc $(OFLAGS) test.c

list.o: list.c list.h
	gcc $(OFLAGS) list.c

clean:
	rm -f *.o *.s t