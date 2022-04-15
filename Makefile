all: HashMap.c LinkedList.c main.c
	gcc -std=gnu99 HashMap.c LinkedList.c main.c -o main
	./main

test: HashMap.c LinkedList.c test.c
	gcc -std=gnu99 HashMap.c LinkedList.c test.c -o test
	./test
