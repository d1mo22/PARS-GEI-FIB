from antlr4 import *
from exprsLexer import exprsLexer
from exprsParser import exprsParser
from treeVisitor import TreeVisitor
from evalVisitor import EvalVisitor

def main():
    input_stream = FileStream("input.exprs")
    lexer = exprsLexer(input_stream)
    lexer.removeErrorListeners()
    token_stream = CommonTokenStream(lexer)
    parser = exprsParser(token_stream)
    parser.removeErrorListeners()
    tree = parser.root()

    if parser.getNumberOfSyntaxErrors() == 0:
        visitor2 = EvalVisitor()
        visitor2.visit(tree)
    else:
        print(parser.getNumberOfSyntaxErrors(), 'errors de sintaxi.')
        print(tree.toStringTree(recog = parser))
    #visitor = TreeVisitor()
    #visitor.visit(tree)


    #print(tree.toStringTree(recog=parser))

if __name__ == '__main__':
    main()