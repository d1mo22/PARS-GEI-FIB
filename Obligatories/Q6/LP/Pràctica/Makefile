GRAMMAR = g.g4
GENERATED_FILES = gLexer.py gParser.py gVisitor.py

.PHONY: all clean

all: $(GENERATED_FILES)

$(GENERATED_FILES): $(GRAMMAR)
	antlr4 -Dlanguage=Python3 -visitor -no-listener $(GRAMMAR)

clean:
	rm -f *.interp *.tokens
	rm -f __pycache__/*
	rm -f gLexer.py gParser.py gVisitor.py
	rm -rf __pycache__
	rm -f *.java