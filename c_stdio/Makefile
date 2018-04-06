all: a.out

run: | all
	./a.out

a.out: main.c
	$(CC) main.c

clean:
	rm -f nvim/*.o nvim/*.so

.PHONY: all run clean
