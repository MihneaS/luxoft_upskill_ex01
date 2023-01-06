CC = gcc
CFLAGS = -Wall -Wextra -g

build: llist main
	$(CC) $(CFLAGS) main.o llist.o  -lpthread -o main

build_test01: llist test01
	$(CC) $(CFLAGS) test01.o llist.o -lpthread -o test01

llist: llist.h llist.c util.h
	$(CC) $(CFLAGS) -c llist.c -lpthread

main: main.c llist.h
	$(CC) $(CFLAGS) -c main.c -lpthread

test01: test01.c llist
	$(CC) $(CFLAGS) -c test01.c
