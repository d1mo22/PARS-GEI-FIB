%% We are given a number of people of different ages and from different families (see the input below).
%% Complete the prolog template below that uses a SAT solver in order to make a commitee such that:
%%   -it has exactly one member per family
%%   -it has at least one and most two people of each age
%%   -if two people of the same age are in the committee, then they must have the same animal.
%% 
%% One possible correct output for the input example below is:
%% 
%% family1:  [76,age18,dog]
%% family2:  [66,age19,cat]
%% family3:  [37,age18,dog]
%% family4:  [77,age21,dog]
%% family5:  [72,age19,cat]
%% family6:  [73,age22,dog]
%% family7:  [38,age24,cat]
%% family8:  [26,age20,dog]
%% family9:  [75,age23,dog]



personInfo(  1,  age24,  family4,  dog  ).
personInfo(  2,  age23,  family5,  cat  ).
personInfo(  3,  age19,  family3,  dog  ).
personInfo(  4,  age24,  family3,  cat  ).
personInfo(  5,  age18,  family3,  dog  ).
personInfo(  6,  age24,  family9,  dog  ).
personInfo(  7,  age20,  family2,  cat  ).
personInfo(  8,  age21,  family6,  dog  ).
personInfo(  9,  age19,  family1,  cat  ).
personInfo( 10,  age19,  family9,  cat  ).
personInfo( 11,  age18,  family8,  dog  ).
personInfo( 12,  age22,  family2,  dog  ).
personInfo( 13,  age24,  family1,  dog  ).
personInfo( 14,  age19,  family3,  cat  ).
personInfo( 15,  age22,  family6,  cat  ).
personInfo( 16,  age21,  family7,  dog  ).
personInfo( 17,  age22,  family2,  cat  ).
personInfo( 18,  age21,  family9,  cat  ).
personInfo( 19,  age22,  family2,  dog  ).
personInfo( 20,  age22,  family8,  cat  ).
personInfo( 21,  age22,  family6,  dog  ).
personInfo( 22,  age23,  family8,  dog  ).
personInfo( 23,  age24,  family1,  cat  ).
personInfo( 24,  age23,  family8,  cat  ).
personInfo( 25,  age23,  family7,  dog  ).
personInfo( 26,  age20,  family8,  dog  ).
personInfo( 27,  age21,  family5,  cat  ).
personInfo( 28,  age19,  family7,  cat  ).
personInfo( 29,  age22,  family8,  dog  ).
personInfo( 30,  age21,  family6,  dog  ).
personInfo( 31,  age18,  family4,  cat  ).
personInfo( 32,  age19,  family5,  cat  ).
personInfo( 33,  age18,  family7,  dog  ).
personInfo( 34,  age22,  family4,  cat  ).
personInfo( 35,  age18,  family1,  cat  ).
personInfo( 36,  age23,  family1,  cat  ).
personInfo( 37,  age18,  family3,  dog  ).
personInfo( 38,  age24,  family7,  cat  ).
personInfo( 39,  age21,  family8,  cat  ).
personInfo( 40,  age18,  family4,  dog  ).
personInfo( 41,  age19,  family9,  dog  ).
personInfo( 42,  age21,  family9,  cat  ).
personInfo( 43,  age19,  family1,  dog  ).
personInfo( 44,  age18,  family4,  cat  ).
personInfo( 45,  age22,  family6,  cat  ).
personInfo( 46,  age19,  family7,  dog  ).
personInfo( 47,  age20,  family2,  dog  ).
personInfo( 48,  age18,  family1,  cat  ).
personInfo( 49,  age24,  family1,  dog  ).
personInfo( 50,  age18,  family1,  cat  ).
personInfo( 51,  age18,  family5,  cat  ).
personInfo( 52,  age24,  family5,  cat  ).
personInfo( 53,  age21,  family6,  cat  ).
personInfo( 54,  age20,  family9,  cat  ).
personInfo( 55,  age21,  family7,  dog  ).
personInfo( 56,  age19,  family6,  dog  ).
personInfo( 57,  age19,  family4,  cat  ).
personInfo( 58,  age23,  family2,  cat  ).
personInfo( 59,  age18,  family7,  dog  ).
personInfo( 60,  age18,  family2,  dog  ).
personInfo( 61,  age22,  family7,  dog  ).
personInfo( 62,  age23,  family9,  dog  ).
personInfo( 63,  age19,  family7,  dog  ).
personInfo( 64,  age22,  family8,  dog  ).
personInfo( 65,  age18,  family6,  cat  ).
personInfo( 66,  age19,  family2,  cat  ).
personInfo( 67,  age23,  family7,  cat  ).
personInfo( 68,  age23,  family4,  cat  ).
personInfo( 69,  age22,  family7,  cat  ).
personInfo( 70,  age20,  family1,  cat  ).
personInfo( 71,  age24,  family6,  cat  ).
personInfo( 72,  age19,  family5,  cat  ).
personInfo( 73,  age22,  family6,  dog  ).
personInfo( 74,  age24,  family8,  cat  ).
personInfo( 75,  age23,  family9,  dog  ).
personInfo( 76,  age18,  family1,  dog  ).
personInfo( 77,  age21,  family4,  dog  ).
personInfo( 78,  age21,  family1,  dog  ).
personInfo( 79,  age22,  family1,  cat  ).
personInfo( 80,  age23,  family7,  cat  ).




%Helpful prolog predicates

person(P):- personInfo(P,_,_,_).
age(A):-    personInfo(_,A,_,_).
family(F):- personInfo(_,_,F,_).


%%%%%%% =======================================================================================
%
% Our LI Prolog template for solving problems using a SAT solver.
% 
% It generates the SAT clauses, calls the SAT solver, and shows the solution. Just specify:
%       1. SAT Variables
%       2. Clause generation
%       3. DisplaySol: show the solution.
%
%%%%%%% =======================================================================================

symbolicOutput(0).

%%%%%%  1. SAT Variables:

satVariable( sel(P) ):- person(P). %   "person P is selected for the committee"

%%%%%%  2. Clause generation for the SAT solver:

writeClauses:-
    onePerFamily,
    ageRange,
    notDifferentAnimals,
    true,!.
writeClauses:- told, nl, write('writeClauses failed!'), nl,nl, halt.

onePerFamily:- family(F), findall( sel(P), personInfo(P,_,F,_), Lits ), exactly(1,Lits), fail.
onePerFamily.

ageRange:- age(A), findall( sel(P), personInfo(P,A,_,_), Lits ), atLeast(1,Lits), atMost(2,Lits), fail.
ageRange.

notDifferentAnimals:- personInfo(P1,Age,_,Animal1), personInfo(P2,Age,_,Animal2), Animal1 \= Animal2,
		      writeOneClause([ -sel(P1), -sel(P2) ]), fail. 
notDifferentAnimals.

%%%%%%  3. DisplaySol: show the solution. Here M contains the literals that are true in the model:

%displaySol(M):- nl, write(M), nl, nl, fail.
displaySol(M):- findall(F,family(F),Fams0), sort(Fams0,Fams),
		member(F,Fams),
		member(sel(P),M), personInfo(P,A,F,An), 
		write(F), write(':  '), write([P,A,An]), nl, fail.
displaySol(_).


%%%%%%% =======================================================================================



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
