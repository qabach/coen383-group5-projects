CC = gcc

edit : main.o linked.o
	gcc -o test main.o linked.o

main.o: main.c	linked.h
	cc -c main.c

linked.o: linked.c linked.h
	cc -c linked.c

clean:
	rm test main.o linked.o
