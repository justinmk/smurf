# all: test
# .PHONY: all

# clean:
# 	rm -f *.o *.out
# test: main.c
# 	./a.out

all: a.out test

deps: | $(LIBUV) $(MSGPACK) $(COXPCALL) $(BUSTED)

test: | a.out
	./a.out

clean:
	rm -f nvim/*.o nvim/*.so

a.out: main.c
	$(CC) main.c

.PHONY: all test clean
