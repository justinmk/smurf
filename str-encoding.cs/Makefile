UUT=main
build: $(UUT)

main:
	mcs main.cs
	mono main.exe

run: | $(UUT)
	mono $(UUT).exe

clean: clean
	rm -rf *.exe
 
.PHONY: build clean

