
symbolicOutput(0).  % set to 1 for DEBUGGING: to see symbolic output only; 0 otherwise.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% To use this prolog template for other optimization problems, complete the missing code represented
%% by %% ... in parts 2,4 below.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Gold Storage Optimization Problem
%
% A distant country stores its gold reserves in the form of bars of varying lengths. These gold bars 
% need to be packed into containers of a fixed length MaxL. Due to traditional manual cutting methods, 
% it can be guaranteed that all bar lengths will be pairwise distinct and never exceed length MaxL. 
% Each container can hold multiple bars, provided the total length of the bars in the container does 
% not exceed MaxL. There is no limit to the number of containers that can be used. The containers used 
% in the solution must have consecutive numbers starting at 1.
%
% The goal is to minimize the number of containers used to store all the gold bars.
%
% The input files contain:
% 1. The lengths of the gold bars (list L in barLengths(L))
% 2. The fixed length of containers (MaxL in containerLength(MaxL)).
%
% Determine the minimum number of containers required to store all the gold bars, while satisfying
% the above constraints. Inefficient solutions will be penalized.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%% Some helpful definitions to make the code cleaner: ====================================

bar(I)         :- barLengths(L), member(I,L).                  % I is a bar
numBars(N)     :- barLengths(L), length(L,N).                  % N is the number of bars
container(J)   :- numBars(N), between(1,N,J).                  % J is a container

%%%%%%% End helpful definitions ===============================================================


%%%%%%%  1. Declare SAT variables to be used: =================================================

% these SAT variables are mandatory 
satVariable( bc(I,J) ) :- bar(I), container(J). % bar I is placed in container J
satVariable( c(J) )    :- container(J).         % containers 1, 2,...,J are used


%%%%%%%  2. Clause generation for the SAT solver: =============================================

% This predicate writeClauses(MaxCost) generates the clauses that guarantee that
% a solution with cost at most MaxCost is found

writeClauses(infinite) :- !, numBars(N), writeClauses(N),!.
writeClauses(MaxContainers) :-
    eachBarOneContainer(MaxContainers),      % Done
    barsDontExceedLength(MaxContainers),     % total length of bars in each container <= MaxL
    relateVariables(MaxContainers),          
    containersAreConsecutive(MaxContainers),
    true,!.
writeClauses(_) :- told, nl, write('writeClauses failed!'), nl,nl, halt.


% generateSubset(K1,K2,S,Sm): Sm is a subset of S with sum s.t. K1 < S <= K2
generate_subset(K1, K2, [E|_], [E]) :- E > K1, E =< K2.
generate_subset(K1, K2, [X|S1], [X|S2]) :-
    K1P is K1 - X, K2P is K2 - X,
    generate_subset(K1P, K2P, S1, S2).
generate_subset(K1, K2, [_|S1], S2) :-
    generate_subset(K1, K2, S1, S2).

% generate a minimal subset with sum > K1
% minSubset(K1,L,Sm): Sm is a subset of L with sum > K1 s.t. if an element is
%                    removed from Sm, its sum is <= K1
minSubset(K1, L, Sm) :-
    max_list(L, Max),
    K2 is K1 + Max,
    generate_subset(K1, K2, L, Sm),
    sum_list(Sm, S),
    min_list(Sm, Min), S-Min =< K1.


barsDontExceedLength(MaxContainers) :-
    between(1,MaxContainers,J), 
    containerLength(MaxL), barLengths(L),
    minSubset(MaxL,L,S),

    findall(bc(I,J), member(I,S), Lits),
    negateAll(Lits, Nlits),
    writeOneClause(Nlits),
    fail.
barsDontExceedLength(_).

eachBarOneContainer(MaxContainers) :-
    bar(I),
    findall(bc(I,J), between(1, MaxContainers, J), Lits),
    exactly(1, Lits), fail.
eachBarOneContainer(_).

relateVariables(MaxContainers) :-
    between(1, MaxContainers, J),
    findall(bc(I,J), bar(I), Lits),
    expressOr(c(J), Lits), 
    fail.
relateVariables(_).

containersAreConsecutive(MaxContainers) :-
    between(2, MaxContainers, J),
    Jprev is J - 1,
    writeOneClause([-c(J), c(Jprev)]),
    fail.
containersAreConsecutive(_).

%%%%%%%  3. DisplaySol: this predicate displays a given solution M: ===========================

%displaySol(M):- nl, write(M), nl, nl, fail.
displaySol(_) :-
    containerLength(MaxL),
    write("Container length: "), write(MaxL), nl, fail.
displaySol(M) :-
    container(J), findall(I, member(bc(I,J),M), L1),
    L1 \= [], sort(L1,L1s),
    write("Container "), write(J), write(": "), write(L1s),
    sum_list(L1s,N), write("\tsum="), write(N), nl, fail.
displaySol(_).

%%%%%%%  4. This predicate computes the cost of a given solution M: ===========================

%% NOTE: we recommend using variables bc(I,J) instead of variables c(J) to express the cost.
costOfThisSolution(M,Cost) :-
    findall(J, member(bc(_, J), M), L),
    max_list(L, Cost), !.
    

%%%%%%% =======================================================================================



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Everything below is given as a standard library, reusable for solving
%%    with SAT many different problems.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% Cardinality constraints on arbitrary sets of literals Lits: ===========================

exactly(K,Lits) :- symbolicOutput(1), write( exactly(K,Lits) ), nl, !.
exactly(K,Lits) :- atLeast(K,Lits), atMost(K,Lits),!.

atMost(K,Lits) :- symbolicOutput(1), write( atMost(K,Lits) ), nl, !.
atMost(K,Lits) :-   % l1+...+ln <= k:  in all subsets of size k+1, at least one is false:
      negateAll(Lits,NLits),
      K1 is K+1,    subsetOfSize(K1,NLits,Clause), writeOneClause(Clause),fail.
atMost(_,_).

atLeast(K,Lits) :- symbolicOutput(1), write( atLeast(K,Lits) ), nl, !.
atLeast(K,Lits) :-  % l1+...+ln >= k: in all subsets of size n-k+1, at least one is true:
      length(Lits,N),
      K1 is N-K+1,  subsetOfSize(K1, Lits,Clause), writeOneClause(Clause),fail.
atLeast(_,_).

negateAll( [], [] ).
negateAll( [Lit|Lits], [NLit|NLits] ) :- negate(Lit,NLit), negateAll( Lits, NLits ),!.

negate( -Var,  Var) :- !.
negate(  Var, -Var) :- !.

subsetOfSize(0,_,[]) :- !.
subsetOfSize(N,[X|L],[X|S]) :- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ) :-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).


%%%%%%% Express equivalence between a variable and a disjunction or conjunction of literals ===

% Express that Var is equivalent to the disjunction of Lits:
expressOr( Var, Lits ) :- symbolicOutput(1), write( Var ), write(' <--> or('), write(Lits), write(')'), nl, !.
expressOr( Var, Lits ) :- member(Lit,Lits), negate(Lit,NLit), writeOneClause([ NLit, Var ]), fail.
expressOr( Var, Lits ) :- negate(Var,NVar), writeOneClause([ NVar | Lits ]),!.

%% expressOr(a,[x,y]) genera 3 clausulas (como en la Transformación de Tseitin):
%% a == x v y
%% x -> a       -x v a
%% y -> a       -y v a
%% a -> x v y   -a v x v y

% Express that Var is equivalent to the conjunction of Lits:
expressAnd( Var, Lits) :- symbolicOutput(1), write( Var ), write(' <--> and('), write(Lits), write(')'), nl, !.
expressAnd( Var, Lits) :- member(Lit,Lits), negate(Var,NVar), writeOneClause([ NVar, Lit ]), fail.
expressAnd( Var, Lits) :- findall(NLit, (member(Lit,Lits), negate(Lit,NLit)), NLits), writeOneClause([ Var | NLits]), !.


%%%%%%% main: =================================================================================

main :- current_prolog_flag(os_argv, Argv),
        nth0(1, Argv, InputFile),
        main(InputFile), !.
main :-  write('Usage: $ ./<executable> <example>          or ?- main(<example>).'), nl, halt.

main(InputFile) :-
        symbolicOutput(1), !,
        consult(InputFile),
        writeClauses(infinite), halt.   % print the clauses in symbolic form and halt
main(InputFile):-
        consult(InputFile),
        told, write('Looking for initial solution with arbitrary cost...'), nl,
        initClauseGeneration,
        tell(clauses), writeClauses(infinite), told,
        tell(header),  writeHeader, told,
        numVars(N), numClauses(C),
        write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
        shell('cat header clauses > infile.cnf',_),
        write('Launching kissat...'), nl,
        shell('kissat -v infile.cnf > model', Result),  % if sat: Result=10; if unsat: Result=20.
        treatResult(Result,[]),!.

treatResult(20,[]       ):- write('No solution exists.'), nl, halt.
treatResult(20,BestModel):-
        nl,costOfThisSolution(BestModel,Cost), write('Unsatisfiable. So the optimal solution was this one with cost '),
        write(Cost), write(':'), nl, displaySol(BestModel), nl,nl,halt.
treatResult(10,_):- %   shell('cat model',_),
        nl,write('Solution found '), flush_output,
        see(model), symbolicModel(M), seen,
        costOfThisSolution(M,Cost),
        write('with cost '), write(Cost), nl,nl,
        displaySol(M), 
        Cost1 is Cost-1,   nl,nl,  write('Now looking for solution with cost '), write(Cost1), write('...'), nl,
        initClauseGeneration, tell(clauses), writeClauses(Cost1), told,
        tell(header),  writeHeader,  told,
        numVars(N),numClauses(C),
        write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
        shell('cat header clauses > infile.cnf',_),
        write('Launching kissat...'), nl,
        shell('kissat -v infile.cnf > model', Result),  % if sat: Result=10; if unsat: Result=20.
        treatResult(Result,M),!.
treatResult(_,_):- write('cnf input error. Wrote something strange in your cnf?'), nl,nl, halt.


initClauseGeneration:-  %initialize all info about variables and clauses:
        retractall(numClauses(   _)),
        retractall(numVars(      _)),
        retractall(varNumber(_,_,_)),
        assert(numClauses( 0 )),
        assert(numVars(    0 )),     !.

writeOneClause([]) :- symbolicOutput(1),!, nl.
writeOneClause([]) :- countClause, write(0), nl.
writeOneClause([Lit|C]) :- w(Lit), writeOneClause(C),!.
w(-Var) :- symbolicOutput(1), satVariable(Var), write(-Var), write(' '),!.
w( Var) :- symbolicOutput(1), satVariable(Var), write( Var), write(' '),!.
w(-Var) :- satVariable(Var),  var2num(Var,N),   write(-), write(N), write(' '),!.
w( Var) :- satVariable(Var),  var2num(Var,N),             write(N), write(' '),!.
w( Lit) :- told, write('ERROR: generating clause with undeclared variable in literal '), write(Lit), nl,nl, halt.


% given the symbolic variable V, find its variable number N in the SAT solver:
:- dynamic(varNumber / 3).
var2num(V,N) :- hash_term(V,Key), existsOrCreate(V,Key,N),!.
existsOrCreate(V,Key,N) :- varNumber(Key,V,N),!.                            % V already existed with num N
existsOrCreate(V,Key,N) :- newVarNumber(N), assert(varNumber(Key,V,N)), !.  % otherwise, introduce new N for V

writeHeader :- numVars(N),numClauses(C), write('p cnf '),write(N), write(' '),write(C),nl.

countClause :-     retract( numClauses(N0) ), N is N0+1, assert( numClauses(N) ),!.
newVarNumber(N) :- retract( numVars(   N0) ), N is N0+1, assert(    numVars(N) ),!.

% Getting the symbolic model M from the output file:
symbolicModel(M) :- get_code(Char), readWord(Char,W), symbolicModel(M1), addIfPositiveInt(W,M1,M),!.
symbolicModel([]).
addIfPositiveInt(W,L,[Var|L]) :- W = [C|_], between(48,57,C), number_codes(N,W), N>0, varNumber(_,Var,N),!.
addIfPositiveInt(_,L,L).
readWord( 99,W) :- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ c
readWord(115,W) :- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ s
readWord( -1,_) :-!, fail. %end of file
readWord(C, []) :- member(C,[10,32]), !. % newline or white space marks end of word
readWord(Char,[Char|W]) :- get_code(Char1), readWord(Char1,W), !.

%%%%%%% =======================================================================================
