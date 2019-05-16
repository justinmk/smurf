all: a.out

run: | all
	./a.out

a.out: main.c
	clang -lm main.c

.PHONY: all run
