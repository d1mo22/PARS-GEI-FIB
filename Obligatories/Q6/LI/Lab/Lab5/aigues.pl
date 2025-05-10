main :- EstatInicial = [0,0],    EstatFinal = [0,4],
        between(0, 1000, CostMax),                  % Busquem solució de cost 0; si no, de 1, etc.
        cami(CostMax, EstatInicial, EstatFinal, [EstatInicial], Cami),
        reverse(Cami, Cami1), write(Cami1), write(' amb cost '), write(CostMax), nl, halt.

cami(0, E, E, C, C).                                % Cas base: quan l'estat actual és l'estat final.
cami(CostMax, EstatActual, EstatFinal, CamiFinsAra, CamiTotal) :-
        CostMax > 0, 
        unPas(CostPas, EstatActual, EstatSeguent),  % En B1 i B2, CostPas és 1.
        \+ member(EstatSeguent, CamiFinsAra),
        CostMax1 is CostMax-CostPas,
        cami(CostMax1, EstatSeguent, EstatFinal, [EstatSeguent|CamiFinsAra], CamiTotal).
% Primer 5L Segon 8L
unPas(1,[_,Y],[5,Y]). % Omplenar 5L
unPas(1,[X,_],[X,8]). % Omplenar 8L
unPas(1,[_,Y],[0,Y]). % Buidar 5L
unPas(1,[X,_],[X,0]). % Buidar 8L
unPas(1,[X,Y],[Z,T]) :- T is min(8, X+Y), Z is X+Y-T. % 5L -> 8L
unPas(1,[X,Y],[Z,T]) :- Z is min(5, X+Y), T is X+Y-Z. % 8L -> 5L