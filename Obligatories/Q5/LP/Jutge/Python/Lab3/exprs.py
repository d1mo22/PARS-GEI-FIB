from antlr4 import *
from exprsLexer import exprsLexer
from exprsParser import exprsParser
from treeVisitor import TreeVisitor
from evalVisitor import EvalVisitor

input_stream = FileStream("input.exprs")
lexer = exprsLexer(input_stream)
token_stream = CommonTokenStream(lexer)
parser = exprsParser(token_stream)
tree = parser.root()

#visitor = TreeVisitor()
#visitor.visit(tree)

visitor2 = EvalVisitor()
visitor2.visit(tree)
#print(tree.toStringTree(recog=parser))