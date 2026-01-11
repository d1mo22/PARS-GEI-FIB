symbolicOutput(0).  % set to 1 to see symbolic output only; 0 otherwise.

%% 6 points.
%% Extend this Prolog source to do car-sequencing: in a production line of a car factory,
%% decide in which order to produce a set of cars.  Each car to be produced has a list of
%% special options (air-conditioning, sun-roof, etc.).  Each option is installed in a different
%% zone along the production line, and in order not to delay the line, at most 2 out of each 4
%% consecutive cars can have a sun-roof, and similar constraints apply for the other options.

%% Example input with 15 cars and 5 options:
car( 1, [      4,5] ).   % car 1 needs options 4 and 5 to be installed. For example, option 4 could be the sun-roof.
car( 2, [1,    4  ] ).
car( 3, [  2,3,  5] ).
car( 4, [1,2,3,4  ] ).
car( 5, [  2,3,  5] ).
car( 6, [1,2,3,4,5] ).
car( 7, [1,    4,5] ).
car( 8, [1,2,3,  5] ).
car( 9, [1        ] ).
car(10, [1,  3,  5] ).
car(11, [  2      ] ).
car(12, [  2      ] ).
car(13, [1,2,    5] ).
car(14, [  2,  4  ] ).
car(15, [    3    ] ).

option( 1,  2, 3 ).  % Option 1 can be in at most 2 cars of each "window" of 3 consecutive positions in the sequence.
option( 2,  3, 4 ).      %Note: possible windows of size 3 are positions 1,2,3; positions 2,3,4; etc. until 13,14,15.
option( 3,  2, 4 ).
option( 4,  2, 4 ).
option( 5,  3, 5 ).

% One possible example of correct output:
%
%                      options:  
% position  1 car 10:  1   3   5
% position  2 car 14:    2   4  
% position  3 car  8:  1 2 3   5
% position  4 car 13:  1 2     5
% position  5 car 15:      3    
% position  6 car  9:  1        
% position  7 car  6:  1 2 3 4 5
% position  8 car 12:    2      
% position  9 car  5:    2 3   5
% position 10 car  7:  1     4 5
% position 11 car  4:  1 2 3 4  
% position 12 car 11:    2      
% position 13 car  3:    2 3   5
% position 14 car  2:  1     4  
% position 15 car  1:        4 5



%%%%%% Some helpful definitions to make the code cleaner:
car(C):- car(C,_).
position(P):- car(P,_).
carOption(C,Opt):- car(C,Opts), member(Opt,Opts).
option(Opt):- option(Opt,_,_).
windowOfSize(WindowSize, WindowStart, WindowEnd):-
    position(WindowStart), WindowEnd is WindowStart+WindowSize-1, position(WindowEnd).

%%%%%%  1. SAT Variables:
satVariable( carPos(C,P)   ):- car(C), position(P).       % "car C is produced at position P in the sequence."
satVariable( posOpt(P,Opt) ):- position(P), option(Opt).  % "at position P in the sequence a car with Opt is produced"

%%%%%%  2. Clause generation:
writeClauses:-
    eachCarExactlyOnePosition,
    eachPositionExactlyOneCar,
    relateCarPosAndPosOpt,
    optionConstraints,
    true.
writeClauses:- told, nl, write('Error: writeClauses failed!'), nl,nl, halt.

eachCarExactlyOnePosition:- car(C),      findall( carPos(C,P), position(P), Lits ), exactly(1,Lits), fail.
eachCarExactlyOnePosition.

eachPositionExactlyOneCar:- position(P), findall( carPos(C,P), car(C),      Lits ), exactly(1,Lits), fail.
eachPositionExactlyOneCar.

relateCarPosAndPosOpt:- carOption(C,Opt), position(P), writeOneClause([ -carPos(C,P), posOpt(P,Opt) ]), fail.
relateCarPosAndPosOpt.

optionConstraints:-
    option(Opt,Max,WindowSize),
    windowOfSize(WindowSize, WindowStart, WindowEnd),
    findall( posOpt(P,Opt), between(WindowStart,WindowEnd,P), Lits ),
    atMost(Max,Lits), fail.
optionConstraints.


%%%%%%  3. DisplaySol: show the solution. Here M contains the literals that are true in the model:
% displaySol(M):- write(M), nl, fail.
displaySol(M):- nl, write('             options:  '), position(P), nl, write2(P), 
		member(carPos(C,P), M ), write(' car '), write2(C), write(': '),
		car(C,Options), writeOptions(Options), fail.
displaySol(_):- nl.

writeOptions(Options):- option(Opt), wop(Opt,Options), fail.
writeOptions(_).

wop(Opt,Options):- member(Opt,Options), !, write(' '), write(Opt),!.
wop(_,_        ):-                         write('  '),!.
    
write2(P):- P < 10, write(' '), write(P),!.
write2(P):- write(P),!.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Everything below is given as a standard library, reusable for solving
%%    with SAT many different problems.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% Cardinality constraints on arbitrary sets of literals Lits: ===========================

exactly(K,Lits):- symbolicOutput(1), write( exactly(K,Lits) ), nl, !.
exactly(K,Lits):- atLeast(K,Lits), atMost(K,Lits),!.

atMost(K,Lits):- symbolicOutput(1), write( atMost(K,Lits) ), nl, !.
atMost(K,Lits):-   % l1+...+ln <= k:  in all subsets of size k+1, at least one is false:
      negateAll(Lits,NLits),
      K1 is K+1,    subsetOfSize(K1,NLits,Clause), writeOneClause(Clause),fail.
atMost(_,_).

atLeast(K,Lits):- symbolicOutput(1), write( atLeast(K,Lits) ), nl, !.
atLeast(K,Lits):-  % l1+...+ln >= k: in all subsets of size n-k+1, at least one is true:
      length(Lits,N),
      K1 is N-K+1,  subsetOfSize(K1, Lits,Clause), writeOneClause(Clause),fail.
atLeast(_,_).

negateAll( [], [] ).
negateAll( [Lit|Lits], [NLit|NLits] ):- negate(Lit,NLit), negateAll( Lits, NLits ),!.

negate( -Var,  Var):-!.
negate(  Var, -Var):-!.

subsetOfSize(0,_,[]):-!.
subsetOfSize(N,[X|L],[X|S]):- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ):-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).


%%%%%%% Express equivalence between a variable and a disjunction or conjunction of literals ===

% Express that Var is equivalent to the disjunction of Lits:
expressOr( Var, Lits ):- symbolicOutput(1), write( Var ), write(' <--> or('), write(Lits), write(')'), nl, !.
expressOr( Var, Lits ):- member(Lit,Lits), negate(Lit,NLit), writeOneClause([ NLit, Var ]), fail.
expressOr( Var, Lits ):- negate(Var,NVar), writeOneClause([ NVar | Lits ]),!.

%% expressOr(a,[x,y]) genera 3 clausulas (como en la Transformación de Tseitin):
%% a == x v y
%% x -> a       -x v a
%% y -> a       -y v a
%% a -> x v y   -a v x v y

% Express that Var is equivalent to the conjunction of Lits:
expressAnd( Var, Lits) :- symbolicOutput(1), write( Var ), write(' <--> and('), write(Lits), write(')'), nl, !.
expressAnd( Var, Lits):- member(Lit,Lits), negate(Var,NVar), writeOneClause([ NVar, Lit ]), fail.
expressAnd( Var, Lits):- findall(NLit, (member(Lit,Lits), negate(Lit,NLit)), NLits), writeOneClause([ Var | NLits]), !.


%%%%%%% main: =================================================================================

main:-  symbolicOutput(1), !, writeClauses, halt.   % print the clauses in symbolic form and halt Prolog
main:-  initClauseGeneration,
        tell(clauses), writeClauses, told,          % generate the (numeric) SAT clauses and call the solver
        tell(header),  writeHeader,  told,
        numVars(N), numClauses(C),
        write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
        shell('cat header clauses > infile.cnf',_),
        write('Calling solver....'), nl,
        shell('kissat -v infile.cnf > model', Result),  % if sat: Result=10; if unsat: Result=20.
        treatResult(Result),!.

treatResult(20):- write('Unsatisfiable'), nl, halt.
treatResult(10):- write('Solution found: '), nl, see(model), symbolicModel(M), seen, displaySol(M), nl,nl,halt.
treatResult( _):- write('cnf input error. Wrote anything strange in your cnf?'), nl,nl, halt.


initClauseGeneration:-  %initialize all info about variables and clauses:
        retractall(numClauses(   _)),
        retractall(numVars(      _)),
        retractall(varNumber(_,_,_)),
        assert(numClauses( 0 )),
        assert(numVars(    0 )),     !.

writeOneClause([]):- symbolicOutput(1),!, nl.
writeOneClause([]):- countClause, write(0), nl.
writeOneClause([Lit|C]):- w(Lit), writeOneClause(C),!.
w(-Var):- symbolicOutput(1), satVariable(Var), write(-Var), write(' '),!.
w( Var):- symbolicOutput(1), satVariable(Var), write( Var), write(' '),!.
w(-Var):- satVariable(Var),  var2num(Var,N),   write(-), write(N), write(' '),!.
w( Var):- satVariable(Var),  var2num(Var,N),             write(N), write(' '),!.
w( Lit):- told, write('ERROR: generating clause with undeclared variable in literal '), write(Lit), nl,nl, halt.


% given the symbolic variable V, find its variable number N in the SAT solver:
:-dynamic(varNumber / 3).
var2num(V,N):- hash_term(V,Key), existsOrCreate(V,Key,N),!.
existsOrCreate(V,Key,N):- varNumber(Key,V,N),!.                            % V already existed with num N
existsOrCreate(V,Key,N):- newVarNumber(N), assert(varNumber(Key,V,N)), !.  % otherwise, introduce new N for V

writeHeader:- numVars(N),numClauses(C), write('p cnf '),write(N), write(' '),write(C),nl.

countClause:-     retract( numClauses(N0) ), N is N0+1, assert( numClauses(N) ),!.
newVarNumber(N):- retract( numVars(   N0) ), N is N0+1, assert(    numVars(N) ),!.

% Getting the symbolic model M from the output file:
symbolicModel(M):- get_code(Char), readWord(Char,W), symbolicModel(M1), addIfPositiveInt(W,M1,M),!.
symbolicModel([]).
addIfPositiveInt(W,L,[Var|L]):- W = [C|_], between(48,57,C), number_codes(N,W), N>0, varNumber(_,Var,N),!.
addIfPositiveInt(_,L,L).
readWord( 99,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ c
readWord(115,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ s
readWord(-1,_):-!, fail. %end of file
readWord(C,[]):- member(C,[10,32]), !. % newline or white space marks end of word
readWord(Char,[Char|W]):- get_code(Char1), readWord(Char1,W), !.

%%%%%%% =======================================================================================
