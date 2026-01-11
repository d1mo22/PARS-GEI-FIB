grammar g;

// Initial rule: a program is a sequence of statements
program: statement* EOF;

// A statement can be an assignment, an expression followed by a newline, or an empty line
statement
    : assignment NEWLINE?
    | expr NEWLINE?
    | NEWLINE // Allows blank lines
    ;

// Variable or function assignment
assignment: IDENTIFIER '=:' expr;

// Expression: A sequence of one or more 'items'
// Evaluation (right-to-left, monadic/dyadic application, adverbs) is handled in the Visitor.
expr: item+ ;

// Items that can compose an expression
item
    : value       # ItemValue// Data (numbers, identifiers, parentheses)
    | verb        # ItemVerb // Basic operations (+, -, *, #, i., etc.)
    | adverb      # ItemAdverb// Verb modifiers (/, :)
    | conjunction # ItemConjunction// Verb combinators (@:)
    | '~'       # ItemTilde// Special modifier (flip ~)
    ;

// Basic values or grouped expressions
value
    : NUMBER+      # ValueNumber// A sequence of numbers is a list/vector
    | IDENTIFIER   # ValueId// Reference to a variable or function
    | '(' expr ')' #ValueExpr// Expression in parentheses
    ;

// Verbs: Operations that can be monadic or dyadic
verb
    : '+' | '-' | '*' | '%' | '|' | '^'         // Arithmetic
    | '>' | '<' | '>=' | '<=' | '=' | '<>'      // Relational
    | ']'    // ] Identity
    | ','       // , Concatenate
    | '#'        // # Size / Filter
    | '{'      // { Index
    | 'i.'       // i. Generate sequence 0..n-1
    ;

// Adverbs: Modify the immediately preceding verb (handled in Visitor)
adverb: '/' | ':' ; // / (fold), : (monadic)

// Conjunctions: Combine verbs (handled in Visitor)
conjunction: '@:' ; // @: (composition)


NEWLINE  : '\r'? '\n' ; // To separate statements

// Numbers (including negatives with _)
NUMBER: '_'? [0-9]+ ;

// Identifiers
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]* ;

// Ignore whitespace (except newlines) and comments
WS          : [ \t]+ -> skip ;
LINE_COMMENT: 'NB.' ~[\r\n]* -> skip ;
