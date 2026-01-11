main :- EstatInicial = [3,3, esq, 0,0],    EstatFinal = [0,0, dre, 3,3],
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


noMengen(0,_).
noMengen(M,C) :- M >= C.

esCorrecte([ME, CE, MD, CD]) :-
        ME >= 0, ME =< 3, CE >= 0, CE =< 3,
        MD >= 0, MD =< 3, CD >= 0, CD =< 3,
        noMengen(ME,CE), noMengen(MD,CD), !.

% [Missioners, Canibals]
unPas(1,[ME,CE,esq,MD,CD], [ME, CEA, dre, MD, CDA]) :- % 1 o 2 canibals L -> R
        member(N, [1,2]),
        CEA is CE - N, 
        CDA is CD + N,        
        esCorrecte([ME, CEA, MD, CDA]).

unPas(1,[ME,CE,esq,MD,CD], [MEA, CE, dre, MDA, CD]) :- % 1 o 2 missioners L -> R
        member(N, [1,2]),
        MEA is ME - N, 
        MDA is MD + N, 
        esCorrecte([MEA, CE, MDA, CD]).

unPas(1,[ME,CE,esq,MD,CD], [MEA, CEA, dre, MDA, CDA]) :- % 1 canibal i 1 misioner L -> R
        CEA is CE - 1, 
        CDA is CD + 1,
        MEA is ME - 1,
        MDA is MD + 1,
        esCorrecte([MEA, CEA, MDA, CDA]).


unPas(1,[ME,CE,dre,MD,CD], [ME,CEA,esq,MD,CDA]) :- % 1 o 2 canibals R -> L
        member(N, [1,2]),
        CEA is CE + N, 
        CDA is CD - N, 
        esCorrecte([ME,CEA,MD,CDA]).

unPas(1,[ME,CE,dre,MD,CD], [MEA,CE,esq,MDA,CD]) :- % 1 o 2 missioners R -> L
        member(N, [1,2]),
        MEA is ME + N, 
        MDA is MD - N, 
        esCorrecte([MEA,CE,MDA,CD]).

unPas(1,[ME,CE,dre,MD,CD], [MEA,CEA,esq,MDA,CDA]) :- % 1 canibal i 1 misioner R -> L
        CEA is CE + 1, 
        CDA is CD - 1,
        MEA is ME + 1,
        MDA is MD - 1,
        esCorrecte([MEA,CEA,MDA,CDA]).
