all: yosh.o
	gcc -o yosh yosh.o

yosh.o: yosh.c yosh.h
	gcc -c yosh.c

run:
	./yosh

clean:
	rm *.o yosh
