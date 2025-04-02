
% Complete the following two predicates in prolog.

% 1.
% nthRoot( N, K, R ) === "Given positive integers N and K,  the integer part of the Nth root of K is R".
% Example: the integer part of the 2th root (square root) of 16 is 4.
% Example: the integer part of the 3rd root (cubic root)  of  8 is 2.
% Example: the integer part of the 4th root               of 16 is 2.
% Example: the integer part of the 4th root               of 15 is 1.

nthRoot( N, K, R ):-  ...
		      



% 2.     
% allSSSS(L) (allSquareSummingSubSequences) ===
%     "Given a sequence of positive integers L, write all non-empty subsequences of L whose sum is a perfect
%     square, in the following format":
% ?-allSSSS([6,3,4,5,6,9,8,5,2,3,4]).
% 9-[6,3]
% 49-[3,4,5,6,9,8,5,2,3,4]
% 4-[4]
% 9-[4,5]
% 9-[9]
% 9-[2,3,4]
% 4-[4]

allSSSS(L):- ...   write(Sum-SS), ....  .


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% SOLUCIONS:

%% nthRoot( N, K, R ):-  between(0,K,R), K >= R**N, R1 is R+1, K < R1**N.

%% allSSSS(L):- append(_,End,L), append(SS,_,End), sum_list(SS,Sum), Sum>0, isSquare(Sum), write(Sum-SS), nl, fail.
%% allSSSS(_).

%% isSquare(N):- between(0,N,R), N is R*R.


