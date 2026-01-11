%% ----------- [2.5 points] ---------- %%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% A list P of integers is said to be an *arithmetic progression* if the difference between
% consecutive elements is a constant (which is called its *common difference*).
% For instance, [5,11,17] is an arithmetic progression (and its common difference is 6).
%
% The predicate longestAP(+L,-P) below should instantiate P with a longest arithmetic progression 
% appearing as a subsequence of L, where L is an ordered list of distinct integers. A subsequence
% of a list L is a list that can be obtained from L by deleting some or no elements without
% changing the order of the remaining elements. For example, the query
% longestAP([2,5,7,11,17,18],P) instantiates P with [5,11,17]. 
%
% Predicate longestAP(L,P) uses lengthAP(L,N,P) to find arithmetic progressions of length N.
% Define the predicate lengthDiffAP/4 that is used in lengthAP/3. Namely, predicate 
% lengthDiffAP(L,N,D,P) should be true if P is an arithmetic progression of length N and 
% common difference D appearing as a subsequence in the (nonempty) sorted list of distinct 
% integers L.
%
% The aimed solution to longestAP/2 works in polynomial time.
% An alternative non-polynomial time solution will be *penalized*.
%
% For example,
%
%   ?- lengthDiffAP([3,12,17,21,60,66],3,9,P).
%   P = [3, 12, 21].
%
%   ?- lengthDiffAP([30,40,45,70,85,100,130,160,200,220,250,300,320,360],5,30,P).
%   P = [40, 70, 100, 130, 160].
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% longestAP(+L,-P) holds if P is instantiated to a longest arithmetic progression
%     that is a subsequence of a nonempty sorted list of distinct integers L
longestAP(L,P) :-
    length(L,N), !,
    between(1,N,K), I is N - K + 1,
    lengthAP(L,I,P), !.

% lengthAP(+L,+N,-P) holds if P is instantiated to an arithmetic progression
%      of length N that is a subsequence of a nonempty sorted list of distinct integers L
lengthAP([X|_],1,[X]).
lengthAP(L,N,P) :-
    N > 1,
    findall(D, (append(_, [X|R], L), member(Y, R), D is Y - X), LD),
    member(D, LD),
    lengthDiffAP(L,N,D,P), !.

% lengthDiffAP(+L,+N,+D,-P) holds if P is instantiated to an arithmetic progression
%      of length N and common difference D that is a subsequence of a nonempty sorted list
%      of distinct integers L
lengthDiffAP(L,1,_,[A]) :-
    member(A,L),!. % Selecciona todos los elementos de la lista
lengthDiffAP(L,N,D,[A,B|X]) :-
    member(A,L),
    B is A+D,
    append(_,[B|T],L),
    N2 is N - 1,
    lengthDiffAP([B|T], N2, D, [B|X]).

