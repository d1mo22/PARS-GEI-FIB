main :- EstatInicial = [[3,3, esq, 0,0]],    EstatFinal = [[0,0, dre, 3,3]],
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

% [Canibals, Missioners]
unPas(1,[_,CE,esq,_,CD], [MEA, CEA, dre, _, CDA]) :- CEA is CE - 1, CDA is CD + 1, CEA =< MEA.  % 1 canibal 
unPas(1,[_,CE,esq,_,CD], [MEA, CEA, dre, _, CDA]) :- CEA is CE - 2, CDA is CD + 2, CEA =< MEA. % 2 canibals
unPas(1,[ME,_,esq,MD,_], [MEA, CEA, dre, MDA, _]) :- MEA is ME - 1, MDA is MD + 1, CEA =< MEA. % 1 missioner
unPas(1,[ME,_,esq,MD,_], [MEA, CEA, dre, MDA, _]) :- MEA is ME - 2, MDA is MD + 2, CEA =< MEA. % 2 missioners
unPas(1,[ME,CE,esq,MD,CD], [MEA, CEA, dre, MDA, CDA]) :- MEA is ME - 1,CEA is CE - 1, CDA is CD + 1,MDA is MD + 1,CEA =< MEA. % 1 canibal i 1 misioner

unPas(1,[_,CE,dre,_,CD], [MEA,CEA,esq,_,CDA]) :- CEA is CE + 1, CDA is CD - 1, CEA =< MEA. % 1 canibal 
unPas(1,[_,CE,dre,_,CD], [MEA,CEA,esq,_,CDA]) :- CEA is CE + 2, CDA is CD - 2, CEA =< MEA. % 2 canibals
unPas(1,[ME,_,dre,MD,_], [MEA,CEA,esq,MDA,_]) :- MEA is ME + 1, MDA is MD - 1, CEA =< MEA. % 1 missioner
unPas(1,[ME,_,dre,MD,_], [MEA,CEA,esq,MDA,_]) :- MEA is ME + 2, MDA is MD - 2, CEA =< MEA. % 2 missioners
unPas(1,[ME,CE,dre,MD,CD], [MEA,CEA,esq,MDA,CDA]) :- MEA is ME + 1,CEA is CE + 1, CDA is CD - 1,MDA is MD - 1,CEA =< MEA.% 1 canibal i 1 misioner
