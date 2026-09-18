CC = gcc
CFLAGS = -Wall -Wextra

slist: main.o
	gcc $(CFLAGS) -o slist main.o

main.o: main.c student.h
	gcc $(CFLAGS) -c main.c

clean:
	rm -f main.o slist