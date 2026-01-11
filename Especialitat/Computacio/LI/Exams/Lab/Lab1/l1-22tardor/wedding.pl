% 6 points.

%% A couple to be wed is facing a problem with the arrangement of the
%% guests in the banquet. There are N guests, who are identified with the
%% numbers 1, 2, \ldots, N. The bride and the groom have a list of
%% pairs of guests who MUST sit together in the same table, and a list
%% of pairs of guests who CANNOT sit together in the same table.
%% There are M available tables, each of which can fit between L and U
%% people. ALL TABLES must be used.

% Find an arrangement of guests in tables.

%% Example input
numGuests(10).
numTables(4).
minPeopleAtTable(2).
maxPeopleAtTable(3).

mustSitTogether(1, 2).
mustSitTogether(3, 4).
mustSitTogether(5, 6).

cantSitTogether(1, 3).
cantSitTogether(2, 6).
cantSitTogether(4, 5).
cantSitTogether(8, 9).

%% A possible example of correct output:

%% Table 1: 9 10
%% Table 2: 5 6
%% Table 3: 3 4 8
%% Table 4: 1 2 7

%%==========================================================

symbolicOutput(0).  % set to 1 to see symbolic output only; 0 otherwise.

%%%%%% Some helpful definitions to make the code cleaner:
table(T) :- numTables(M), between(1, M, T).
guest(G) :- numGuests(N), between(1, N, G).


%%%%%%  1. SAT Variables:
satVariable( guestTable(G, T) ):- guest(G), table(T).   % "guest G sits at table T."


%%%%%%  2. Clause generation:
writeClauses:-
      allTablesUsed,
      mustSitTogetherC,
      cantSitTogetherC,
      %minGuestPerTable,
      maxGuestPerTable,
      true.
writeClauses:- told, nl, write('Error: writeClauses failed!'), nl, nl, halt.

allTablesUsed :-
      guest(G),
      findall(guestTable(G,T), table(T), Lits),
      exactly(1,Lits), fail.
allTablesUsed.

maxGuestPerTable :-
      table(T),
      findall(guestTable(G,T), guest(G), L),
      maxPeopleAtTable(Max),
      minPeopleAtTable(Min),
      atMost(Max,L), 
      atLeast(Min, L), fail.
maxGuestPerTable.

mustSitTogetherC :-
      mustSitTogether(G1, G2),
      table(T),
      writeOneClause([ -guestTable(G1,T), guestTable(G2,T) ]), 
      writeOneClause([ -guestTable(G2,T), guestTable(G1,T) ]), 
      fail.
mustSitTogetherC.

cantSitTogetherC :-
      cantSitTogether(G1, G2),
      table(T),
      writeOneClause([ -guestTable(G1,T), -guestTable(G2,T) ]), 
      fail.
cantSitTogetherC.

%%%%%%  3. DisplaySol: show the solution. Here M contains the literals that are true in the model:
% displaySol(M):- write(M), nl, fail.
displaySol(M):- nl,
                table(T),
                nl,
                write('Table '), write(T), write(':'),
                guest(G),
                member(guestTable(G, T), M),
                write(' '), write(G),
                fail.
displaySol(_):- nl.


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
