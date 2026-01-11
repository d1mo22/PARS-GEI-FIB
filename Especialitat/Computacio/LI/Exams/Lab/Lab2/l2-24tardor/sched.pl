:- use_module(library(clpfd)).

/* Task Scheduling Problem.  
   Given a set of tasks with specific durations, precedence constraints, and a maximum slot limit,
   the objective is to determine the start slots of each task such that:  
   * all precedence constraints X-Y are satisfied (task X must finish before task Y starts).  
   * the number of slots needed (makespan) is minimized while staying within the given slot limit.  

   Description of the input:
   example(Ident, TaskDurations, Precedences, Limit, Optimal)
     Ident: a               - Identifier of the example.
     Tasks: [3,2,4]         - The durations of tasks 1, 2, and 3 are 3, 2, and 4 slots respectively.
     Precedences: [1-2,2-3] - Task 1 must finish before task 2 starts, and task 2 must finish before task 3 starts.
     Limit: 10              - The maximum allowed number of slots is 10.
     Optimal: 9             - Example 'a' has an optimal makespan of 9 slots. This is ONLY used to check the solution.

   For example:
   ?- main(a).
   
   Task durations [3,2,4] with precedences [1-2,2-3] within 10 slots
   
   Slots  : 1234567890
   Task  1: ***       : start(1) duration(3) end(3)
   Task  2:    **     : start(4) duration(2) end(5)
   Task  3:      **** : start(6) duration(4) end(9)
   
   Total number of slots needed: 9
*/

example(e1, [3,2,4], [1-2,2-3], 10, 9).
example(e2, [3,2,4], [], 10, 4).
example(e3, [4,3,7,2,6,5,3], [1-3,1-4,2-5,3-6,4-7], 25, 16).
example(e4, [3,5,2,7,4,6,8,2,5,3,7,6,4,3,5,7,2,8,4,6],
            [1-2,1-3,2-4,3-5,4-6,5-7,6-8,7-9,8-10,2-11,3-12,6-13,8-14,9-15,10-16,11-17,12-18,14-19,15-20], 50, 33).


%% To invoke the program with the example Id, use THIS predicate main/1.
main(Id) :-
    main(Id, _), !, halt.

%% Our external solution checker will use the second argument in main/2 to check your solution.
main(Id, StartSlots) :- 
    example(Id, Durations, Precedences, Limit, _),
    nl, write('Task durations '), write(Durations), write(' with precedences '), write(Precedences),
    write(' within '), write(Limit), write(' slots'), nl, nl,

%1: Variables and domains:
    length(Durations, N),
    length(StartSlots, N),         % Variables for start slots
    StartSlots ins 1..Limit,        % Definir el rang de les variables

%2: Constraints:
    insideMaximumMakespan(StartSlots, Durations, Limit),
    precedenceConstraints(StartSlots, Durations, Precedences),
    
%3: Labeling:
    defineEndSlots(StartSlots, Durations, EndSlots),
    maxExprOfEndSlots(EndSlots, MaxExpr),
    labeling([min(MaxExpr)], StartSlots),

%4: Show the result:
    displaySolution(StartSlots, Durations, Limit),
    write('Total number of slots needed: '),
    makespan(StartSlots, Durations, MaxEnd),    % ALSO:  MaxEnd is MaxExpr,
    write(MaxEnd), nl, nl, !.


% insideMaximumMakespan(StartSlots, Durations, Limit)
insideMaximumMakespan([], [], _).
insideMaximumMakespan([S|LS], [D|LD], N) :- % COMPLETE
     S + D - 1 #=< N,
    insideMaximumMakespan(LS,LD,N).

% precedenceConstraints(StartSlots, Duraitions, Precedences)
precedenceConstraints(_, _, []).
precedenceConstraints(LS, LD, [A-B|LC]) :- % COMPLETE
    nth1(A, LS, SA),
    nth1(A, LD, DA),
    nth1(B, LS, SB),
    SA+DA #=< SB,
    precedenceConstraints(LS, LD, LC).

% defineEndSlots(StartSlots, Durations, EndSlots)
defineEndSlots([], [], []).
defineEndSlots([S|LS], [D|LD], [E|LE]) :-
    S+D-1 #= E,
    defineEndSlots(LS, LD, LE).

% maxExprOfEndSlots([X1,X2,...X_{n-1},X_n], E): holds if E is the expression:
%     max(X1,max(X2,max(...max(X_{n-1},X_n)))).
% For example: maxExprOfEndSlots([X,Y,Z,T], max(X,max(Y,max(Z,T)))).
maxExprOfEndSlots([X], X) :- !.
maxExprOfEndSlots([X|L], max(X,MaxL)) :- % COMPLETE
    maxExprOfEndSlots(L, MaxL).


%% ---------------------------------------------------------------
%% Everything below serves to make a pretty print of the solution.
%% ---------------------------------------------------------------

displaySolution(_, _, Lim) :-
    displayHeadLines(Lim), fail.
displaySolution(LS, LD, Lim) :-
    nl, length(LD, N), between(1,N,I), nth1(I, LS, S), nth1(I, LD, D),
    writef('Task%3r: ', [I]), displayTask(S, D, Lim), nl, fail.
displaySolution(_, _, _) :- nl.

displayHeadLines(Lim) :-
    Lim > 10, writef('%r', [' ',9]), K is Lim div 10, between(1,K,I), writef('%r', [' ',9]), write(I), fail.
displayHeadLines(Lim) :-
    (Lim > 10 -> nl ; true), write('Slots  : '), between(1,Lim,I), D is I mod 10, write(D), fail.
displayHeadLines(_).

displayTask(S, D, Lim) :-
    S >= 1, S+D-1 =< Lim, B1 is S-1, B2 is Lim-(S+D-1), displayBar(B1, D, B2), displaySummary(S,D,Lim), !.
displayTask(S, D, Lim) :-
    S < 1, S+D-1 > Lim, displayBar(0, Lim, 0), displaySummary(S,D,Lim), !.
displayTask(S, D, Lim) :-
    (S > Lim ; S+D-1 < 1), displayBar(Lim, 0, 0), displaySummary(S,D,Lim), !.
displayTask(S, D, Lim) :-
    S >= 1, S+D-1 > Lim, B1 is S-1, A is Lim-S+1, displayBar(B1, A, 0), displaySummary(S,D,Lim), !.
displayTask(S, D, Lim) :-
    S < 1, S+D-1 =< Lim, A is D+S-1, B2 is Lim-(S+D-1), displayBar(0, A, B2), displaySummary(S,D,Lim), !.

displayBar(B1,A,B2) :-
    writef('%r', [' ',B1]), writef('%r', ['*',A]), writef('%r', [' ',B2]).

displaySummary(S,D,Lim) :-
    E is S+D-1,
    write(' : start('), writeSlot(S,Lim), write(') duration('), write(D), write(') end('), writeSlot(E,Lim),  write(')').
    
writeSlot(N, Lim) :-
    write(N), (N < 1 ; N > Lim) -> write('!!') ; true.

makespan(LS, LD, MaxE) :-
    findall(E, (nth1(I, LS, S), nth1(I, LD, D), E is S+D-1), LE),
    max_list(LE, MaxE).
