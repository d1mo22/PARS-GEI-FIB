grammar exprs;

root : stmt*
     ;

stmt
     : VAR ':=' expr     # assignacio
     | 'write' VAR       # escriure
     ;
expr 
     : <assoc=right> expr '^' expr    # potencia
     | expr '/' expr    # diviso
     | expr '*' expr    # multiplicio
     | expr '-' expr    # resta
     | expr '+' expr    # suma
     | VAR              # variable
     | NUM              # numero
     ;

VAR : [a-zA-Z]+;
NUM : [0-9]+ ;
WS  : [ \t\n\r]+ -> skip;