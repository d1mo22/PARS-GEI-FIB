% Given a family F of subsets of a base set S, find a frequent element in F, that is,
% an element E of S that appears in at least half of the subsets in F. 
% Represent F as a list of lists. The base set S is given implicitly as the union of
% the sets represented by F.
% As an example, the frequent elements in the family 
%   F = [[2,4],[1,3],[3,4,5],[1,2,3],[4,6,7]] are 3 and 4.
% Its base set can be represented by the list [1,2,3,4,5,6,7].

% Define a predicate frequent(F,E) that is true when E is a frequent element in F.
% It should be defined in such a way that all frequent elements can be found
% in a call to the predicate main defined below. Some auxiliary predicates, as base(F,S), 
% will be needed. Predefined predicates such as union or length can be used.


example(1, [[2,4],[1,3],[3,4,5],[1,2,3],[4,6,7]]).  % frequent elements: 3 4
example(2, [[1], [1,2]]).                           % frequent elements: 1 2
example(3, [[1,2], [2,3], [3,4]]).                  % frequent elements: 2 3
example(4, [[1,2,3,4,5],[2,4,6],[1,3,5,7],[2,3],[6,9],[2,5,7],[4,8,9],[1]]).          % frequent elements: 2
example(5, [[1,2,3],[2,6],[1,3,7],[1,5,3],[6,7,8,9],[3,4,5,7],[2,5,8,9],[1,3,5,9]]).  % frequent elements: 1 3 5


%% base(F,S) holds
%%   if family F has S as base set
base([],[]).
base([F],F).
base([A,B|F],S) :-
        union(A,B,S1),
        base([S1|F],R),
        sort(R,S), !.


%% frequent(F,E) holds
%%   if E is a frequent element of the family F
frequent(F,E) :-
        length(F, LF),
        % ONLY as a HINT (other solutions may be valid):
        findall(_, (member(T,F), member(E,T)), G),
        length(G, LG),
        LG >= (LF+1)//2.

main(N) :- 
        example(N,F), 
        base(F,S),      % family F has S as base set
        member(E,S),
        frequent(F,E),  % E is a frequent element of family F
        write(E), nl,
        fail.
main(_).

