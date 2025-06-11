import sys
from antlr4 import *
from gLexer import gLexer
from gParser import gParser
from visitor import GVisitor


def main():
    debug_mode = False
    # Check if a filename is provided
    if len(sys.argv) < 2:
        print("Usage: python3 g.py [-d] <filename.j>")
        sys.exit(1)

    # Check for debug mode
    if sys.argv[1] == '-d':
        debug_mode = True
        input_file = sys.argv[2] if len(sys.argv) > 2 else None
    else:
        input_file = sys.argv[1]

    if not input_file:
        print("Usage: python3 g.py [-d] <filename.j>")
        sys.exit(1)

    # Read the input file
    with open(input_file, 'r') as file:
        input_stream = InputStream(file.read())

    # Create a lexer and parser
    lexer = gLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = gParser(stream)

    # Parse the input
    tree = parser.program()

    # Create a visitor and evaluate the parsed tree
    visitor = GVisitor(debug_mode=debug_mode)
    result = visitor.visit(tree)


if __name__ == '__main__':
    main()
