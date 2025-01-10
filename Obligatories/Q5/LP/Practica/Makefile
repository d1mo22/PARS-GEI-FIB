# Variables
GRAMMAR = scheme.g4
GENERATED_FILES = schemeLexer.py schemeParser.py schemeVisitor.py scheme.interp scheme.tokens

.PHONY: all clean

all: $(GENERATED_FILES)

$(GENERATED_FILES): $(GRAMMAR)
	java -jar antlr-4.13.2-complete.jar -Dlanguage=Python3 -visitor -no-listener $(GRAMMAR)

clean:
	rm -f *.interp *.tokens
	rm -f __pycache__/*
	rm -f schemeLexer.py schemeParser.py schemeVisitor.py
	rm -rf __pycache__