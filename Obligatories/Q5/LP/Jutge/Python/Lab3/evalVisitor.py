from exprsVisitor import exprsVisitor
from exprsParser import exprsParser

class ReturnException(Exception):
    def __init__(self, value):
        self.value = value

class EvalVisitor(exprsVisitor):

    def __init__(self):
        self.memoria = {}
        self.funciones = {}
        self.pila_memoria = []

    def visitRoot(self, ctx):
        for stmt in ctx.stmt():
            self.visit(stmt)
        return None

    def visitAssignacio(self, ctx):
        var_name = ctx.VAR().getText()
        value = self.visit(ctx.expr())
        self.memoria[var_name] = value
        return value

    def visitEscriure(self, ctx):
        value = self.visit(ctx.expr())
        print(value)

    def visitCondicional(self, ctx):
        condition = self.visit(ctx.condition())
        if condition:
            for stmt in ctx.stmt():
                self.visit(stmt)
        return None

    def visitBucle(self, ctx):
        while self.visit(ctx.condition()):
            for stmt in ctx.stmt():
                self.visit(stmt)
        return None

    def visitFuncion(self, ctx):
        func_name = ctx.VAR().getText()
        params = []
        if ctx.params():
            params = [param.getText() for param in ctx.params().VAR()]
        stmts = ctx.stmt()
        self.funciones[func_name] = (params, stmts)
        return None

    def visitLlamadaFuncion(self, ctx):
        func_name = ctx.VAR().getText()
        args = []
        if ctx.args():
            args = [self.visit(arg) for arg in ctx.args().expr()]
        
        if func_name not in self.funciones:
            raise Exception(f"Error: Función '{func_name}' no definida.")
        
        params, stmts = self.funciones[func_name]
        
        if len(params) != len(args):
            raise Exception(f"Error: Función '{func_name}' espera {len(params)} argumentos, se recibieron {len(args)}.")
        
        # Crear nuevo contexto de memoria
        memoria_local = self.memoria.copy()
        for param, arg in zip(params, args):
            memoria_local[param] = arg
        self.pila_memoria.append(self.memoria)
        self.memoria = memoria_local
        
        
        # Ejecutar y capturar el return
        return_value = None
        try:
            for stmt in stmts:
                self.visit(stmt)
        except ReturnException as re:
            return_value = re.value
        finally:
            self.memoria = self.pila_memoria.pop()
        
        return return_value

    def visitRetorno(self, ctx):
        value = self.visit(ctx.expr())
        raise ReturnException(value)

    # Métodos para condiciones
    def visitLess_than(self, ctx):
        return self.visit(ctx.expr(0)) < self.visit(ctx.expr(1))
    
    def visitGreater_than(self, ctx):
        return self.visit(ctx.expr(0)) > self.visit(ctx.expr(1))
    
    def visitEqual(self, ctx):
        return self.visit(ctx.expr(0)) == self.visit(ctx.expr(1))
    
    def visitNot_equal(self, ctx):
        return self.visit(ctx.expr(0)) != self.visit(ctx.expr(1))
    
    def visitLess_or_equal(self, ctx):
        return self.visit(ctx.expr(0)) <= self.visit(ctx.expr(1))
    
    def visitGreater_or_equal(self, ctx):
        return self.visit(ctx.expr(0)) >= self.visit(ctx.expr(1))

    # Métodos para expresiones
    def visitPotencia(self, ctx):
        return self.visit(ctx.expr(0)) ** self.visit(ctx.expr(1))
    
    def visitDiviso(self, ctx):
        divisor = self.visit(ctx.expr(1))
        if divisor == 0:
            raise ZeroDivisionError("Error: División por cero.")
        return self.visit(ctx.expr(0)) / divisor
    
    def visitMultiplicio(self, ctx):
        return self.visit(ctx.expr(0)) * self.visit(ctx.expr(1))
    
    def visitResta(self, ctx):
        return self.visit(ctx.expr(0)) - self.visit(ctx.expr(1))
    
    def visitSuma(self, ctx):
        return self.visit(ctx.expr(0)) + self.visit(ctx.expr(1))
    
    def visitNegacion(self, ctx):
        return -self.visit(ctx.expr())
    
    def visitNumero(self, ctx):
        return int(ctx.NUM().getText())
    
    def visitVariable(self, ctx):
        var_name = ctx.VAR().getText()
        if var_name in self.memoria:
            return self.memoria[var_name]
        else:
            raise NameError(f"Error: Variable '{var_name}' no definida.")
    
    def visitParentesis(self, ctx):
        return self.visit(ctx.expr())