grammar exprs;

// Regla principal que contiene múltiples sentencias
root : stmt* ;

// Definición de las sentencias
stmt
     : VAR ':=' expr                   # assignacio
     | 'write' expr                    # escriure
     | 'if' condition 'then' stmt* 'end' # condicional
     | 'while' condition 'do' stmt* 'end' # bucle
     | 'function' VAR '(' params? ')' stmt* 'end' # funcion
     | VAR '(' args? ')'              # llamada
     | 'return' expr                  # retorno
      ;

params : VAR (',' VAR)* ;

args : expr (',' expr)* ;

// Definición de las condiciones
condition
     : expr '<' expr     # less_than
     | expr '>' expr     # greater_than
     | expr '=' expr     # equal
     | expr '<>' expr    # not_equal
     | expr '<=' expr    # less_or_equal
     | expr '>=' expr    # greater_or_equal
      ;

// Definición de las expresiones aritméticas
expr 
     : <assoc=right> expr '^' expr    # potencia
     | expr '/' expr                   # diviso
     | expr '*' expr                   # multiplicio
     | expr '-' expr                   # resta
     | expr '+' expr                   # suma
     | VAR                            # variable
     | NUM                            # numero
     | VAR '(' args? ')'              # llamadaFuncion
     | '(' expr ')'                   # parentesis
     ;

// Definición de tokens
VAR : [a-zA-Z][a-zA-Z0-9_]* ;  // Identificadores empiezan con letra
NUM : [0-9]+ ;
WS  : [ \t\n\r]+ -> skip ;     // Ignorar espacios en blanco
LEXICAL_ERROR : . ;           // Manejar errores léxicos