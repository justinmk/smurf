# reference: http://www.devin.com/cruft/javamakefile.html

JAVAC=javac
.SUFFIXES: .java .class
sources = $(wildcard *.java)
classes = $(sources:.java=.class)

all: $(classes)

%.class : %.java
	$(JAVAC) -Xlint:unchecked $<

run: | all
	java Main

clean:
	$(RM) *.class

.PHONY: run

