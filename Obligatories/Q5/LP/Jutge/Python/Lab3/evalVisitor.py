from exprsVisitor import exprsVisitor

class EvalVisitor(exprsVisitor):
    
    def __init__(self):
        self.memoria = {}
    
    def visitRoot(self, ctx):
          # Visita todas las declaraciones dentro del root
        for stmt in ctx.stmt():
            self.visit(stmt)
        return None

    def visitSuma(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        return self.visit(expressio1) + self.visit(expressio2)

    def visitPotencia(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        return self.visit(expressio1) ** self.visit(expressio2)

    def visitMultiplicio(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        return self.visit(expressio1) * self.visit(expressio2)

    def visitDiviso(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        return self.visit(expressio1) / self.visit(expressio2)

    def visitResta(self, ctx):
        [expressio1, operador, expressio2] = list(ctx.getChildren())
        return self.visit(expressio1) - self.visit(expressio2)

    def visitNumero(self, ctx):
        [numero] = list(ctx.getChildren())
        return int(numero.getText())
    
    def visitVariable(self, ctx):
        var_name = ctx.VAR().getText()
        if var_name in self.memoria:
            return self.memoria[var_name]
        else:
            raise NameError(f"Error: Variable '{var_name}' no definida.")
    
    def visitAssignacio(self, ctx):
        var_name = ctx.VAR().getText()
        value = self.visit(ctx.expr())
        self.memoria[var_name] = value
        return value
    
    def visitEscriure(self, ctx):
        var_name = ctx.VAR().getText()
        value = self.memoria.get(var_name, 0)
        if var_name in self.memoria:
            value = self.memoria[var_name]
            print(value)
            return value
        else:
            raise NameError(f"Error: Variable '{var_name}' no definida.")