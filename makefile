all: yosh.o parse.o
	gcc -o yosh yosh.o parse.o

yosh.o: yosh.c yosh.h
	gcc -c yosh.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./yosh

clean:
	rm *.o yosh yosh_debug

bug: yosh.c yosh.h parse.c parse.h
	gcc -c -g yosh.c
	gcc -c -g parse.c
	gcc -g -o yosh_debug yosh.o parse.o

debug: yosh_debug
	gdb ./yosh_debug
