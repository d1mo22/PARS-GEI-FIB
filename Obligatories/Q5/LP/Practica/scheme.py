import argparse
from antlr4 import CommonTokenStream, FileStream
from schemeLexer import schemeLexer
from schemeParser import schemeParser
from evalVisitor import EvalVisitor
from errorListener import ErrorListener
from treeVisitor import TreeVisitor


def setup():
    parser = argparse.ArgumentParser(description='Scheme Interpreter')
    parser.add_argument('file', type=str, nargs='?',
                        help='Scheme source file')
    parser.add_argument('-d', '--debug', action='store_true',
                        help='Print debug information')

    args = parser.parse_args()

    return args


def main():
    args = setup()

    input_stream = FileStream(args.file)
    lexer = schemeLexer(input_stream)
    token_stream = CommonTokenStream(lexer)
    parser = schemeParser(token_stream)
    # Remove default error listeners and add custom one
    parser.removeErrorListeners()
    parser.addErrorListener(ErrorListener())

    tree = parser.root()
    # If we are in debug mode, print the tokens
    if args.debug:
        print('Tokens:')
        print(tree.toStringTree(recog=parser))
        print('\nTree structure:')
        tree_visitor = TreeVisitor()
        tree_visitor.visit(tree)
        print()
    # If there are no syntax errors, evaluate the tree
    if parser.getNumberOfSyntaxErrors() == 0:
        evaluator = EvalVisitor()
        evaluator.visit(tree)


if __name__ == '__main__':
    main()
