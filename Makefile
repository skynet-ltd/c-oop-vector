.PHONY: all


jemalloc=$(if $(JEMALLOC), -D __JEMALLOC_ON__)

all:
	gcc$(jemalloc) -fPIC -c vector.c -o vector.o
	gcc -shared vector.o -o libvector.so
