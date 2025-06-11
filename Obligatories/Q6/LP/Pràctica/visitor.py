from gVisitor import gVisitor
from gParser import gParser
from functools import reduce
import numpy as np


class GVisitor(gVisitor):

    def __init__(self, debug_mode=False):
        """Initialize memory, verb dictionaries and debug mode."""
        self.memory = {}
        self.last_result = None
        self.reduce = reduce
        self.debug_mode = debug_mode

        self.monadic_verbs = {
            '-': np.negative,
            '#': lambda x: np.array([x.size]),
            ']': lambda x: x,
            'i.': lambda x: np.arange(x.item()),
            '*:': lambda x: np.square(x),
        }
        self.dyadic_verbs = {
            '+': np.add,
            '-': np.subtract,
            '*': np.multiply,
            '%': np.floor_divide,
            '|': lambda x, y: np.remainder(y, x),
            '^': np.power,
            '>': lambda x, y: (np.greater(x, y)).astype(int),
            '<': lambda x, y: (np.less(x, y)).astype(int),
            '>=': lambda x, y: (np.greater_equal(x, y)).astype(int),
            '<=': lambda x, y: (np.less_equal(x, y)).astype(int),
            '=': lambda x, y: (np.equal(x, y)).astype(int),
            '<>': lambda x, y: (np.not_equal(x, y)).astype(int),
            ',': lambda x, y: np.concatenate((np.atleast_1d(x).flatten(), np.atleast_1d(y).flatten())),
            '#': lambda x, y: y[x.astype(bool)],
            '{': lambda x, y: y[x],
        }

    def _resolve_verb(self, verb_repr, arity):
        """Looks for a verb, returns if it's callable (adapting arity if needed)."""
        if callable(verb_repr):
            return verb_repr

        if isinstance(verb_repr, str):
            if arity == 1:
                func = self.monadic_verbs.get(verb_repr)
                if func:
                    return func
                func_dyadic = self.dyadic_verbs.get(verb_repr)
                if func_dyadic:
                    if self.debug_mode:
                        print(
                            f"Warning: Using dyadic verb '{verb_repr}' as monadic (applying f(x,x)).")

                    def monadic_wrapper(x, _f=func_dyadic): return _f(x, x)
                    return monadic_wrapper
            elif arity == 2:
                func = self.dyadic_verbs.get(verb_repr)
                if func:
                    return func
                func_monadic = self.monadic_verbs.get(verb_repr)
                if func_monadic:
                    if self.debug_mode:
                        print(
                            f"Warning: Using monadic verb '{verb_repr}' as dyadic (ignoring left argument).")

                    def dyadic_wrapper(x, y, _f=func_monadic): return _f(y)
                    return dyadic_wrapper
        return None

    def visitProgram(self, ctx: gParser.ProgramContext):
        """Visits the root node of the program."""
        for i in range(ctx.getChildCount() - 1):
            child = ctx.getChild(i)
            if isinstance(child, gParser.StatementContext):
                self.visit(child)
        return None

    def visitStatement(self, ctx: gParser.StatementContext):
        """Visits a statement. Prints the final result if it's an expression."""
        if ctx.assignment():
            self.visit(ctx.assignment())
            self.last_result = None
        elif ctx.expr():
            result = self.visit(ctx.expr())
            self.last_result = result
            if result is not None:
                self._print_formatted_result(result)
        elif ctx.NEWLINE():
            self.last_result = None
            pass
        return None

    def _print_formatted_result(self, result):
        """Print results in format."""
        if self.debug_mode:
            print(
                f"DEBUG: _print_formatted_result called with: {result} (Type: {type(result)})")
        if result is None:
            return
        if isinstance(result, np.ndarray):
            output_str = ' '.join(map(str, np.atleast_1d(result).flatten()))
            print(output_str.replace('-', '_'))
        elif callable(result):
            print("<function>")
        else:
            print(str(result).replace('-', '_'))

    def visitAssignment(self, ctx: gParser.AssignmentContext):
        """Visit an assignment."""
        var_name = ctx.IDENTIFIER().getText()
        value = self.visit(ctx.expr())
        if value is not None:
            if self.debug_mode:
                print(
                    f"DEBUG: Assigning to '{var_name}' the value: {value} (Type: {type(value)})")
            self.memory[var_name] = value
        else:
            if self.debug_mode:
                print(
                    f"DEBUG: Expression for '{var_name}' evaluated to None, not assigned.")
        return None

    # Helper Methods for Rule Application

    def _try_apply_conjunction(self, stack):
        """Attempts to apply the conjunction rule '@:'."""
        for i in range(len(stack) - 2, 0, -1):
            if stack[i] == '@:':
                f_repr = stack[i - 1]
                g_repr = stack[i + 1]
                left_is_func = callable(f_repr) or isinstance(f_repr, str)
                right_is_func = callable(g_repr) or isinstance(g_repr, str)

                if left_is_func and right_is_func:
                    f_func = self._resolve_verb(f_repr, 1)
                    g_func = self._resolve_verb(g_repr, 1)
                    if f_func and g_func:
                        if self.debug_mode:
                            print(
                                f"DEBUG: Recognized Conjunction pattern @:: {f_repr} @: {g_repr}")
                        f_name = f_repr if isinstance(f_repr, str) else getattr(
                            f_repr, '__name__', 'derived_f')
                        g_name = g_repr if isinstance(g_repr, str) else getattr(
                            g_repr, '__name__', 'derived_g')

                        def composition_func(y, _f=f_func, _g=g_func, _f_name=f_name, _g_name=g_name, _debug=self.debug_mode):
                            if _debug:
                                print(
                                    f"DEBUG EXEC: composition_func({_f_name} @: {_g_name}) called with y={y}")
                            intermediate = _g(y)
                            if _debug:
                                print(
                                    f"DEBUG EXEC:   intermediate result from {_g_name}({y}) = {intermediate}")
                            if intermediate is None:
                                return None
                            final_result = _f(intermediate)
                            if _debug:
                                print(
                                    f"DEBUG EXEC:   final result from {_f_name}({intermediate}) = {final_result}")
                            return final_result

                        result = composition_func
                        consumed_count = 3
                        replace_start_index = i - 1
                        new_stack = stack[:replace_start_index] + [result] + \
                            stack[replace_start_index + consumed_count:]
                        if self.debug_mode:
                            print(
                                f"DEBUG: Applying Conjunction @:. Result: <function>")
                        if self.debug_mode:
                            print(
                                f"DEBUG: Stack after @:: {[str(item) for item in new_stack]}")
                        return True, new_stack
        return False, stack

    def _try_apply_fork(self, stack):
        """
        Attempts to apply the Fork rule (Func Verb Func/Verb).
        Example: (+ ]) * (- ]) applied to 5 -> (5+5) * (5-5) = 10 * 0 = 0
        """
        if len(stack) >= 3:
            last3 = stack[-3:]
            f_repr, g_repr, h_repr = last3
            is_func_f = callable(f_repr)
            is_dyadic_verb_g = isinstance(g_repr, str)
            is_monadic_repr_h = isinstance(h_repr, str) or callable(h_repr)

            if is_func_f and is_dyadic_verb_g and is_monadic_repr_h:
                f_func = f_repr
                g_func = self._resolve_verb(g_repr, 2)
                h_func = self._resolve_verb(h_repr, 1)

                if g_func and h_func:
                    if self.debug_mode:
                        print(
                            f"DEBUG: Recognized Fork pattern: {f_repr} {g_repr} {h_repr}")
                    f_name = getattr(f_repr, '__name__', 'derived_f')
                    g_name = g_repr
                    h_name = h_repr if isinstance(h_repr, str) else getattr(
                        h_repr, '__name__', 'derived_h')

                    def derived_fork_func(y, _f=f_func, _g=g_func, _h=h_func, _f_n=f_name, _g_n=g_name, _h_n=h_name, _debug=self.debug_mode):
                        if _debug:
                            print(
                                f"DEBUG EXEC: derived_fork_func({_f_n} {_g_n} {_h_n}) called with y={y}")
                        left_arg = _f(y)
                        if _debug:
                            print(
                                f"DEBUG EXEC: left arg from {_f_n}({y}) = {left_arg}")
                        if left_arg is None:
                            return None
                        right_arg = _h(y)
                        if _debug:
                            print(
                                f"DEBUG EXEC: right arg from {_h_n}({y}) = {right_arg}")
                        if right_arg is None:
                            return None
                        final_result = _g(left_arg, right_arg)
                        if _debug:
                            print(
                                f"DEBUG EXEC: final result from {_g_n}({left_arg}, {right_arg}) = {final_result}")
                        return final_result

                    result = derived_fork_func
                    replace_start_index = len(stack) - 3
                    new_stack = stack[:replace_start_index] + [result]
                    if self.debug_mode:
                        print(f"DEBUG: Applying Fork. Result: <function>")
                    if self.debug_mode:
                        print(
                            f"DEBUG: Stack after Fork: {[str(item) for item in new_stack]}")
                    return True, new_stack
        return False, stack

    def _try_apply_hook(self, stack):
        """Attempts to apply the Hook rule (Val Verb Func/Verb)."""
        if len(stack) >= 3:
            last3 = stack[-3:]
            left_val, middle_verb_repr, right_verb_repr = last3
            is_value = isinstance(left_val, np.ndarray)
            is_dyadic_str = isinstance(middle_verb_repr, str)
            is_monadic_repr = isinstance(
                right_verb_repr, str) or callable(right_verb_repr)

            if is_value and is_dyadic_str and is_monadic_repr:
                dyadic_func = self._resolve_verb(middle_verb_repr, 2)
                monadic_func = self._resolve_verb(right_verb_repr, 1)

                if dyadic_func and monadic_func:
                    if self.debug_mode:
                        print(
                            f"DEBUG: Recognized Hook pattern: {left_val} {middle_verb_repr} {right_verb_repr}")
                    fixed_left_value = left_val
                    dyad_name = middle_verb_repr
                    monad_name = right_verb_repr if isinstance(right_verb_repr, str) else getattr(
                        right_verb_repr, '__name__', 'derived_monad')
                    fixed_val_repr = str(fixed_left_value)

                    def derived_hook_func(y, _dyad_f=dyadic_func, _monad_f=monadic_func, _fixed_val=fixed_left_value, _dyad_n=dyad_name, _monad_n=monad_name, _fixed_repr=fixed_val_repr, _debug=self.debug_mode):
                        if _debug:
                            print(
                                f"DEBUG EXEC: derived_hook_func({_fixed_repr} {_dyad_n} {_monad_n}) called with y={y}")
                        right_operand = _monad_f(y)
                        if _debug:
                            print(
                                f"DEBUG EXEC:   right operand from {_monad_n}({y}) = {right_operand}")
                        if right_operand is None:
                            return None
                        final_result = _dyad_f(_fixed_val, right_operand)
                        if _debug:
                            print(
                                f"DEBUG EXEC:   final result from {_dyad_n}({_fixed_repr}, {right_operand}) = {final_result}")
                        return final_result

                    result = derived_hook_func
                    replace_start_index = len(stack) - 3
                    new_stack = stack[:replace_start_index] + [result]
                    if self.debug_mode:
                        print(f"DEBUG: Applying Hook. Result: <function>")
                    if self.debug_mode:
                        print(
                            f"DEBUG: Stack after Hook: {[str(item) for item in new_stack]}")
                    return True, new_stack
        return False, stack

    def _try_apply_adverb(self, stack):
        """Attempts to apply prioritized adverb rules ('/', ':', '~')."""
        for i in range(len(stack) - 1, 0, -1):
            adverb_candidate = stack[i]
            verb_candidate_repr = stack[i-1]

            if (callable(verb_candidate_repr) or isinstance(verb_candidate_repr, str)) and \
               isinstance(adverb_candidate, str) and adverb_candidate in ['/', ':', '~']:

                adverb = adverb_candidate
                verb_repr = verb_candidate_repr
                derived_func = None

                if self.debug_mode:
                    print(
                        f"DEBUG: Potential Adverb pattern found: {verb_repr} {adverb} at index {i-1}, {i}")

                if adverb == '/':
                    verb_func = self._resolve_verb(verb_repr, 2)
                    if verb_func:
                        def fold_func(y, _verb_func=verb_func, _verb_repr=verb_repr, _debug=self.debug_mode):
                            if _debug:
                                print(
                                    f"DEBUG EXEC: fold_func({_verb_repr} /) called with y={y}")
                            if not isinstance(y, np.ndarray):
                                return None
                            flat_y = y.flatten()
                            if flat_y.size == 0:
                                return None
                            if flat_y.size == 1:
                                return np.atleast_1d(flat_y)

                            accumulator = flat_y[-1]
                            for j in range(flat_y.size - 2, -1, -1):
                                accumulator = _verb_func(
                                    flat_y[j], accumulator)
                                if accumulator is None:
                                    return None
                            return np.array([accumulator])
                        derived_func = fold_func

                elif adverb == ':':
                    verb_func = self._resolve_verb(verb_repr, 2)
                    if verb_func:
                        def monadic_apply_func(y, _dyadic_func=verb_func, _verb_repr=verb_repr, _debug=self.debug_mode):
                            if _debug:
                                print(
                                    f"DEBUG EXEC: monadic_apply_func({_verb_repr} :) called with y={y}")
                            return _dyadic_func(y, y)

                        derived_func = monadic_apply_func

                elif adverb == '~':
                    original_diadic = self._resolve_verb(verb_repr, 2)
                    if original_diadic:
                        verb_name = verb_repr if isinstance(verb_repr, str) else getattr(
                            verb_repr, '__name__', 'derived')

                        def smart_flipped_func(*args, _orig_diadic=original_diadic, _v_name=verb_name, _debug=self.debug_mode):
                            if _debug:
                                print(
                                    f"DEBUG EXEC: smart_flipped_func({_v_name} ~) called with args={args}")
                            if len(args) == 1:
                                y = args[0]
                                return _orig_diadic(y, y)
                            elif len(args) == 2:
                                x, y = args
                                return _orig_diadic(y, x)
                            else:
                                return None
                        derived_func = smart_flipped_func
                    else:
                        return None

                if derived_func:
                    result = derived_func
                    consumed_count = 2
                    replace_start_index = i - 1
                    new_stack = stack[:replace_start_index] + [result] + \
                        stack[replace_start_index + consumed_count:]
                    if self.debug_mode:
                        print(
                            f"DEBUG: Aplicando Adverbio {adverb} (priorizado). Resultado: <function>")
                    if self.debug_mode:
                        print(
                            f"DEBUG: Pila después de Adverbio (priorizado): {[str(item) for item in new_stack]}")
                    return True, new_stack
        return False, stack

    def _try_apply_standard(self, stack):
        """Attempts to apply standard dyadic/monadic logic."""
        op_index = -1
        for i in range(len(stack) - 1, -1, -1):
            item = stack[i]
            if isinstance(item, str) or callable(item):
                op_index = i
                break

        if op_index == -1:
            return False, stack  # No operator found

        operator = stack[op_index]
        left1 = stack[op_index - 1] if op_index > 0 else None
        right1 = stack[op_index + 1] if op_index < len(stack) - 1 else None
        left1_is_value = isinstance(left1, np.ndarray)
        right1_is_value = isinstance(right1, np.ndarray)

        if self.debug_mode:
            print(
                f"DEBUG: Standard Logic - op_index={op_index}, operator='{operator}', left1='{left1}', right1='{right1}'")

        result = None
        consumed_count = 0
        replace_start_index = -1
        operation_applied = False

        # Try Dyadic (Value Op Value)
        if left1_is_value and right1_is_value:
            verb_func = self._resolve_verb(operator, 2)
            if verb_func:
                try:
                    result = verb_func(left1, right1)
                    # If verb_func failed internally (and returned None), propagate error
                    if result is None:
                        return True, None
                    consumed_count = 3
                    replace_start_index = op_index - 1
                    operation_applied = True
                    if self.debug_mode:
                        print(f"DEBUG: Applying Dyadic. Op: {operator}")
                except Exception as _:
                    return True, None

        # Try Monadic (Op Value)
        elif right1_is_value and (op_index == 0 or not left1_is_value):
            verb_func = self._resolve_verb(operator, 1)
            if verb_func:
                try:
                    result = verb_func(right1)
                    # If verb_func failed internally (and returned None), propagate error
                    if result is None:
                        return True, None
                    consumed_count = 2
                    replace_start_index = op_index
                    operation_applied = True
                    op_name = operator if isinstance(operator, str) else getattr(
                        operator, '__name__', '<derived function>')
                    if self.debug_mode:
                        print(f"DEBUG: Applying Monadic. Op: {op_name}")
                except Exception as _:
                    return True, None

        if operation_applied:
            if self.debug_mode:
                print(
                    f"DEBUG: Standard operation applied: {operator if isinstance(operator, str) else '<derived function>'}")
            new_stack = stack[:replace_start_index] + [result] + \
                stack[replace_start_index + consumed_count:]
            if self.debug_mode:
                print(
                    f"DEBUG: Stack after standard op: {[str(item) for item in new_stack]}")
            return True, new_stack
        else:
            return False, stack  # No standard operation was applied

    # Main expression evaluation method

    def visitExpr(self, ctx: gParser.ExprContext):
        """
        Evaluates a complete G expression using stack-based evaluation.

        Process:
        1. Evaluates all initial items
        2. Applies rules in order of priority until reduced to a single value:
            - Conjunction (@:)
            - Fork (func verb func)
            - Hook (val verb func)
            - Adverbs (/, :, ~)
            - Standard operations (monadic/dyadic)
        """

        items_ctx = ctx.item()
        if not items_ctx:
            return None

        # 1. Evaluate all initial items
        evaluated_items = []
        for item_ctx in items_ctx:
            evaluated_item = self.visit(item_ctx)
            # Allow verbs/adverbs/conjunctions as strings initially
            is_operator_str = isinstance(evaluated_item, str) and evaluated_item in [
                '/', ':', '~', '@:']
            if evaluated_item is None and not isinstance(item_ctx, gParser.ItemVerbContext) and not is_operator_str:
                if self.debug_mode:
                    print(
                        f"DEBUG: Error evaluating initial item: {item_ctx.getText()}")
                return None  # Propagate error if not an unresolved verb/op
            evaluated_items.append(evaluated_item)

        stack = list(evaluated_items)

        if len(stack) == 1:
            item = stack[0]
            if isinstance(item, (int, float, np.number)):
                return np.array([item])
            return item

        # 2. Stack reduction loop
        while len(stack) > 1:
            if self.debug_mode:
                print(f"\nDEBUG: Start visitExpr loop iteration.")
                print(f"DEBUG: Current stack: {[str(item) for item in stack]}")

            processed = False

            # Try to apply rules in priority order
            processed, stack = self._try_apply_conjunction(stack)
            if stack is None:
                return None  # Propagate error
            if processed:
                continue

            processed, stack = self._try_apply_fork(stack)
            if stack is None:
                return None
            if processed:
                continue

            processed, stack = self._try_apply_hook(stack)
            if stack is None:
                return None
            if processed:
                continue

            processed, stack = self._try_apply_adverb(stack)
            if stack is None:
                return None
            if processed:
                continue

            processed, stack = self._try_apply_standard(stack)
            if stack is None:
                return None
            if processed:
                continue

            # If NO operation was applied in this iteration
            if not processed:
                if self.debug_mode:
                    print(
                        f"DEBUG: No operation applied in this iteration. Stack: {[str(item) for item in stack]}. Ending loop.")
                if len(stack) > 1:
                    is_pending_monadic = (len(stack) == 2 and (callable(stack[0]) or isinstance(
                        stack[0], str)) and isinstance(stack[1], np.ndarray))
                    if not is_pending_monadic:
                        return None  # Return None in case of invalid incomplete evaluation
                # Exit loop (could be valid final state or already reported error)
                break

            if self.debug_mode:
                print(f"DEBUG: End visitExpr loop iteration.")

        # Return final result
        if len(stack) == 1:
            final_result = stack[0]
            if isinstance(final_result, (int, float, np.number)):
                return np.array([final_result])
            return final_result

        elif len(stack) == 0:  # Error case where stack became empty
            if self.debug_mode:
                print("DEBUG: visitExpr ending with empty stack.")
            return None
        # If loop ended but stack has > 1 element (uncaught error before)
        else:
            if self.debug_mode:
                print(
                    f"DEBUG: visitExpr ending with anomalous stack: {[str(s) for s in stack]}")

            # Check if it's the 'func value' case which is valid as partial final state
            is_pending_monadic = (len(stack) == 2 and (callable(stack[0]) or isinstance(
                stack[0], str)) and isinstance(stack[1], np.ndarray))
        if not is_pending_monadic:
            return None
            # Even if it's 'func value', it's not a directly printable final result, could be considered error or intermediate state
        return None  # Return None if evaluation didn't complete to a single value/function

    # --- Visit Methods for Items ---
    def visitItemValue(self, ctx: gParser.ItemValueContext):
        return self.visit(ctx.value())

    def visitItemVerb(self, ctx: gParser.ItemVerbContext):
        verb_text = ctx.getText()
        # Resolve identifiers that could be defined verbs
        if verb_text in self.memory:
            resolved = self.memory[verb_text]
            if callable(resolved):
                return resolved  # Return function if it's a defined verb
            # If it's a value in memory, it will be handled as value, not verb
            # return resolved # This would cause problems if 'a = 1 2' and then 'a + 3'
        # Return string of primitive or unresolved verb
        return verb_text

    def visitItemAdverb(self, ctx: gParser.ItemAdverbContext):
        return ctx.getText()

    def visitItemConjunction(self, ctx: gParser.ItemConjunctionContext):
        return ctx.getText()

    def visitItemTilde(self, ctx: gParser.ItemTildeContext):
        return '~'

    # Visit methods for values
    def visitValueNumber(self, ctx: gParser.ValueNumberContext):
        numbers_text = [num.getText() for num in ctx.NUMBER()]
        values = []
        for num_str in numbers_text:
            if num_str.startswith('_'):
                values.append(int(num_str[1:]) * -1)
            else:
                values.append(int(num_str))
        return np.array(values, dtype=int)

    def visitValueId(self, ctx: gParser.ValueIdContext):
        var_name = ctx.IDENTIFIER().getText()
        if var_name in self.memory:
            return self.memory[var_name]
        else:
            return None

    def visitValueExpr(self, ctx: gParser.ValueExprContext):
        return self.visit(ctx.expr())
