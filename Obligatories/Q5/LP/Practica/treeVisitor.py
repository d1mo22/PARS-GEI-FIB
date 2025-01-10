from schemeVisitor import schemeVisitor
from schemeParser import schemeParser


class TreeVisitor(schemeVisitor):

    def __init__(self):
        self.nivell = 0

    def visitAddition(self, ctx: schemeParser.AdditionContext):
        [_, _, expressio1, expressio2, _] = list(ctx.getChildren())
        print('  ' * self.nivell + '+')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitSubstraction(self, ctx: schemeParser.SubstractionContext):
        [_, _, expressio1, expressio2, _] = list(ctx.getChildren())
        print('  ' * self.nivell + '-')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitMultiplication(self, ctx: schemeParser.MultiplicationContext):
        [_, _, expressio1, expressio2, _] = list(ctx.getChildren())
        print('  ' * self.nivell + '*')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitDivision(self, ctx: schemeParser.DivisionContext):
        [_, _, expressio1, expressio2, _] = list(ctx.getChildren())
        print('  ' * self.nivell + '/')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitDisplay(self, ctx: schemeParser.DisplayContext):
        [_, _, expresion, _] = list(ctx.getChildren())
        print('  ' * self.nivell + 'display')
        self.nivell += 1
        self.visit(expresion)
        self.nivell -= 1

    def visitNumber(self, ctx: schemeParser.NumberContext):
        [numero] = list(ctx.getChildren())
        print('  ' * self.nivell + numero.getText())

    def visitString(self, ctx: schemeParser.StringContext):
        [string] = list(ctx.getChildren())
        print('  ' * self.nivell + string.getText())

    def visitVariable(self, ctx: schemeParser.VariableContext):
        [var] = list(ctx.getChildren())
        print('  ' * self.nivell + var.getText())

    def visitBoolean(self, ctx: schemeParser.BooleanContext):
        [boolean] = list(ctx.getChildren())
        print('  ' * self.nivell + boolean.getText())

    def visitLet(self, ctx: schemeParser.LetContext):
        print('  ' * self.nivell + 'let')
        self.nivell += 1
        for binding in ctx.binding():
            self.visit(binding)
        for stmt in ctx.stmt():
            self.visit(stmt)
        self.nivell -= 1

    def visitBind(self, ctx: schemeParser.BindContext):
        [_, var, expr, _] = list(ctx.getChildren())
        print('  ' * self.nivell + 'bind')
        self.nivell += 1
        print('  ' * self.nivell + var.getText())
        self.visit(expr)
        self.nivell -= 1

    def visitConditional(self, ctx: schemeParser.ConditionalContext):
        print('  ' * self.nivell + 'if')
        self.nivell += 1
        self.visit(ctx.condition())
        self.visit(ctx.stmt(0))
        self.visit(ctx.stmt(1))
        self.nivell -= 1

    def visitFunction(self, ctx: schemeParser.FunctionContext):
        [_, _, _, name, params, _, *body, _] = list(ctx.getChildren())
        print('  ' * self.nivell + 'define')
        self.nivell += 1
        print('  ' * self.nivell + name.getText())
        for param in self.visit(params):
            print('  ' * self.nivell + param)
        for stmt in body:
            self.visit(stmt)
        self.nivell -= 1

    def visitParams(self, ctx: schemeParser.ParamsContext):
        return [var.getText() for var in ctx.VAR()]

    def visitQuote(self, ctx: schemeParser.QuoteContext):
        print('  ' * self.nivell + 'quote')
        self.nivell += 1
        self.visit(ctx.list_())
        self.nivell -= 1

    def visitList_expr(self, ctx: schemeParser.List_exprContext):
        print('  ' * self.nivell + 'list')
        self.nivell += 1
        for element in ctx.element():
            self.visit(element)
        self.nivell -= 1
