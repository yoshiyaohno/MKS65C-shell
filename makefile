all: yosh.o
	gcc -o yosh yosh.o

yosh.o: yosh.c yosh.h
	gcc -c yosh.c

run:
	./yosh

clean:
	rm *.o yosh yosh_debug

bug: yosh.c yosh.h
	gcc -c -g yosh.c
	gcc -g -o yosh_debug yosh.o

debug: yosh_debug
	gdb ./yosh_debug
