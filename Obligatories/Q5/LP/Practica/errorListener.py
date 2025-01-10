from antlr4 import error


class ErrorListener(error.ErrorListener.ErrorListener):
    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        print(f"Syntax error at line {line}:{column}")
        print(f"  → {msg}")
        if offendingSymbol:
            print(f"  → Problematic token: {offendingSymbol.text}")
