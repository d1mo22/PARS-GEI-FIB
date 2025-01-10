from schemeVisitor import schemeVisitor
from schemeParser import schemeParser


class Function:
    def __init__(self, name, params, body, parent_scope):
        self.name = name
        self.params = params
        self.body = body
        self.parent_scope = parent_scope.copy()  # Closure


class EvalVisitor(schemeVisitor):

    def __init__(self):
        self.memory = {
            'newline': print,
            'car': lambda x: x[0],
            'cdr': lambda x: x[1:],
            'cons': lambda x, y: [x] + y,
            'null?': lambda x: "#t" if not x else "#f",
            # 'filter': self.filter_impl,
            # 'map': self.map_impl,

        }
        self.functions = {}
        self.stack = []
        self.input_buffer = []

    # def map_impl(self, args):
    #     """Map implementation"""
    #     func, lst = args
    #     if not isinstance(func, Function):
    #         raise TypeError("map: first argument must be a function")
    #     if not isinstance(lst, list):
    #         raise TypeError("map: second argument must be a list")
    #     return [self.execute_user_function(func, [element]) for element in lst]

    # def filter_impl(self, args):
    #     """Filter implementation"""
    #     predic, lst = args
    #     return [self.visit(element) for element in lst if self.visit(predic)(self.visit(element))]

    def visitRoot(self, ctx: schemeParser.RootContext):
        result = None
        # Visit all statements
        for child in ctx.stmt():
            result = self.visit(child)
        return result

    def visitAddition(self, ctx: schemeParser.AdditionContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return self.visit(expr1) + self.visit(expr2)

    def visitSubstraction(self, ctx: schemeParser.SubstractionContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return self.visit(expr1) - self.visit(expr2)

    def visitMultiplication(self, ctx: schemeParser.MultiplicationContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return self.visit(expr1) * self.visit(expr2)

    def visitDivision(self, ctx: schemeParser.DivisionContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return self.visit(expr1) / self.visit(expr2)

    def visitMod(self, ctx: schemeParser.ModContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return self.visit(expr1) % self.visit(expr2)

    def visitDisplay(self, ctx: schemeParser.DisplayContext):
        [_, _, expr, _] = list(ctx.getChildren())
        result = self.visit(expr)
        if isinstance(result, list):
            print('(' + ' '.join(map(str, result)) + ')')
        else:
            print(result)
        return result

    def visitNumber(self, ctx: schemeParser.NumberContext):
        [number] = list(ctx.getChildren())
        num_str = number.getText()
        if '.' in num_str:
            return float(num_str)
        # else
        return int(num_str)

    def visitString(self, ctx: schemeParser.StringContext):
        [string] = list(ctx.getChildren())
        # Remove quotes
        return string.getText()[1:-1]

    def visitConstant(self, ctx: schemeParser.ConstantContext):
        [_, _, var_name, value_expr, _] = list(ctx.getChildren())
        var_name = var_name.getText()
        value = self.visit(value_expr)
        if var_name in self.memory:
            raise ValueError("Error: Constant"
                             + f"'{var_name}' is already defined")
        self.memory[var_name] = value
        return value

    def visitLet(self, ctx: schemeParser.LetContext):
        old_scope = self.memory.copy()
        new_scope = old_scope.copy()

        for binding in ctx.binding():
            var_name = binding.VAR().getText()
            value = self.visit(binding.expr())
            new_scope[var_name] = value

        self.memory = new_scope
        result = None
        for stmt in ctx.stmt():
            result = self.visit(stmt)

        self.memory = old_scope
        return result

    def visitBind(self, ctx: schemeParser.BindContext):
        return None

    def visitVariable(self, ctx: schemeParser.VariableContext):
        var_name = ctx.getText()

        if var_name in self.memory:
            return self.memory[var_name]
        elif var_name in self.functions:
            return self.functions[var_name]
        # else
        raise NameError(f"Variable not defined: {var_name}")

    def visitLess_than(self, ctx: schemeParser.Less_thanContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return "#t" if self.visit(expr1) < self.visit(expr2) else "#f"

    def visitGreater_than(self, ctx: schemeParser.Greater_thanContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return "#t" if self.visit(expr1) > self.visit(expr2) else "#f"

    def visitEqual(self, ctx: schemeParser.EqualContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return "#t" if self.visit(expr1) == self.visit(expr2) else "#f"

    def visitNot_equal(self, ctx: schemeParser.Not_equalContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return "#t" if self.visit(expr1) != self.visit(expr2) else "#f"

    def visitLess_or_equal(self, ctx: schemeParser.Less_or_equalContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return "#t" if self.visit(expr1) <= self.visit(expr2) else "#f"

    def visitGreater_or_equal(self, ctx: schemeParser.Greater_or_equalContext):
        [_, _, expr1, expr2, _] = list(ctx.getChildren())
        return "#t" if self.visit(expr1) >= self.visit(expr2) else "#f"

    def visitNull_condition(self, ctx: schemeParser.Null_conditionContext):
        [_, _, expr, _] = list(ctx.getChildren())
        value = self.visit(expr)
        return "#t" if not value else "#f"

    def visitAnd_condition(self, ctx: schemeParser.And_conditionContext):
        conditions = ctx.condition()
        for condition in conditions:
            if self.visit(condition) == "#f":
                return "#f"
        return "#t"

    def visitOr_condition(self, ctx: schemeParser.Or_conditionContext):
        conditions = ctx.condition()
        for condition in conditions:
            if self.visit(condition) == "#t":
                return "#t"
        return "#f"

    def visitBoolean_condition(self, ctx: schemeParser.Boolean_conditionContext):
        [value] = list(ctx.getChildren())
        if value.getText() == "#t":
            return True
        return False

    def visitNot(self, ctx: schemeParser.NotContext):
        [_, _, condition, _] = list(ctx.getChildren())
        result = self.visit(condition)
        return "#t" if result == "#f" else "#f"

    def visitConditional(self, ctx: schemeParser.ConditionalContext):
        condition_result = self.visit(ctx.condition())
        # Convertir a booleano solo aquí
        condition = "#t" if condition_result not in [
            0, "#f", False, None] else "#f"
        if condition == "#t":
            return self.visit(ctx.stmt(0))
        return self.visit(ctx.stmt(1))

    def visitConditional_multiple(self, ctx: schemeParser.Conditional_multipleContext):
        clauses = ctx.cond_clause()

        for clause in clauses:
            result = self.visit(clause)
            if result is not None:
                return result

        return None

    def visitNormal_clause(self, ctx: schemeParser.Normal_clauseContext):
        [_, condition, stmt, _] = list(ctx.getChildren())
        condition_result = self.visit(condition)
        # Convertir a booleano solo aquí
        if condition_result not in [0, "#f", False, None]:
            return self.visit(stmt)
        return None

    def visitElse_clause(self, ctx: schemeParser.Else_clauseContext):
        [_, _, stmt, _] = list(ctx.getChildren())
        return self.visit(stmt)

    def visitCondition_function_call(self, ctx: schemeParser.Condition_function_callContext):
        return self.visitStmt_function_call(ctx)

    def visitExprStmt(self, ctx: schemeParser.ExprStmtContext):
        return self.visitChildren(ctx)

    def visitFunction(self, ctx: schemeParser.FunctionContext):
        [_, _, _, name, params, _, *body, _] = list(ctx.getChildren())
        func = Function(
            name=name.getText(),
            params=self.visit(params),
            body=body,
            parent_scope=self.memory.copy()
        )

        self.functions[func.name] = func
        self.memory[func.name] = func
        return func.name

    def visitStmt_function_call(self, ctx: schemeParser.Stmt_function_callContext):
        func_name = ctx.VAR().getText()
        # Modificado para obtener lista de argumentos
        arg_values = [self.visit(arg) for arg in ctx.args().expr()]

        if func_name in self.memory:
            func = self.memory[func_name]
            if isinstance(func, Function):
                # User-defined function
                return self.execute_user_function(func, arg_values)
            else:
                # Built-in function
                if len(arg_values) == 1:  # Para funciones que esperan un solo argumento
                    return func(arg_values[0])
                # Para funciones con múltiples argumentos
                return func(*arg_values)

        if func_name not in self.functions:
            raise NameError(f"Function not defined: {func_name}")

        func = self.functions[func_name]
        return self.execute_user_function(func, arg_values)

    def visitExpr_function_call(self, ctx: schemeParser.Expr_function_callContext):
        return self.visitStmt_function_call(ctx)

    def visitReturn(self, ctx: schemeParser.ReturnContext):
        [_, _, expr, _] = list(ctx.getChildren())
        return self.visit(expr)

    def visitParams(self, ctx: schemeParser.ParamsContext):
        return [var.getText() for var in ctx.VAR()]

    def visitArgs(self, ctx: schemeParser.ArgsContext):
        args = []
        for expr in ctx.expr():
            args.append(self.visit(expr))
        return args

    def visitRead(self, ctx: schemeParser.ReadContext):
        value = input()
        try:
            if '.' in value:
                return float(value)
            return int(value)
        except ValueError:
            return value

    def visitNewline(self, ctx: schemeParser.NewlineContext):
        self.memory['newline']()

    def visitQuote(self, ctx: schemeParser.QuoteContext):
        return self.visit(ctx.list_())

    def visitList_expr(self, ctx: schemeParser.List_exprContext):
        return [self.visit(element) for element in ctx.element()]

    def visitList_element(self, ctx: schemeParser.List_elementContext):
        return self.visit(ctx.expr())

    def execute_user_function(self, func, arg_values):
        """Apply a user-defined function"""
        if len(func.params) != len(arg_values):
            raise TypeError(f"{func.name} expects" +
                            f"{len(func.params)} arguments, received {len(arg_values)}")

        # Create a new variable environment based on the closure
        new_scope = func.parent_scope.copy()

        # Assign arguments to parameters
        for param, arg in zip(func.params, arg_values):
            new_scope[param] = arg

        # Save current environment and switch to new one
        old_memory = self.memory
        self.memory = new_scope

        # Execute function body
        result = None
        for stmt in func.body:
            result = self.visit(stmt)

        # Restore previous environment
        self.memory = old_memory
        return result
