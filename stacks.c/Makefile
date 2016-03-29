# UUT=hanoi
LIBS=-lm
CC=gcc
CFLAGS=-Wall -Wpedantic -std=c99 -Iinclude $(LIBS)

all: clean build/main test

test: | build/main
	./build/main

build/main: build/$(UUT).o
	cc -o build/main build/$(UUT).o

build/%.o: %.c
	[ -d build ] || mkdir build/
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf build/

.PHONY: all clean test
