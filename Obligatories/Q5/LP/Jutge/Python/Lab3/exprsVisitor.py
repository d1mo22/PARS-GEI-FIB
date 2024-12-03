# Generated from exprs.g4 by ANTLR 4.13.2
from antlr4 import *
if "." in __name__:
    from .exprsParser import exprsParser
else:
    from exprsParser import exprsParser

# This class defines a complete generic visitor for a parse tree produced by exprsParser.

class exprsVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by exprsParser#root.
    def visitRoot(self, ctx:exprsParser.RootContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#assignacio.
    def visitAssignacio(self, ctx:exprsParser.AssignacioContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#escriure.
    def visitEscriure(self, ctx:exprsParser.EscriureContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#condicional.
    def visitCondicional(self, ctx:exprsParser.CondicionalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#bucle.
    def visitBucle(self, ctx:exprsParser.BucleContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#funcion.
    def visitFuncion(self, ctx:exprsParser.FuncionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#llamada.
    def visitLlamada(self, ctx:exprsParser.LlamadaContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#retorno.
    def visitRetorno(self, ctx:exprsParser.RetornoContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#params.
    def visitParams(self, ctx:exprsParser.ParamsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#args.
    def visitArgs(self, ctx:exprsParser.ArgsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#less_than.
    def visitLess_than(self, ctx:exprsParser.Less_thanContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#greater_than.
    def visitGreater_than(self, ctx:exprsParser.Greater_thanContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#equal.
    def visitEqual(self, ctx:exprsParser.EqualContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#not_equal.
    def visitNot_equal(self, ctx:exprsParser.Not_equalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#less_or_equal.
    def visitLess_or_equal(self, ctx:exprsParser.Less_or_equalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#greater_or_equal.
    def visitGreater_or_equal(self, ctx:exprsParser.Greater_or_equalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#parentesis.
    def visitParentesis(self, ctx:exprsParser.ParentesisContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#suma.
    def visitSuma(self, ctx:exprsParser.SumaContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#potencia.
    def visitPotencia(self, ctx:exprsParser.PotenciaContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#llamadaFuncion.
    def visitLlamadaFuncion(self, ctx:exprsParser.LlamadaFuncionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#numero.
    def visitNumero(self, ctx:exprsParser.NumeroContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#diviso.
    def visitDiviso(self, ctx:exprsParser.DivisoContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#variable.
    def visitVariable(self, ctx:exprsParser.VariableContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#resta.
    def visitResta(self, ctx:exprsParser.RestaContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#multiplicio.
    def visitMultiplicio(self, ctx:exprsParser.MultiplicioContext):
        return self.visitChildren(ctx)



del exprsParser