CC = gcc
CCFLAGS = -ansi -Wall -pedantic

all: main

main: main.o libsl.a
	${CC} ${CCFLAGS} -o sl main.o libsl.a

main.o: main.c
	${CC} ${CCFLAGS} -c main.c

libsl.a: sorted-list.o
	ar -rv libsl.a sorted-list.o

sorted-list.o: sorted-list.c
	${CC} ${CCFLAGS} -c sorted-list.c

clean:
	rm *.o *.a 
