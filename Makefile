#I think I have labelled the flags backwards. Ask about this?

CFLAGS = -Wall -Werror -o t
OFLAGS = -Wall -Werror -g -c -Og

all: t

t: test.o list.o node_manager.o
	gcc $(CFLAGS) test.o list.o node_manager.o

test.o: test.c list.h node_manager.h
	gcc $(OFLAGS) test.c

list.o: list.c list.h
	gcc $(OFLAGS) list.c

node_manager.o: node_manager.c node_manager.h
	gcc $(OFLAGS) node_manager.c

clean:
	rm -f *.o *.s t