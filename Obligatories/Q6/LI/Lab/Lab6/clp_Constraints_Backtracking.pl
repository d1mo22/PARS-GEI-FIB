:- use_module(library(clpfd)).

% En swi Prolog la declaració de constraints amb el # es desfà sota backtracking.

% Per exemple, per expressar que la llista d'enters L està ordenada, s'ha de fer
% recursivament, com en sortedOK, i NO amb backtracking, com en sortedERR:

sortedOK([_]).                                          %%%% OK!
sortedOK([X,Y|L]):- X #< Y, sortedOK([Y|L]).

sortedERR(L):- append(_, [X,Y|_], L), X #< Y, fail.     %%%% <------ aixi no
sortedERR(_).                                           %%%% <------ funciona!!!

main:-
    length(L,5),
    L ins 1..6,
    sortedOK(L),
%    sortedERR(L),
    label(L),
    write(L), nl, halt.

