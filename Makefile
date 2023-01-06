build: llist main
	gcc -g main.o llist.o  -lpthread -o main

build_test01: llist test01
	gcc -g test01.o llist.o -lpthread -o test01

llist: llist.h llist.c util.h
	gcc -c -g llist.c -lpthread

main: main.c llist.h
	gcc -c -g main.c -lpthread

test01: test01.c llist
	gcc -c -g test01.c
