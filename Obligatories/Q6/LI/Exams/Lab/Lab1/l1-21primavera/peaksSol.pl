% Complete the predicate writePeaks(L) to make main write all numbers in L strictly larger than its
% predecessor and its successor. In this example, it should behave exactly like this:
%
% ?- main.
% 18 46 46 47 32 50 
% true.

main:- writePeaks([25,1,18,3,11,11,46,44,46,24,6,20,47,14,32,30,30,18,50,43]), nl.

%% writePeaks(L):- ...
%% writePeaks(_).
writePeaks(L):- append(_,[A,B,C|_],L), A<B, B>C, write(B), write(' '), fail.
writePeaks(_).

