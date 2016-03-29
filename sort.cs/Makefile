all: run

build:
	mcs main.cs main.partial.cs

run: | build
	mono main.exe

test: all

distclean: clean
	rm -rf $(DEPS_DIR)
 
.PHONY: all test valgrind clean distclean

