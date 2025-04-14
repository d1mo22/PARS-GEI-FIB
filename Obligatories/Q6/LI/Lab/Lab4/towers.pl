
symbolicOutput(0).  % set to 1 for DEBUGGING: to see symbolic output only; 0 otherwise.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% To use this prolog template for other optimization problems, replace the code parts 1,2,3,4 below. %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% We are given a map with NxM positions. On the map are a number of square villages.
%% On each position inside a village we are allowed to place a tower, at most one tower per
%% village.  These towers can be used to watch horizontally and vertically (like the towers
%% or castles in the game of chess).
%% The aim is to determine where to position the towers such that each village (has at least
%% one position that) is watched by at least one tower (for example, if the village has a
%% tower itself), and MINIMIZE the total number of towers.
%% There is a list of "significant" villages that MUST have a tower.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% begin input example towersInput1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%% upperLimitTowers(10).         % maxim number of towers allowed
%% significantVillages([e,q,r]). % list of villages where a tower is mandatory
%% map_size(34,40).              % numrows, numcols; the left upper corner of the map has coordinates (1,1)
%%
%% village(a, 2,20,2).           % village(ident,row,col,size):  row,col of left upper corner, and size of the square
%% village(b, 3,13,2).
%% village(c, 7,21,2).
%% village(d, 8,13,2).
%% village(e,10,30,4).
%% village(f,11, 7,3).
%% village(g,12, 3,2).
%% village(h,12,13,2).
%% village(i,12,20,2).
%% village(j,12,25,2).
%% village(k,12,37,3).
%% village(l,16, 2,2).
%% village(m,16, 6,3).
%% village(n,16,12,3).
%% village(o,16,20,3).
%% village(p,16,26,2).
%% village(q,16,32,3).
%% village(r,17,38,2).
%% village(s,22,21,2).
%% village(t,23,13,2).
%% village(u,27,20,3).
%% village(v,28,12,2).
%% village(w,31,12,3).
%% village(x,33,21,2).
%%
%%%%%%% end input example towersInput1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% The output could look similar to this  (each "T" indicates a tower):
%%
%% Solution found with cost 7
%%
%%     1.......10........20........30........40
%%
%%  1  ........................................
%%  2  ...................aa...................
%%  3  ............bb.....aa...................
%%  4  ............bb..........................
%%  5  ........................................
%%  6  ........................................
%%  7  ....................cc..................
%%  8  ............dd......cc..................
%%  9  ............dd..........................
%% 10  .............................eeee.......
%% 11  ......fff....................eeee.......
%% 12  ..gg..fff...hh.....ii...jj...eeee...kkk.
%% 13  ..gg..fff...hh.....ii...jj...eeeT...kkk.
%% 14  ....................................kkk.
%% 15  ........................................
%% 16  .ll..mmm...nnn.....ooo...pp....Tqq......
%% 17  .ll..mmm...nnn.....ooo...pp....qqq...rr.
%% 18  .....mmm...nnn.....ooo.........qqq...rT.
%% 19  ........................................
%% 20  ........................................
%% 21  ........................................
%% 22  ....................ss..................
%% 23  ............tt......ss..................
%% 24  ............tt..........................
%% 25  ........................................
%% 26  ........................................
%% 27  ...................Tuu..................
%% 28  ...........vv......uuu..................
%% 29  ...........vT......uuu..................
%% 30  ........................................
%% 31  ...........www..........................
%% 32  ...........www..........................
%% 33  ...........wwT......xx..................
%% 34  ....................xT..................


%%%%%%% Some helpful definitions to make the code cleaner: ====================================

row(I):- map_size(N,_), between(1,N,I).                               % I is a row in the map
col(J):- map_size(_,M), between(1,M,J).                               % J is a col in the map
position(I,J):- row(I), col(J).                                       % I-J is a position in the map
village(V):- village(V,_,_,_).                                        % V is a village identifier
rowVillage(V,I):- village(V,I1,_,S), I2 is I1+S-1, between(I1,I2,I).  % I is a row of the village V
colVillage(V,J):- village(V,_,J1,S), J2 is J1+S-1, between(J1,J2,J).  % J is a col of the village V
posVillage(V,I,J):- rowVillage(V,I), colVillage(V,J).                 % I-J is one position in village V
significantVillage(V):- significantVillages(L), member(V,L).          % V is a significant village
posWatchesVillage(V,I,J):- position(I,J), rowVillage(V,I).            % position (I,J) watches village V
posWatchesVillage(V,I,J):- position(I,J), colVillage(V,J).            %               "

%%%%%%% End helpful definitions ===============================================================


%%%%%%%  1. Declare SAT variables to be used: =================================================

satVariable( towerPos(I,J) ):- row(I), col(J).  % means "there is a tower at position I-J"
% YOU MAY WANT TO INTRODUCE SOME OTHER VARIABLE FOR MAKING THE CARDINALITY CONSTRAINTS SMALLER


%%%%%%%  2. Clause generation for the SAT solver: =============================================

% This predicate writeClauses(MaxCost) generates the clauses that guarantee that
% a solution with cost at most MaxCost is found

writeClauses(infinite):- !, upperLimitTowers(N), writeClauses(N),!.
writeClauses(MaxNumTowers):-
    ...
    true,!.                    % this way you can comment out ANY previous line of writeClauses
writeClauses(_):- told, nl, write('writeClauses failed!'), nl,nl, halt.


%%%%%%%  3. DisplaySol: this predicate displays a given solution M: ===========================

% displaySol(M) :- write(M), nl, nl, fail.
displaySol(M):- write('    1.......10........20........30........40'), nl,
		row(I), nl, write2(I), write('  '),  col(J), writePos(M,I,J), fail.
displaySol(_):- nl,nl.

writePos(M,I,J):- member(towerPos(I,J),M), write('T'), !.
writePos(_,I,J):- posVillage(V,I,J), write(V), !.
writePos(_,_,_):- write('.'), !.
write2(N):- N < 10, !, write(' '), write(N),!.
write2(N):- write(N),!.


%%%%%%%  4. This predicate computes the cost of a given solution M: ===========================

costOfThisSolution(M,Cost):- ...


%%%%%% ========================================================================================



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
        Cost1 is Cost-1,   nl,nl,nl,nl,nl,  write('Now looking for solution with cost '), write(Cost1), write('...'), nl,
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
