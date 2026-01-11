main :- EstatInicial = [[1, 2, 5, 8], esq, []],    EstatFinal = [[], dre, [1, 2, 5, 8]],
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

unPas(Cost, [X, esq, Y], [X1, dre, Y1]) :- % Movem 1 persona L -> R
        member(N, X),
        Cost is N,

        append(Y,[N],T),
        sort(T,Y1),

        select(N, X, Z),
        sort(Z, X1).

unPas(Cost, [X, esq, Y], [X1, dre, Y1]) :- % Movem 2 persones L -> R
        member(N, X),
        member(M, X), 
        not(M == N),
        Cost is max(N,M),

        append(Y,[N,M],T),
        sort(T,Y1),

        select(N, X, Z),
        select(M, Z, Z1),
        sort(Z1, X1).

unPas(Cost, [X, dre, Y], [X1, esq, Y1]) :- % Movem 1 persona L -> R
        member(N, Y),
        Cost is N,

        append(X,[N],Z),
        sort(Z,X1),

        select(N, Y, T),
        sort(T,Y1).

unPas(Cost, [X, dre, Y], [X1, esq, Y1]) :- % Movem 2 persones L -> R
        member(N, Y),
        member(M, Y), 
        not(M == N),
        Cost is max(N,M),

        append(X,[N,M],T),
        sort(T,X1),

        select(N, Y, Z),
        select(M, Z, Z1),
        sort(Z1, Y1).


% Per el problema B

% [[1, 2, 5, 8], esq, []] -> [[5, 8], dre, [1,2]] -> [[1, 5, 8], esq, [2]] ->
% [[1], dre, [2, 5, 8]] -> [[1, 2], esq, [5, 8]] -> [[], dre, [1, 2, 5, 8]] 