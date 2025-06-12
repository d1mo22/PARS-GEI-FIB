
%% ----------- [2.5 points] ---------- %%


/*
Given two undirected graphs G and H in normal form with N vertices, determine the 
smallest number of vertex exchanges needed to transform G into H.
Vertices will be represented with integers 1..N, where N is the order of the graph.

We say that G is in normal form (NF) if G is given as its list of edges and:
1. for any edge [i,j], it holds that i < j, and
2. for any two edges [i,j] and [k,l] appearing in this order in the list of edges,
   that is, G = [...,[i,j],...[k,l],...], it holds that i < k, or i = k and j < l.

If U and V are two vertices in G, the graph obtained from G by applying 
exchange [U,V] is the graph where all occurrencies of U are substituted by occurrencies
of V and viceversa. For example, graph G = [[1,2],[2,3]] is transformed into graph 
H = [[2,1],[1,3]] after applying one exchange (that is, exchange [1,2]). 
Expressed in normal form, H = [[1,2],[1,3]].

For example, for the graphs number 1 below, this is a possible sequence of exchanges:
?- main(1).
  From: [[1,2],[1,4],[1,5],[2,3],[2,4],[3,5]]
    to: [[1,2],[1,3],[2,3],[2,4],[3,5],[4,5]]
  Trying cost: 0 1 2
  Solution found at cost 2 with 2 steps
  Sequence of states: 
    [[1,2],[1,4],[1,5],[2,3],[2,4],[3,5]]    %% initial state
    [[1,2],[1,5],[2,3],[2,4],[3,4],[3,5]]    %% step 1: applied exchange [1,3] in vertices [1,2],[1,5],[2,3],[3,4],[3,5]
    [[1,2],[1,3],[2,3],[2,4],[3,5],[4,5]]    %% step 2: applied exchange [1,4] in vertices [1,2],[1,3],[2,4],[4,5] (*)
true.                                        %%   (*) in step 2, the exchange [3,5] will also be successful

Fill the ellipsis and add any additional predicate you may need for your solution.
It is MANDATORY to complete and use the predicates: oneStep/3, order/2, and subs/3.
*/


% graphs(example number, 1st graph in NF, 2nd graph in NF)
% graphs 1: cost 2 (2 steps)
graphs(1,[[1,2],[1,4],[1,5],[2,3],[2,4],[3,5]],     [[1,2],[1,3],[2,3],[2,4],[3,5],[4,5]]).
% graphs 2: cost 1 (1 steps)
graphs(2,[[1,4],[1,5],[1,6],[2,4],[2,5],[2,6],[3,4],[3,5],[3,6]],       [[1,2],[1,4],[1,6],[2,3],[2,5],[3,4],[3,6],[4,5],[5,6]]).
% graphs 3: cost 3 (3 steps)
graphs(3,[[1,2],[1,3],[1,4],[1,5],[2,6],[2,7],[2,8]],       [[1,7],[2,8],[3,8],[4,8],[5,7],[6,7],[7,8]]).
% graphs 4: cost 4 (4 steps)
graphs(4,[[1,2],[1,5],[1,6],[1,7],[2,3],[3,4]],     [[1,4],[2,4],[3,4],[4,5],[5,6],[6,7]]).
% graphs 5: cost 4 (4 steps)
graphs(5,[[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]],     [[1,7],[2,3],[2,5],[3,6],[4,5],[4,7]]).

% main predicate: main(K) checks whether graphs in example K are isomorphic
main(K) :- secondary(K,_,_).

secondary(K,Cost,Path) :-
    graphs(K,G,H), order(G,N),
    write('  From: '), write(G), nl, write('    to: '), write(H), nl,
    write('  Trying cost:'),
    between(0, N, Cost), write(' '), write(Cost),
    InitialState = G, FinalState = H,
    computePath(Cost, InitialState, FinalState, [InitialState], Path),
    writeSolution(Cost, Path),
    !.

computePath(0, S, S, C, C).
computePath(Cost, State, FinalState, PathSoFar, TotalPath) :-
    Cost > 0,
    oneStep(CostStep, State, NextState),
    \+ member(NextState, PathSoFar),
    Cost1 is Cost - CostStep,
    computePath(Cost1, NextState, FinalState, [NextState|PathSoFar], TotalPath).

% oneStep(Cost,G,H): H can be obtained from G with one exchange,
%                    both G and H are graphs in normal form.
%                    The cost of each step is 1.
oneStep(1,G,H) :-
    order(G,N),
    between(1, N, X),
    between(1, N, Y),
    X \= Y,
    subs([X,Y], G, TempH),
    normalForm(TempH,H).

% order(G,N): the number of vertices of G is N 
% DONE
order(G,N) :-
    % Concatenar todas las sublistas
    % sort para eliminar repetidos
    flatten(G, L),
    max_list(L, N).

% subs([X,Y],G,H): H can be obtained from G with the exchange [X,Y]
subs([_,_], [], []).
subs([X,Y], [[X,Y]|T1], [[Y,X]|T2]) :- subs([X,Y], T1, T2), !.
subs([X,Y], [[Y,X]|T1], [[X,Y]|T2]) :- subs([X,Y], T1, T2), !.
subs([X,Y], [[X,Z]|T1], [[Y,Z]|T2]) :- subs([X,Y], T1, T2), !.
subs([X,Y], [[Y,Z]|T1], [[X,Z]|T2]) :- subs([X,Y], T1, T2), !.
subs([X,Y], [[T,X]|T1], [[T,Y]|T2]) :- subs([X,Y], T1, T2), !.
subs([X,Y], [[T,Y]|T1], [[T,X]|T2]) :- subs([X,Y], T1, T2), !.
subs([X,Y], [[T,Z]|T1], [[T,Z]|T2]) :- subs([X,Y], T1, T2), !.  


% the normal form of X is Y
normalForm(X,Y) :-
    edgeSort(X,Z),
    sort(Z,Y).

% edgeSort(G,H): G and H are the same graph but each edge [i,j] in H satisfies i < j
edgeSort([],[]).
edgeSort([X|Y],[XP|YP]) :-
    sort(X,XP),
    edgeSort(Y,YP).

% writes the smallest cost found and a sequence of states with that cost
writeSolution(Cost, Path) :-
    nl, write('  Solution found at cost '), write(Cost),
    write(' with '), length(Path, L), L1 is L - 1, write(L1),
    (L1 =\= 1 -> write(' steps') ; write(' step')),
    nl, write('  Sequence of states: '), nl, writeSteps(Path).
    
writeSteps([]).
writeSteps([S|L]) :- writeSteps(L), write('    '), write(S), nl.
