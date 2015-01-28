.PHONY: build clean
CC = gcc
CFLAGS = -Wall -Werror -Os

build: bd bl

bd: bd.o
	$(CC) $(CFLAGS) $^ -o $@

bl: bl.o
	$(CC) $(CFLAGS) $^ -o $@

bd.o: binary_dump.c
	$(CC) $(CFLAGS) -c $^ -o $@

bl.o: binary_load.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -fv bd.o bl.o bl bd
