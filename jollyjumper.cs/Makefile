all: run

build:
	mcs main.cs

run: | build
	mono main.exe

test: all
	$(BUSTED) -v '--lpath=./?.lua;' '--cpath=./?.so;' -o gtest test

distclean: clean
	rm -rf $(DEPS_DIR)
 
.PHONY: all test valgrind clean distclean

