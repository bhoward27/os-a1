# 1) "make" the program with -fno-stack-protector to experience 
#    "segmentation fault" when a password with size > 20 is entered
# 2) "make clean", comment out the SFLAGS with -fno-stack-protector 
#     and uncomment the SFLAGS without -fno-stack-protector then "make"
#     the program to experience gcc's protection, i.e., the detection
#     of buffer overflow via the use of canary and the resulting 
#     *** stack smashing detected ***: ./x terminated
#     Aborted
#     when a password with size > 20 is entered

SFLAGS = -S -O2 -fno-stack-protector
# SFLAGS = -S -O2
OFLAGS = -g -c
CFLAGS = -o x

all:	x

x:	main.o 
	gcc $(CFLAGS) main.o

main.o:	main.s
	gcc $(OFLAGS) main.s

main.s:	main.c
	gcc $(SFLAGS) main.c

clean:	
	rm -f x *.o main.s
