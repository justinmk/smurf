UUT=producerconsumer
build: $(UUT)

producerconsumer:
	mcs producerconsumer.cs
	mono producerconsumer.exe

run: | $(UUT)
	mono $(UUT).exe

clean: clean
	rm -rf *.exe
 
.PHONY: build clean

