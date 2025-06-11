%% ----------- [5 points] ---------- %%


symbolicOutput(0).  % set to 1 for DEBUGGING: to see symbolic output only; 0 otherwise.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% A tatamibari puzzle is a rectangular grid containing three different kinds of symbols: 
%% a vertical line (|), a horizontal line (–), or a cross (+). The grid is composed of cells.
%% A point in the grid that is adjacent to four cells is called a corner. 
%%
%% The grid must be partitioned into rectangular regions according to the following rules:
%% 1. Every region must contain exactly one symbol.
%% 2. The region in which a – symbol is contained must have greater width than height.
%% 3. The region in which a | symbol is contained must have greater height than width.
%% 4. The region in which a + symbol is contained must be a square.
%% 5. Four different regions never meet at the same corner; that is, situations like this
%%         a b b b
%%         c d d d
%%         c d d d
%%    cannot happen (regions are described by cells containing the same letter).
%%
%% As a consequence of the concept of partition, the regions must also satisfy the condition:
%% 6. Every cell belongs to exactly one region.
%%
%% Given a tatamibari puzzle, find a solution according to the above rules.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%% begin example 1: puzzle 6x7 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% % grid(NR,NC): the tatamibari puzzle has NR rows and NC columns
%% grid(6,7).

%% % coordinates [I,J] mean: symbol at row I (1 <= I <= NR), column J (1 <= J <= NC)
%% horizontal([[1,6],[6,2],[6,5]]).    % location of the – symbols
%% vertical([[3,6]]).                  % location of the | symbols
%% cross([[1,5],[3,3]]).               % location of the + symbols

%% %    Input (6 symbols)   Solution for input                   Regions (upper left cell coordinates,
%% %    (dots represent     (regions are described by cells      height, width, and letter)
%% %    empty cells)         containing the same letter)
%% %
%% %      1 2 3 4 5 6 7       1 2 3 4 5 6 7                      1. r(1,1,4,4)  a
%% %    1 · · · · + – ·     1 a a a a b c c                      2. r(1,5,1,1)  b
%% %    2 · · · · · · ·     2 a a a a d d d                      3. r(1,6,1,2)  c
%% %    3 · · + · · | ·     3 a a a a d d d                      4. r(2,5,4,3)  d
%% %    4 · · · · · · ·     4 a a a a d d d                      5. r(5,1,2,4)  e
%% %    5 · · · · · · ·     5 e e e e d d d                      6. r(6,5,1,3)  f
%% %    6 · – · · – · ·     6 e e e e f f f

%%%%%%% end example 1: puzzle 6x7 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% begin example 2: UNSATISFIABLE puzzle 4x5unsat %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% % grid(NR,NC): the tatamibari puzzle has NR rows and NC columns
%% grid(4,5).

%% % coordinates [I,J] mean: symbol at row I (1 <= I <= NR), column J (1 <= J <= NC)
%% horizontal([[1,4]]).        % location of the – symbols
%% vertical([[4,2]]).          % location of the | symbols
%% cross([[2,2],[3,4]]).       % location of the + symbols

%% %    Input (4 symbols)     NO solution exists!
%% %    (dots represent
%% %    empty cells)
%% %
%% %      1 2 3 4 5
%% %    1 · · · – ·
%% %    2 · + · · ·
%% %    3 · · · + ·
%% %    4 · | · · ·

%%%%%%% end example 2: UNSATISFIABLE puzzle 4x5unsat %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%% Some helpful definitions to make the code cleaner: ====================================

cell(I,J) :- height(I), width(J).                     % (I,J) is a valid grid cell
height(I) :- grid(H,_), between(1,H,I).               % I is a valid region height
width(J)  :- grid(_,W), between(1,W,J).               % J is a valid region width

reg(I,J,K,L) :- grid(H,W), cell(I,J),                 % (I,J,K,L) is a valid region description
                height(K), width(L),              
                I + K - 1 =< H, J + L - 1 =< W.  
horReg(I,J,K,L) :- reg(I,J,K,L), K < L.               % (I,J,K,L) is a horizontal region
verReg(I,J,K,L) :- reg(I,J,K,L), K > L.               % (I,J,K,L) is a vertical region
sqReg(I,J,K,L)  :- reg(I,J,K,L), K = L.               % (I,J,K,L) is a square region

horSym(I,J) :- horizontal(L), member([I,J],L).        % cell (I,J) contains a horizontal symbol
verSym(I,J) :- vertical(L), member([I,J],L).          % cell (I,J) contains a vertical symbol
crossSym(I,J) :- cross(L), member([I,J],L).           % cell (I,J) contains a cross symbol 
symbol(I,J) :- horSym(I,J).                           % cell (I,J) contains a – symbol
symbol(I,J) :- verSym(I,J).                           % or a | symbol
symbol(I,J) :- crossSym(I,J).                         % or a + symbol

cellInReg(A,B,I,J,K,L) :-                             % cell (A,B) is inside region (I,J,K,L)
        Ip is I + K - 1, Jp is J + L - 1,             % (assumes region is valid) 
        between(I,Ip,A), between(J,Jp,B).                   

%%%%%%% End helpful definitions ===============================================================


%%%%%%%  1. SAT Variables: ====================================================================

satVariable( r(I,J,K,L) ) :- reg(I,J,K,L).        % "there is a region whose upper left cell is
                                                  %   at (I,J) and has height K and width L"

%%%%%%%  2. Clause generation for the SAT solver: =============================================

writeClauses :-
    everyRegionExactlyOneSymbol,    % every region contains exactly one symbol
    horSymbolInHorRegion,           % every horizontal symbol belongs to a horizontal region 
    verSymbolInVerRegion,           % every vertical symbol belongs to a vertical region
    crossSymbolInSqRegion,          % every cross symbol belongs to a square region 
    fourRegNeverMeet,               % four regions never meet at the same corner
    everyCellExactlyOneRegion,      % every cell belongs to exactly one region
    true,!.
writeClauses :- told, nl, write('writeClauses failed!'), nl,nl, halt.

% regionExactlyOneSymbol(I,J,K,L): given a region whose upper left cell is at (I,J) and
%                                  has height K and width L, the predicate is true if
%                                  that region contains exactly one symbol (–, |, or +)
regionExactlyOneSymbol(I,J,K,L) :-
        findall([A,B],(symbol(A,B),cellInReg(A,B,I,J,K,L)),LSym),
        length(LSym,1).

everyRegionExactlyOneSymbol :-      % every region contains exactly one symbol
        reg(I,J,K,L),
        \+regionExactlyOneSymbol(I,J,K,L),
        % ... %% complete this!
everyRegionExactlyOneSymbol.

horSymbolInHorRegion :-             % every horizontal symbol belongs to a horizontal region
        % ... %% complete this!
horSymbolInHorRegion.

verSymbolInVerRegion :-             % every vertical symbol belongs to a vertical region
        % ... %% complete this!
verSymbolInVerRegion.

crossSymbolInSqRegion :-            % every cross symbol belongs to a square region
        % ... %% complete this!
crossSymbolInSqRegion.

fourRegNeverMeet :-                 % four regions never meet at the same corner
        % ... %% complete this!
fourRegNeverMeet.

everyCellExactlyOneRegion :-        % every cell belongs to exactly one region
        % ... %% complete this!
everyCellExactlyOneRegion.


%%%%%%%  3. DisplaySol: show the solution. Here M contains the literals that are true in the model:

letters([a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z]).
gridLetter(S,I0,J0,C) :-
        nth0(N,S,r(I,J,K,L)), letters(Lt),
        cellInReg(I0,J0,I,J,K,L),
        nth0(N,Lt,C).

%displaySol(M) :- nl, sort(M,M1), write(M1), nl, nl, fail.
displaySol(_) :-
        nl, write("Tatamibari:"), nl, fail.
displaySol(_) :-
        nl, write("  "),
        grid(_,NC),
	between(1,NC,J), writeRowOrColumnNumber(J), fail.
displaySol(_) :-
        grid(NR,NC),
        horizontal(LH), vertical(LV), cross(LC),
        between(1,NR,I), nl, writeRowOrColumnNumber(I), between(1,NC,J),
        writeInitialSymbol(LH,LV,LC,I,J), fail.
displaySol(_) :-
        nl, nl, write("Solution:"), nl, fail.
displaySol(_) :-
        nl, write("  "),
        grid(_,NC),
	between(1,NC,J), writeRowOrColumnNumber(J), fail.
displaySol(M) :-
        grid(NR,NC),
        between(1,NR,I), nl, writeRowOrColumnNumber(I), between(1,NC,J),
        sort(M,S),
        gridLetter(S,I,J,C), write(" "), write(C), fail.
displaySol(M) :- 
        length(M,J), K is J - 1,
        sort(M,S), letters(Lt),
        nl, nl, write("Region: (upper left cell coord.), height, width"), nl, nl,
        between(0,K,I),
        nth0(I,S,R), R = r(X,Y,H,W), nth0(I,Lt,C),
        write(" "), write(C), 
        write(": ("), write(X), write(","), write(Y), write("), "), 
        write(H), write(", "), write(W), nl, fail.
displaySol(_).

writeRowOrColumnNumber(N) :- write(" "), N1 is N mod 10, write(N1), !.

writeInitialSymbol(LH,_,_,I,J) :-
        member([I,J], LH), !, write(" –").
writeInitialSymbol(_,LV,_,I,J) :-
        member([I,J], LV), !, write(" |").
writeInitialSymbol(_,_,LC,I,J) :-
        member([I,J], LC), !, write(" +").
writeInitialSymbol(_,_,_,_,_) :-
        write(" ·").

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

main:-  current_prolog_flag(os_argv, Argv),
        nth0(1, Argv, InputFile),
        main(InputFile), !.
main:-  write('Usage: $ ./<executable> <example>          or ?- main(<example>).'), nl, halt.

main(InputFile):-
        symbolicOutput(1), !,
        consult(InputFile),
        writeClauses, halt.   % print the clauses in symbolic form and halt Prolog
main(InputFile):-
        consult(InputFile),
        initClauseGeneration,
        tell(clauses), writeClauses, told,          % generate the (numeric) SAT clauses and call the solver
        tell(header),  writeHeader,  told,
        numVars(N), numClauses(C),
        write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
        shell('cat header clauses > infile.cnf',_),
        write('Calling solver....'), nl,
        shell('kissat -v infile.cnf > model', Result),  % if sat: Result=10; if unsat: Result=20.
        treatResult(Result),!.

treatResult(20) :- write('Unsatisfiable'), nl, halt.
treatResult(10) :- write('Solution found: '), nl, see(model), symbolicModel(M), seen, displaySol(M), nl,nl,halt.
treatResult( _) :- write('cnf input error. Wrote anything strange in your cnf?'), nl,nl, halt.


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
