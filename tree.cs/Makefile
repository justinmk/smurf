UUT=tree
build: $(UUT)

tree:
	mcs tree.cs
	mono tree.exe

run: | $(UUT)
	mono $(UUT).exe

clean: clean
	rm -rf *.exe
 
.PHONY: build clean


