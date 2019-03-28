all: card

run: | all
	./card > carp.ppm

card: card.cpp
	clang++ -O3 card.cpp -o card

clean:
	rm card

.PHONY: all run clean
