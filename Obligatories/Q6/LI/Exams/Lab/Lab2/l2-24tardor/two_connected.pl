/*

Given an (undirected) graph G with vertices V and edges E,
a **simple path** from vertex X to vertex Y
is a sequence of vertices P such that:

   (1) the first element of P is X,
   (2) the  last element of P is Y,
   (3) two consecutive vertices in P form an edge in E, and
   (4) all vertices in P are different.

For example, for the graph with vertices [1,2,3,4,5] and edges
[[1,2], [1,3], [1,4], [1,5], [2,3], [3,4], [3,5]],
the sequence [4,3,1,5] is a simple path from 4 to 5.

A graph G is **2-connected** if, for every pair of vertices X and Y,
there are at least two simple paths from X to Y whose only common vertices are precisely X and Y.

For instance, the example of graph given above is 2-connected, since
for every pair of vertices, there are at least two disjoint simple paths that connect them:

 X   Y    PATH1         PATH2
=================================
 1   2    [1,2]         [1,3,2]
 1   3    [1,2,3]       [1,3]
 1   4    [1,2,3,4]     [1,4]
 1   5    [1,2,3,5]     [1,5]
 2   3    [2,3]         [2,1,3]
 2   4    [2,3,4]       [2,1,4]
 2   5    [2,3,5]       [2,1,5]
 3   4    [3,4]         [3,5,1,4]
 3   5    [3,4,1,5]     [3,5]
 4   5    [4,1,5]       [4,3,5]

Define a predicate

  two_connected(V, E)

that is true if the graph with vertices V and edges E is 2-connected.
Complete the given Prolog code.

*/

graph([1,2,3,4,5], [[1,2], [1,3], [1,4], [1,5], [2,3], [3,4], [3,5]]).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% edge([X, Y], E) is true
% if there is an edge connecting X and Y in the set of edges E.
edge([X, Y], E) :- member([X,Y], E).
edge([X, Y], E):- member([Y,X], E).
    
% simple_path(X, Y, E, Vis, P) is true 
% if P is a simple path from X to Y using edges in E without visiting vertices in Vis
simple_path(X, X, _, Vis, [X]) :-
    not(member(X, Vis)).
    
simple_path(X, Y, E, Vis, [X|L]) :-
    not(member(X,Vis)),
    edge([X,Z], E),
    simple_path(Z,Y, E, [X|Vis], L).



% two_disjoint_simple_paths(X, Y, E) is true 
% if there are at least two disjoint simple paths from X to Y using edges E.
two_disjoint_simple_paths(X, Y, E) :-
    findall(P, simple_path(X, Y, E, [], P), S),
    select(P1, S, R),
    member(P2, R),
    append([X|L1], [Y], P1),
    append([X|L2], [Y], P2),
    not((member(Z, L1), member(Z,L2))).

% two_connected(V, E) is true
% if the graph with vertices V and edges E is 2-connected.
two_connected(V, E) :-
    select(X,V,R),
    member(Y, R),
    not(two_disjoint_simple_paths(X, Y, E)), !,
    fail.
two_connected(_, _).

main :- graph(V, E), two_connected(V, E).
