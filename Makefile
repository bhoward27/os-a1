CFLAGS = -Wall -Werror -std=c11 -o test.out
OFLAGS = -Wall -Werror -std=c11 -g -c -Og

all: test.out

run: test.out
	./test.out

test.out: test.o list.o node_manager.o list_manager.o
	gcc $(CFLAGS) test.o list.o node_manager.o list_manager.o

test.o: test.c list.h
	gcc $(OFLAGS) test.c

list.o: list.c list.h node_manager.h list_manager.h
	gcc $(OFLAGS) list.c

node_manager.o: node_manager.c node_manager.h list.h
	gcc $(OFLAGS) node_manager.c

list_manager.o: list_manager.c list_manager.h list.h
	gcc $(OFLAGS) list_manager.c

clean:
	rm -f *.o *.s *.out