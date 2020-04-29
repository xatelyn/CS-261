CC=gcc --std=c99 -g

all: test

test: test.c products.o dynarray.o
	$(CC) test.c products.o dynarray.o -o test

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

products.o: products.c products.h
	$(CC) -c products.c

clean:
	rm -f test products.o dynarray.o
