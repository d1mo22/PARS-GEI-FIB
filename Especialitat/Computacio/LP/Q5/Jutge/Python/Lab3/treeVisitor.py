from exprsVisitor import exprsVisitor

class TreeVisitor(exprsVisitor):
    def __init__(self):
        self.nivell = 0
        self.memoria = {}

    def visitSuma(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        print('  ' *  self.nivell + '+')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitResta(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        print('  ' * self.nivell + '-')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitMultiplicio(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        print('  ' * self.nivell + '*')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitDiviso(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        print('  ' * self.nivell + '/')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1

    def visitPotencia(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        print('  ' * self.nivell + '^')
        self.nivell += 1
        self.visit(expressio1)
        self.visit(expressio2)
        self.nivell -= 1


    def visitNumero(self, ctx):
        [numero] = list(ctx.getChildren())
        print("Hola  " * self.nivell + numero.getText())

    def visitAssignacio(self, ctx):
        var_name = ctx.VAR().getText()
        value = self.visit(ctx.expr())
        self.memoria[var_name] = value

    def visitEscriure (self, ctx):
        var = ctx.VAR().getText()
        value = self.memoria.get(var, 0)
        print(value)
        
