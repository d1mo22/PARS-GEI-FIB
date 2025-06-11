% Complete the predicate teamPoints to make main behave exactly like
% this (note that each won match gives 3 points and each draw gives 1 point):
%
% ?- main.
% [10-barca,7-valencia,7-madrid,5-betis]
% true.



main:- findall(Pts-T,teamPoints(T,Pts),Clas0), sort(Clas0,Clas1), reverse(Clas1,Clas), write(Clas), nl.

results( [ [barca,    3-0, 3-2, 1-0, 2-2],
	   [valencia, 1-1, 4-1, 2-1, 0-3],
           [madrid,   0-2, 1-1, 2-1, 3-2],
	   [betis,    2-2, 2-1, 1-3, 0-0] ] ).

%% teamPoints(...):-
%% ...
teamPoints(Team,Points):- results(R),  member([Team|Matches],R),
     findall( N-M, (member(N-M,Matches),N>M), Wins ),  length(Wins, NumWins ),
     findall( N-N,  member(N-N,Matches),      Draws),  length(Draws,NumDraws),  Points is 3*NumWins+NumDraws.

