% 4 points.

%% Given a list of integers L, and a maximum sum K, 
%% write the subsets Sm of L such that:
%%  * sum(Sm) =< K, and
%%  * no element in L \ Sm can be added to Sm without exceeding the sum K.

% For the example below, a correct output would be the following
% (or in another order):
%% [2,5,-2,1]
%% [2,-2,2,3,1]
%% [2,-2,2,4]
%% [2,-2,4,1]
%% [5,-2,2,1]
%% [5,-2,3]
%% [7,-2,1]
%% [-2,2,4,1]
%% [-2,3,4,1]

%% Hint: you can use the predicate sum_list(L, X),
%% which is true if X is the sum of the numbers in L;
%% e.g., sum_list([1,2,3], 6) holds.

%% ===============================
%% Example
%% ===============================

numbers([2,5,7,-2,2,9,3,4,1]).
maxSum(6).

%% subsetWithRest(L, Subset, Rest) holds
%% if Subset is a subset of L and Rest is the rest of the elements.
subsetWithRest([], [], []).
subsetWithRest([X|S1], [X|S2], SR) :- subsetWithRest(S1,S2,SR).
subsetWithRest([X|S1], S2, [X|SR]) :- subsetWithRest(S1,S2,SR).

%% maxSubset(K, L, Sm) holds
%% if Sm is a subset of numbers of L such that
%% it sums at most K
%% and if we try to add any other element, the sum exceeds K.
maxSubset(K, L, Sm):-
    subsetWithRest(L, Sm, Rest),
    sum_list(Sm, S), S =< K,
    KmS is K-S,
    checkMax(KmS,Rest).

checkMax(LIM, LR) :-
    member(X, LR), X =< LIM, !, fail.
checkMax(_,_).

main :-
    numbers(L),  maxSum(K),
    maxSubset(K, L, Sm),
    write(Sm), nl, fail.
main:- halt.
