%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Notació:
%%   * "donat N" significa que l'argument N estarà instanciat inicialmente.
%%   * "ha de ser capaç de generar totes les respostes possibles" significa que
%%     si hi ha backtracking ha de poder generar la següent resposta, com el
%%     member(E,L) que per una llista L "donada" pot generar tots els elements E.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% En LI adapterem la "Notation of Predicate Descriptions" de SWI-Prolog per
%% descriure els predicats, prefixant cada argument amb un d'aquests 3 símbols:
%%   '+' quan l'argument ha d'estar necessàriament instanciat (no pot ser una
%%       variable sense instanciar). Pot ser ground (f(a) o 34)" o no (X+1 o g(a,Y)).
%%       Quan parlem de "donada L", llavors especficarem +L en la *descripció*.
%%       Per exemple, l'argument de +L del predicat esta_ordenada(+L).
%%   '-' quan l'argument ha de ser necessàriament una variable que quedarà
%%       instanciada, al satisfer-se el predicat, amb un cert terme que podem
%%       veure com un "resultat".
%%       Per exemple, l'argument -F en el predicat fact(+N,-F) que per un N donat,
%%       se satisfà fent que F sigui el valor N!.
%%   '?' quan s'accepta que l'argument pugui estar instanciat o no.
%%       Es tracta dels casos en que es diu "ha de poder generar la S i també
%%       comprovar una S donada". Llavors especificarem ?S en la *descripció*.
%%       Per exemple, l'argument ?S de suma(+L,?S).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% En aquests exercicis feu servir els predicats:
%%   * member(E,L)         en lloc de  pert(E,L)
%%   * append(L1,L2,L3)    en lloc de  concat(L1,L2,L3)
%%   * select(E,L,R)       en lloc de  pert_amb_resta(E,L,R)
%%   * permutation(L,P)    en lloc de  permutacio(L,P)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



% PROB. A =========================================================
% Escriu un predicat
% prod(+L,?P)  que signifiqui: P és el producte dels
% elements de la llista de enters donada L. Ha de poder generar la
% P i també comprovar una P donada

prod([], 1).
prod([X|L1], P) :- prod(L1, P1), P is P1 * X.

% PROB. B =========================================================
% Escriu un predicat
% pescalar(+L1,+L2,?P) que signifiqui: P és el producte escalar dels
% vectors L1 i L2, on els vectors es representen com llistes
% d'enters. El predicat ha de fallar si els dos vectors
% tenen longituds diferents.

pescalar([],[],0).
pescalar([X|L1], [Y|L2], P) :- pescalar(L1, L2, P1), P is P1+X*Y.

% PROB. C =========================================================
% Representant conjunts com llistes sense repeticions, escriu
% predicats per les operacions d'intersecció i unió de conjunts donats

% interseccio(+L1,+L2,?L3)
interseccio([],_,[]).
interseccio([X|L1], L2, L3) :- member(X,L2), !, interseccio(L1, L2, L4), L3 = [X|L4].
interseccio([_|L1], L2, L3) :- interseccio(L1,L2,L3).

% unio(+L1,+L2,?L3)

unio([],L2,L2).
unio([X|L1], L2, L3) :- not(member(X,L2)), !, unio(L1,L2,L4), L3 = [X|L4].
unio([_|L1], L2, L3) :- unio(L1,L2,L3).

% PROB. D =========================================================
% Usant append/3, escriu un predicat per calcular l'últim 
% element d'una llista donada, i un altre per calcular la llista
% inversa d'una llista donada.

% ultim(+L,?E)
ultim(L1, E) :- append(_, [E], L1), !.

% inversa(+L1,?L2)
inversa([],[]).
inversa([X|L1],L2) :- inversa(L1,L3), append(L3, [X], L2).

% PROB. E =========================================================
% Escriu un predicat
% fib(+N,?F) que signifiqui: F és l'N-éssim nombre de Fibonacci
% per a la N donada. Aquests nombres es defineixen així:
% fib(1) = 1, fib(2) = 1, i si N > 2 llavors
% fib(N) = fib(N-1) + fib(N-2)

fib(1,1) :- !.
fib(2,1) :- !.
fib(N,F) :- N1 is N-1, N2 is N-2, fib(N2,F2), fib(N1, F1), F is F1 + F2. 

% PROB. F =========================================================
% Escriu un predicat
% dados(+P,+N,-L) que signifiqui: la llista L expressa una forma de
% sumar P punts llançant N daus. Per exemple: si P és 5, i
% N és 2, una solució seria [1,4] (noteu que la longitud de L és N.
% Tant P com N venen instanciats. El predicat deu ser capaç de
% generar totes les solucions possibles,

% valor de 1-6
% N = Vegades que llancem el dau
% P = Resultat de sumar els valors dels daus
dados(0,0,[]) :- !.
dados(P, N, [X|L]) :- N>0, between(1,6,X), P1 is P - X, N1 is N - 1, dados(P1, N1, L).

% PROB. G =========================================================
% Escriu un predicat
% suma_la_resta(+L) que, donada una llista d'enters L, es satisfà si
% existeix algun element en L que és igual a la suma de la resta
% d'elements de L, i que altrament falla.
%
% Escriu abans un predicat
% suma(+L,?S) que, donada una llista d'enters L, se satisfà si S
% és la suma dels elements d'L.

% suma(+L,?S)
suma([],0) :- !.
suma([X|L], S) :- suma(L,S1), S is S1 + X.

% suma_la_resta(+L)
suma_la_resta(L) :- select(X,L,R), suma(R,S), X = S, !.

% PROB. H =========================================================
% Escriu un predicat
% card(+L) que, donada una llista d'enters L, escriba la llista
% que, para cada element d'L, diu quantes vegades surt aquest
% element en L.
% Per exemple, si fem la consulta
% card( [1,2,1,5,1,3,3,7] )  l'intèrpret escriurà:
% [[1,3],[2,1],[5,1],[3,2],[7,1]].

card(L):- cards(L, R), write(R).
 
cards([], []).
cards([X|L], [[X, N]|R]):- 
    cards(L, R1), % Procesem la resta de la llista
    card_in_list([X, N1], R1, R), !, % Mirem si la X esta a R1 y actualitzem el contador
    N is N1+1. % Si trobem X, incrementem el contador
cards([X|L], [[X, 1]|R1]):- 
    cards(L, R1). % En el cas de que X sigui nou creem una nova entrada [X,1]

% FinalL = List - [L]
card_in_list(X, L, R):- 
    append(L1, [X|L2], L),
    append(L1, L2, R).


% PROB. I ========================================================
% Escriu un predicat
% esta_ordenada(+L) que signifiqui: la llista L de nombres enters
% està ordenada de menor a major.
% Per exemple, a la consulta:
% ?- esta_ordenada([3,45,67,83]).
% l'intèrpret respon yes, i a la consulta:
% ?- esta_ordenada([3,67,45]).
% respon no.

esta_ordenada([]).
esta_ordenada([_]).
esta_ordenada([X,Y|L]):- X < Y, esta_ordenada([Y|L]).


% PROB. J ========================================================
% Escriu un predicat
% palíndroms(+L) que, donada una llista de lletres L escrigui
% totes les permutacions dels seus elements que siguin palíndroms
% (capicues). Per exemple, amb la consulta palindrom([a,a,c,c])
% s'escriu [a,c,c,a] i [c,a,a,c]
% (possiblement diverses vegades, no cal que eviteu les repeticions).

isPalindrome(L) :- reverse(L,L).


palindrom(L):- 
    setof(P, (permutation(L,P), isPalindrome(P)), S),
    member(P, S),
    write(P), nl,
    fail. 






% PROB. K ========================================================
% Volem obtenir en Prolog un predicat
% dom(+L) que, donada una llista L de fitxes de dominó (en el format
% indicat abaix), escrigui una cadena de dominófent servir *totes*
% les fitxes de L, o escrigui "no hi ha cadena" si no és possible.
% Per exemple,
% ?- dom( [ f(3,4), f(2,3), f(1,6), f(2,2), f(4,2), f(2,1) ] ).
% escriu la cadena correcta:
% [ f(2,3), f(3,4), f(4,2), f(2,2), f(2,1), f(1,6) ].
%
% També podem "girar" alguna fitxa como f(N,M), reemplaçant-la
% per f(M,N). Així, per:
% ?- dom( [ f(4,3), f(2,3), f(1,6), f(2,2), f(2,4), f(2,1) ] ).
% només hi ha cadena si es gira alguna fitxa (per exemple, hi ha
% mateixa cadena d'abans).
%
% El següent programa Prolog encara no té implementat els possibles
% girs de fitxes, ni té implementat el predicat ok(P), que
% significa: P és una cadena de dominó correcta (tal qual,
% sense necessitat de girar cap fitxa):

p([],[]).
p(L,[X|P]) :- select(X,L,R), p(R,P).
p(L,[f(D, C)|P]) :- select(f(C, D),L,R), p(R,P).

dom(L) :- p(L,P), ok(P), write(P), nl.
dom(_) :- write('no hi ha cadena'), nl.

% a) Escriu el predicat ok(+P) que falta.
ok([]).
ok([_]).
ok([f(_,A),f(A,B)|R]):- ok([f(A,B)|R]).




% b) Estén el predicat p/2 per a que el programa també pugui
%    fer cadenes girant alguna de les fitxes de l'entrada.







% PROB. L ========================================================
% Write in Prolog a predicate aplanada(+L,?F) that ``flattens''
% (cat.: ``aplana'') the list F as in the example:
% ?- aplanada( [a,b,[c,[d],e,[]],f,[g,h]], F ).
% F = [a,b,c,d,e,f,g,h]

aplanada([], []).
aplanada([H|T], F) :-
    aplanada(H, FH),
    aplanada(T, FT),
    append(FH, FT, F), !.
aplanada(X, [X]).





% PROB. M ========================================================
% Consider two groups of 10 people each. In the first group,
% as expected, the percentage of people with lung cancer among smokers
% is higher than among non-smokers.
% In the second group, the same is the case.
% But if we consider the 20 people of the two groups together, then
% the situation is the opposite: the proportion of people with
% lung cancer is higher among non-smokers than among smokers!
% Can this be true? Write a little Prolog program to find it out.

%% Descomenteu i completeu les linies de codi que veieu a continuació:
%SC1: Fumadores con cáncer
%SNC1: Fumadores sin cáncer

%NSC1: No fumadores con cáncer
%NSNC1: No fumadores sin cáncer
 main :-
    between(0,3,SC1), between(0,3,SNC1), between(0,3,NSC1), between(0,3,NSNC1), 
    10 is SC1+SNC1+NSC1+NSNC1,  
    SMOKERS1 is SC1 + SNC1,
    NO_SMOKERS1 is NSC1+NSNC1,
    % Condición para grupo 1: porcentaje fumadores con cáncer > porcentaje no fumadores con cáncer
    SC1/(SMOKERS1) > NSC1/(NO_SMOKERS1),

    between(0,3,SC2), between(0,3,SNC2), between(0,3,NSC2), between(0,3,NSNC2), 
    10 is SC2+SNC2+NSC2+NSNC2, 
    SMOKERS2 is SC2 + SNC2,
    NO_SMOKERS2 is NSC2+NSNC2, 
    % Condición para grupo 2: porcentaje fumadores con cáncer > porcentaje no fumadores con cáncer
    SC2/(SMOKERS2) > NSC2/(NO_SMOKERS2),

    TOTAL_S is SMOKERS1 + SMOKERS2,
    TOTAL_NS is NO_SMOKERS1 + NO_SMOKERS2,
    TOTAL_SC is SC1 + SC2,
    TOTAL_NC is 20-TOTAL_SC,
    TOTAL_S > 0,
    TOTAL_NS > 0,
    TOTAL_SC/TOTAL_S < TOTAL_NC/TOTAL_NS,

    write('Grupo 1: '), write([SC1,SNC1,NSC1,NSNC1]), nl,
    write('Grupo 2: '), write([SC2,SNC2,NSC2,NSNC2]), nl.

