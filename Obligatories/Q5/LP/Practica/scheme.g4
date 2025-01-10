grammar scheme;

root : stmt* EOF;

stmt : expr                                         #exprStmt
     | '(' 'define' VAR expr ')'                    #constant
     | '(' 'let' '(' binding+ ')' stmt+ ')'         #let
     | '(' 'display' expr ')'                       #display
     | '(' 'if' condition stmt stmt ')'             #conditional
     | '(' 'cond' cond_clause+ ')'                  #conditional_multiple
     | '(' 'define' '(' VAR params ')' stmt* ')'    #function
     | '(' VAR args ')'                             #stmt_function_call
     | '(' 'return' expr ')'                        #return
     ;

binding : '(' VAR expr ')'             #bind
        ;

cond_clause : '(' condition stmt ')'      #normal_clause
            | '(' 'else' stmt ')'         #else_clause
            ;

params : VAR* ;

args : expr* ;

expr : '(' '/' expr expr ')'          #division
     | '(' '*' expr expr ')'          #multiplication
     | '(' '-' expr expr ')'          #substraction
     | '(' '+' expr expr ')'          #addition
     | '(' 'mod' expr expr ')'        #mod
     | '(' 'read' ')'                 #read
     | '(' 'newline' ')'              #newline
     | condition                      #condition_expr
     | VAR                            #variable
     | NUM                            #number
     | STRING                         #string
     | BOOLEAN                        #boolean
     | '(' VAR args ')'               #expr_function_call
     | '\'' list                      #quote 
     ;

condition
     : '(' '<' expr expr ')'          #less_than
     | '(' '>' expr expr ')'          #greater_than
     | '(' '=' expr expr ')'          #equal
     | '(' '<>' expr expr ')'         #not_equal
     | '(' '<=' expr expr ')'         #less_or_equal
     | '(' '>=' expr expr ')'         #greater_or_equal
     | '(' 'and' condition+ ')'       #and_condition
     | '(' 'or' condition+ ')'        #or_condition
     | '(' 'not' condition ')'        #not
     | '(' 'null?' expr ')'           #null_condition
     | BOOLEAN                        #boolean_condition
     | '(' VAR args ')'               #condition_function_call  
     ;

list : '(' element* ')'               #list_expr
     ;

element : expr                        #list_element
        ;

BOOLEAN : '#t' | '#f' ;

VAR : [a-zA-Z][a-zA-Z0-9_?-]*  ;
NUM : [0-9]+ ;
STRING : '"' .*? '"' ;
COMMENT : ';' ~[\r\n]* -> skip ;
WS : [ \t\r\n]+ -> skip ;
