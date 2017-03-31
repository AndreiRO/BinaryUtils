.PHONY: build clean
CC = gcc
CFLAGS = -Wall -Os

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

install: build
	sudo mv bd bl /usr/local/bin
