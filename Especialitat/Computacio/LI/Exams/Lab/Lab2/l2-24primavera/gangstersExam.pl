
%% ----------- [5 points] ---------- %%


symbolicOutput(0).  % set to 1 for DEBUGGING: to see symbolic output only; 0 otherwise.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% To use this prolog template for other optimization problems, replace the code parts 1,2,3,4 below. %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% BELOW IS A SOLUTION FOR THE GANGSTER PROBLEM, WHICH YOU ALREADY KNOW:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% The mafia has a lot of gangsters for doing different tasks.
%% These tasks are planned every 3 days (72h), according to a forecast
%% of the tasks to be done every hour.
%% No gangster can do two different tasks during the same hour or on two consecutive hours.
%% Some gangsters are not available on certain hours.
%% We want to plan all tasks (which gangster does what task when) and
%% we want to find the minimal K such that no gangster works more than
%% K consecutive hours.
%%
%% MODIFY THIS SOLUTION TO FULFILL THE FOLLOWING ADDITIONAL REQUIREMENTS, FOR THIS EXAM:
%% - When a gangster rests between two tasks, the break lasts at least two hours.
%% - There is a list of gangsters that cannot do more than two different tasks
%%   over the course of the 72 hours.
%% - Some gangsters cannot do some tasks.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%% begin input example gangstersExamInput1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% example: 4 gangsters are needed for killing on hour 1, one gangster on hour 2, two gangsters on hour 3, etc.
%% gangstersNeeded( killing,       [4,1,2,4,2,1,1,4,1,1,3,2,4,2,1,2,1,3,2,3,4,1,3,1,2,3,1,3,4,3,2,3,4,2,3,1,4,4,1,4,2,2,1,4,3,3,3,2,2,3,4,4,1,3,3,3,4,4,1,1,2,3,3,3,3,2,1,3,1,1,3,2] ).
%% gangstersNeeded( countingMoney, [1,2,1,3,1,4,3,1,3,1,4,3,2,2,1,2,1,2,1,1,2,1,2,1,1,3,1,2,2,4,3,2,4,4,4,1,2,4,4,2,4,4,4,3,2,2,1,3,2,1,3,3,2,3,3,3,1,4,1,1,3,1,2,3,3,1,4,4,3,3,2,1] ).
%% gangstersNeeded( politics,      [2,4,2,1,1,1,4,1,1,4,1,3,2,4,1,1,4,1,4,3,1,3,2,4,4,2,4,2,1,1,4,3,1,2,2,2,1,1,3,1,1,1,2,2,4,1,1,3,4,4,2,3,2,4,3,1,1,1,3,4,2,2,4,4,3,1,1,2,1,4,3,2] ).

%% gangsters([g01,g02,g03,g04,g05,g06,g07,g08,g09,g10,g11,g12]).

%% notAvailable(g01,[6,13,14,16,21,35,37,41,59]).
%% notAvailable(g02,[14,34,40,45,48,52,58,65,70,72]).
%% notAvailable(g03,[8,11,13,27,30,38,50,51,70]).
%% notAvailable(g04,[4,12,16,17,26,30,42,45,48,55,71]).

%% ADDED FOR THIS EXAM:

%% maxTwoTaskGangsters([g01,g02,g04,g06,g07]).

%% notAllowedTask(g09, politics).
%% notAllowedTask(g10, politics).
%% notAllowedTask(g11, politics).
%% notAllowedTask(g12, politics).

%% initialMaxConsecutive(24).

%
%%%%%%% end input example gangstersExamInput1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% EXAMPLE OUTPUT: (cost 15, but the optimal cost is 8).
%%
%%                       10        20        30        40        50        60        70  
%%               123456789012345678901234567890123456789012345678901234567890123456789012
%%
%% gangster g01: -p----p---cc----ppp--pppppp--ccccc---cc--cccc--p--cccccccc--c-----cccc--
%% gangster g02: ---ccc--ccccc---ppppppppppppppp---ppppp---cc----pp---pp---pp--pp--cc--p-
%% gangster g03: -p----p--p---ppppppp--cccc----pp--c---ppppppp--cc--ppppppppppppp--cc--cc
%% gangster g04: -pp--kkkk---k------ppppp--pp--pppppp--p---kk----pppppp--kk--ppppp----p--
%% gangster g05: -ccccccccccccc----cccc--ppp--cccccccccccc--pp--ppp--cccccc--c--cc--cccc-
%% gangster g06: pppppppppppppp--kkkkkk--kkkk--pppp--kkkk--ppppppppppppp--k---k--p--ppppp
%% gangster g07: p---ccc--ppppp---c--ccc----cccccccc--ccccc--p--ccccccccc--pp--ccccc--p--
%% gangster g08: k--k--p--ppppp--ppp----pp--kkkkkkkkkkkkk--kkkkkkkkkk---kk--p--pppppppppp
%% gangster g09: kkkk---k--kkk--c---k--k--kkkk--kkkkk--ccccc--c--kkkkkkk--c--ccccc--k--k-
%% gangster g10: kkkkk--k--kkkkkkkkkkk--kkk--kkkkk---kkkkkkkkkkkk--cc-----ccc--kkkk--cc--
%% gangster g11: k--kkkkkkkkkkkkkkk--kkk--ccccc--kkkkkkkkkkkkkkk--kkkkkkkkk--kkkkkkkk--kk
%% gangster g12: ccccccccccc--ccccc--kkk--c--kk--cccccc--cccccccc--kkkkkkkkkkkkkkk--kkkkk


%%%%%%% Some helpful definitions to make the code cleaner: ====================================

task(T):-          gangstersNeeded(T,_).
needed(T,H,N):-    gangstersNeeded(T,L), nth1(H,L,N).
gangster(G):-      gangsters(L), member(G,L).
hour(H):-          between(1,72,H).
blocked(G,H):-     notAvailable(G,L), member(H,L).
available(G,H):-   hour(H), gangster(G), \+blocked(G,H).

%% ADDED FOR THIS EXAM:
threeConsecutiveHours(H1,H2,H3) :-     %% COMPLETE 1/5
    hour(H1), 
    H2 is H1 + 1,
    hour(H2),
    H3 is H2 + 1,
    hour(H3).

%%%%%%% End helpful definitions ===============================================================


%%%%%%%  1. Declare SAT variables to be used: =================================================

satVariable( does(G,T,H) ):- gangster(G), task(T), hour(H).  % means:  "gangster G does task T at hour H"     (MANDATORY)
satVariable( busyAtHour(G,H) ):- gangster(G), hour(H).       % means:  "gangster G is busy at hour H"

%% ADDED FOR THIS EXAM:
satVariable( doesTask(G,T) ) :- gangster(G), task(T).        % means:  "gangster G does task T"


%%%%%%%  2. Clause generation for the SAT solver: =============================================

% This predicate writeClauses(MaxCost) generates the clauses that guarantee that
% a solution with cost at most MaxCost is found

writeClauses(infinite) :- !, initialMaxConsecutive(InitialMaxCost), writeClauses(InitialMaxCost), !.
writeClauses(MaxConsecutiveHours) :-
    enoughGangstersAtEachHour,
    eachHourEachGangsterAtMostOneTask,
    noGangsterDoesTwoDifferentTasksConsecutively,  
    relateDoesVarsWithBusyAtHourVars,                    %% express busy SAT vars wrt. does SAT vars
    unAvailableGangsters,
    noMoreConsecutiveHoursThan(MaxConsecutiveHours),
    %% NEW FOR THIS EXAM:
    twoRestHoursBetweenTasks,
    relateDoesVarsWithDoesTask,                          %% express doesTask SAT vars wrt. does SAT vars
    someGangstersAtMostTwoDifferentTasks,
    someGangstersHaveProhibitedTasks,
    true,!.
writeClauses(_) :- told, nl, write('writeClauses failed!'), nl,nl, halt.

enoughGangstersAtEachHour :-  needed(T,H,N), findall( does(G,T,H), available(G,H), Lits ), atLeast(N,Lits), fail.
enoughGangstersAtEachHour.

eachHourEachGangsterAtMostOneTask :- available(G,H), findall( does(G,T,H), task(T), Lits ), atMost(1, Lits ), fail.
eachHourEachGangsterAtMostOneTask.

noGangsterDoesTwoDifferentTasksConsecutively :-
    gangster(G), task(T1), task(T2), T1\=T2, hour(H1), H2 is H1+1, hour(H2), available(G,H1), available(G,H2),
    writeOneClause([ -does(G,T1,H1), -does(G,T2,H2) ]), fail. 
noGangsterDoesTwoDifferentTasksConsecutively.

relateDoesVarsWithBusyAtHourVars :- available(G,H), findall( does(G,T,H), task(T), Lits ), expressOr( busyAtHour(G,H), Lits ), fail.
relateDoesVarsWithBusyAtHourVars.

unAvailableGangsters :- gangster(G), hour(H), \+available(G,H), writeOneClause([ -busyAtHour(G,H) ]), fail. 
unAvailableGangsters.

noMoreConsecutiveHoursThan(K) :- gangster(G), hour(HIni), HFin is HIni+K, hour(HFin),
    findall( -busyAtHour(G,H), between(HIni,HFin,H), Clause ), writeOneClause(Clause), fail.
noMoreConsecutiveHoursThan(_).

%%  NEW FOR THIS EXAM:
twoRestHoursBetweenTasks :-
    %% COMPLETE 2/5
    gangster(G), threeConsecutiveHours(H1,H2,H3), available(G,H1), available(G,H3),
    writeOneClause([ -busyAtHour(G,H1), busyAtHour(G, H2), -busyAtHour(G,H3)]), 
    fail.
twoRestHoursBetweenTasks.

relateDoesVarsWithDoesTask :-
    %% COMPLETE 3/5
    gangster(G), task(T),
    findall(does(G,T,H), available(G,H), Lits),
    expressOr(doesTask(G,T), Lits ),
    fail.
relateDoesVarsWithDoesTask.

someGangstersAtMostTwoDifferentTasks :-
    maxTwoTaskGangsters(L),
    member(G,L),
    findall(doesTask(G,T), task(T), Lits),
    atMost(2,Lits),
    fail.
someGangstersAtMostTwoDifferentTasks.

someGangstersHaveProhibitedTasks :-
    %% COMPLETE 5/5
    notAllowedTask(G, T),
    writeOneClause([ -doesTask(G,T) ]), 
    fail.
someGangstersHaveProhibitedTasks.


%%%%%%%  3. DisplaySol: this predicate displays a given solution M: ===========================

% displaySol(M) :- write(M), nl, fail.
displaySol(M) :- nl,nl,
    write('                      10        20        30        40        50        60        70  '), nl,
    write('              123456789012345678901234567890123456789012345678901234567890123456789012'), nl,
    gangster(G), nl, write('gangster '), write(G), write(': '), hour(H), writeIfBusy(G,H,M), fail.
displaySol(_) :- nl,nl,!.

writeIfBusy(G,H,M) :- member( does(G, killing,       H), M),  write('k'),!.
writeIfBusy(G,H,M) :- member( does(G, countingMoney, H), M),  write('c'),!.
writeIfBusy(G,H,M) :- member( does(G, politics,      H), M),  write('p'),!.
writeIfBusy(_,_,_) :- write('-'),!.


%%%%%%%  4. This predicate computes the cost of a given solution M: ===========================

%% Here the sort predicate is used to remove repeated elements of the list:
costOfThisSolution(M,Cost) :-
    between(0,71,N), Cost is 72-N,
    gangster(G),
    findall(H, member(busyAtHour(G,H),M), L0), sort(L0,L),
    append(_,L1,L), append(LK,_,L1),
    length(LK,Cost), LK=[K1|_], last(LK,KK), KK is K1+Cost-1,!.

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
