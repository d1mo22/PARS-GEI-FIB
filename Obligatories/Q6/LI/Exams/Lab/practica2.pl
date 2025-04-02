% CRIDES UTILS:
% write(X)  (nl -> nl es per canviar de linia)
% permutation(L,L1)
% reverse(L,L1)
% member(X,L)
% append(L1,L2,L) -> L1 ++ L2 = L
% select(X,L,R) -> treu de L una instancia de X ( si n n hi ha cap false, si n hi ha mes d una diferents resultats), la llista resultant en R
% sum_list(L, X)
% subtract(L,S1,S2) -> S2 = L-S1

% 1. Escribe un predicado prod(L,P) que signifique: “P es el producto de los elementos de la lista
% de enteros dada L”. Debe poder generar la P y tambi ́en comprobar una P dada.

prod([],1).
prod([X|L], P):- prod(L, Y), P is X * Y.


% 2. Escribe un predicado pescalar(L1,L2,P) que signifique: “P es el producto escalar de los
% vectores L1 y L2”, donde los vectores se representan como listas de enteros. El predicado debe
% fallar si los dos vectores tienen longitudes distintas.

pescalar([], [], 0).    
pescalar([X|L1],[Y|L2],P):- pescalar(L1, L2, Q), P is X*Y + Q, !.


% 3. Representando conjuntos con listas sin repeticiones, escribe predicados para las operaciones de
% intersecci ́on y uni ́on de conjuntos dados.

% Union:
union(L1, [],L1).
union([], L2, L2).
union([X|L1], L2, U):- member(X, L2), !, union(L1, L2, U).
union([X|L1], L2, [X|U]):- union(L1, L2, U).

% Intersection:
intersection(_, [], []).
intersection([], _, []).
intersection([X|L1], L2, [X|U]):- member(X, L2), !, intersection(L1, L2, U).
intersection([_|L1], L2, U):- intersection(L1, L2, U).


% 4. Usando append, escribe un predicado para calcular el  ́ultimo elemento de una lista dada, y otro
% para calcular la lista inversa de una lista dada.

ultim(Y, Last):- append(_, [Last], Y), !.

invers([], []).
invers([X|L], Inverse) :- invers(L, T), append(T, [X], Inverse). 


% 5. Escribe un predicado fib(N,F) que signifique: “F es el N-´esimo n´umero de Fibonacci para la
% N dada”. Estos n´umeros se definen as´ı: fib(1) = 1, fib(2) = 1, y si N > 2 entonces fib(N) =
% fib(N − 1) + fib(N − 2).

fib(1, 1).
fib(2, 1).
fib(N, F) :-
    N > 2,
    N1 is N - 1,
    N2 is N - 2,
    fib(N1, X),
    fib(N2, Y),
    F is X + Y.


% 6. Escribe un predicado dados(P,N,L) que signifique: “la lista L expresa una manera de sumar
% P puntos lanzando N dados”. Por ejemplo: si P es 5 y N es 2, una soluci´on ser´ıa [1,4] (n´otese
% que la longitud de L es N). Tanto P como N vienen instanciados. El predicado debe ser capaz de
% generar todas las soluciones posibles.

dados(0, 0, []).
dados(P,N,[X|L]) :- 
    N > 0, member(X, [1,2,3,4,5,6]), 
    N1 is N - 1, P1 is P - X, 
    dados(P1, N1, L).

sum([], 0).
sum([H|T], SA) :- sum(T, S), SA is H + S.

% 7. Escribe un predicado suma demas(L) que, dada una lista de enteros L, se satisface si existe alg´un
% elemento en L que es igual a la suma de los dem´as elementos de L, y falla en caso contrario.

suma_demas(L) :-
    select(X, L, R),
    sum_list(R, SUM),
    X == SUM.   


% 8. Escribe un predicado suma_ants(L) que, dada una lista de enteros L, se satisface si existe alg´un
% elemento en L que es igual a la suma de los elementos anteriores a ´el en L, y falla en caso
% contrario

suma_ants(L) :- append(L1, [X|_], L), sum(L1, X), !.


% 9. Escribe un predicado card(L) que, dada una lista de enteros L, escriba la lista que, para cada
% elemento de L, dice cu´antas veces aparece este elemento en L. Por ejemplo, si hacemos la consulta
% card( [1,2,1,5,1,3,3,7] ) el int´erprete escribir´a:
% [[1,3],[2,1],[5,1],[3,2],[7,1]].

countApp(_, [], 1). %siempre aparece 1 vez minimo
countApp(X, [H|T], App) :- X == H, countApp(X, T, NApp), App is NApp + 1, !.
countApp(X, [_|T], App) :- countApp(X, T, App).

removeEquals(_, [], []).
removeEquals(X, [H|T], L) :- X == H, removeEquals(X, T, L), !.
removeEquals(X, [H|T], [H|L]) :- removeEquals(X, T, L).

card([H|T]) :- 
    write('['),
    countApp(H, T, App), removeEquals(H, T, NT),
    write('['), write(H), write(','), write(App), write(']'), 
    cardRec(NT),
    write(']'), !.

cardRec([]).
cardRec([H|T]) :- 
    countApp(H, T, App), removeEquals(H, T, NT), 
    write(','), write('['), write(H), write(','), write(App), write(']'),
    cardRec(NT).

% 10. Escribe un predicado esta ordenada(L) que signifique: “la lista L de n´umeros enteros est´a
% ordenada de menor a mayor”. Por ejemplo, a la consulta:
%   ?-esta ordenada([3,45,67,83]).
%   el int´erprete responde yes, y a la consulta:
%   ?-esta ordenada([3,67,45]).
%   responde no.

esta_ordenada([]).
esta_ordenada([_]).
esta_ordenada([F,S|L]) :-
    F =< S,
    esta_ordenada([S|L]).


% 11. Escribe un predicado ord(L1,L2) que signifique: “L2 es la lista de enteros L1 ordenada de
% menor a mayor”. Por ejemplo: si L1 es [4,5,3,3,2] entonces L2 ser´a [2,3,3,4,5]. Hazlo en
% una l´ınea, usando s´olo los predicados permutacion y esta ordenada.

ord(L1, L2) :- permutation(L1, L2), esta_ordenada(L2), !.


% 12. Escribe un predicado diccionario(A,N) que, dado un alfabeto A de s´ımbolos y un natural N,
% escriba todas las palabras de N s´ımbolos, por orden alfab´etico (el orden alfab´etico es seg´un el
% alfabeto A dado). Por ejemplo, diccionario( [ga,chu,le],2) escribir´a:
% gaga gachu gale chuga chuchu chule lega lechu lele.

diccionario(A, N):- palabras(A, N, Res), printPalabras(Res), write(' '),  fail.

palabras(_, 0, []):- !.
palabras(A, N, [Pal|Res]):- 
    member(Pal, A),
    N1 is N - 1,
    palabras(A, N1, Res).

printPalabras([]).
printPalabras([R|Res]):- write(R), printPalabras(Res).


% 13. Escribe un predicado palindromos(L) que, dada una lista de letras L, escriba todas las permutaciones de sus elementos que sean pal´ındromos (capic´uas). Por ejemplo, con la consulta
% palindromos([a,a,c,c]) se escribe [a,c,c,a] y [c,a,a,c].

isPalindrome(L) :- reverse(L, L).

palindromos(L) :- permutation(L, P), isPalindrome(P), write(P), nl, fail.


findMembers(X, L):- member(X, L), !, X.


% 14. Encuentra mediante un programa Prolog, usando el predicado permutaci´on, qu´e 8 d´ıgitos diferentes tenemos que asignar a las letras S, E, N, D, M, O, R, Y, de manera que se cumpla la suma
% siguiente:
%   S E N D
% + M O R E
% M O N E Y

sendMoreMoney :- 
    Letters = [S, E, N, D, M, O, R, Y, _, _],
    Numbers = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
    permutation(Letters, Numbers),
    X is S * 1000 + E * 100 + N * 10 + D,
    K is M * 1000 + O * 100 + R * 10 + E,
    Z is M * 10000 + O * 1000 + N * 100 + E * 10 + Y,
    AAAA is X + K, 
    AAAA = Z,
    writeLetters(Letters).

writeLetters([S, E, N, D, M, O, R, Y, _, _]):-
    write('S = '), write(S), nl,
    write('E = '), write(E), nl,
    write('N = '), write(N), nl,
    write('D = '), write(D), nl,
    write('M = '), write(M), nl,
    write('O = '), write(O), nl,                                                 
    write('R = '), write(R), nl,
    write('Y = '), write(Y), nl.


% 16. Queremos obtener en Prolog un predicado dom(L) que, dada una lista L de fichas de domin´o (en
%     el formato de abajo), escriba una cadena de domin´o usando todas las fichas de L, o escriba “no
%     hay cadena” si no es posible. Por ejemplo,
%     ?- dom( [ f(3,4), f(2,3), f(1,6), f(2,2), f(4,2), f(2,1) ] ).
%     escribe la cadena correcta:
%     [ f(2,3), f(3,4), f(4,2), f(2,2), f(2,1), f(1,6) ].
%     Tambi´en podemos girar alguna ficha como f(N,M), reemplaz´andola por f(M,N). As´ı, para:
%     ?- dom ([ f(4,3), f(2,3), f(1,6), f(2,2), f(2,4), f(2,1) ]).
%     s´olo hay cadena si se gira alguna ficha (por ejemplo, hay la misma cadena que antes).
%     El siguiente programa Prolog a´un no tiene en cuenta los posibles giros de fichas, ni tiene implementado el predicado ok(P), que significa: “P es una cadena de domin´o correcta (tal cual, sin
%     necesidad ya de girar ninguna ficha)”:
%     p([],[]).
%     p(L,[X|P]) :- select(X,L,R), p(R,P).
%     dom(L) :- p(L,P), ok(P), write(P), nl.
%     dom( ) :- write(’no hay cadena’), nl.
%     (a) ¿Qu´e significa el predicado p(L,P) para una lista L dada?
%     (b) Escribe el predicado ok(P) que falta.
%     (c) Extiende el predicado p para que el programa tambi´en pueda hacer cadenas girando alguna
%     de las fichas de la entrada.

p([],[]).
p(L,[X|P]) :- select(X,L,R), p(R,P).
p(L,[f(D, C)|P]) :- select(f(C, D),L,R), p(R,P).

dom(L) :- p(L,P), ok(P), write(P), nl.
dom( ) :- write('no hay cadena'), nl.

ok([]). % Vacio = okay
ok([_]). % Solo un elemento = okay
ok( [f(_, C), f(C, D) | R]) :- ok([f(C, D) | R]).

% 20. Write in Prolog a predicate flatten(L,F) that “flattens” (cast.: “aplana”) the list F as in the
% example:
% ?-flatten( [a,b,[c,[d],e,[]],f,[g,h]], F ).
% F=[a,b,c,d,e,f,g,h]?

flatten([], []).
flatten([H|T], F) :-
    flatten(H, FH),
    flatten(T, FT),
    append(FH, FT, F), !.
flatten(X, [X]).

% 21. Escribe un predicado Prolog log(B,N,L) que calcula la parte entera L del logaritmo en base B
% de N, donde B y N son naturales positivos dados. Por ejemplo, ?- log(2,1020,L). escribe L=9?
% Pod´eis usar la exponenciaci´on, como en 125 is 5**3. El programa (completo) no debe ocupar
% m´as de 3 lineas.

%log(B,N,L) :- N is X ** B



%% Write a Prolog predicate eqSplit(L,S1,S2) that, given a list of
%% integers L, splits it into two disjoint subsets S1 and S2 such that
%% the sum of the numbers in S1 is equal to the sum of S2. It should
%% behave as follows:
%%
%% ?- eqSplit([1,5,2,3,4,7],S1,S2), write(S1), write('    '), write(S2), nl, fail.
%%
%% [1,5,2,3]    [4,7]
%% [1,3,7]    [5,2,4]
%% [5,2,4]    [1,3,7]
%% [4,7]    [1,5,2,3]


eqSplit(L, S1, S2) :-
    subset(L, S1),
    subtract(L, S1, S2),
    sum_list(S1, Sum),
    sum_list(S2, Sum).

% Generates all subsets of a given list. subset(L, Result).
subset( [], [] ).
subset( [_|L],    S  ):-  subset(L,S).
subset( [X|L], [X|S] ):-  subset(L,S).


% 23. Given a list of integers L, and a maximum sum K, write the subsets Sm of L such that:
%  sum(Sm) =< K, and
%  no element in L \ Sm can be added to Sm without exceeding the sum K.
% For the example below, a correct output would be the following (or in another order):
% [2,5,-2,1]
% [2,-2,2,3,1]
% [2,-2,2,4]
% [2,-2,4,1]
% [5,-2,2,1]
% [5,-2,3]
% [7,-2,1]
% [-2,2,4,1]
% [-2,3,4,1]
% Hint: you can use the predicate sum list(L, X), which is true if X is the sum of the numbers
% in L; e.g., sum list([1,2,3], 6) holds.
% Complete:
%% Example:
numbers([2,5,7,-2,2,9,3,4,1]).
maxSum(6).
%% subsetWithRest(L, Subset, Rest) holds
%% if Subset is a subset of L and Rest is the rest of the elements.
subsetWithRest([],[],[]).
subsetWithRest([X|L], [X|Subs], Rest):- subsetWithRest(L,Subs,Rest).
subsetWithRest([X|L], Subs, [X|Rest]):- subsetWithRest(L,Subs,Rest).

%% maxSubset(K, L, Sm) holds
%% if Sm is a subset of numbers of L such that
%% it sums at most K
%% and if we try to add any other element, the sum exceeds K.
maxSubset(K, L, Sm):-
    subsetWithRest(L, Sm, Rest),
    sum_list(Sm,X), X =< K,
    findall(patataa,(member(Y,Rest), (X + Y) =< K), Lits), length(Lits,Z), Z == 0.

main23 :-
    numbers(L), maxSum(K),
    maxSubset(K, L, Sm),
    write(Sm), nl, fail.
main23:- halt.


% 24. Given a graph declared as in the example below, write all its cliques of size at least minCliqueSize.
% Remember, a clique is a complete subgraph: a subset {textttS of the vertices such that for all
% U,V in S there is an edge U-V.
% For the example below, a correct output would be the following (or in another order):
% [2,4,5,7,9]
% [2,4,5,7]
% [2,4,5,9]
% [2,4,7,9]
% [2,4,8,9]
% [2,5,7,9]
% [4,5,7,9]
% Complete:
%%==== Example: ========================================================
numVertices(10).
minCliqueSize(4).
vertices(Vs):- numVertices(N), findall(I,between(1,N,I),Vs).
vertex(V):- vertices(Vs), member(V,Vs).
edge(U,V):- edge1(U,V).
edge(U,V):- edge1(V,U).
edge1(9,8).
edge1(8,2).
edge1(7,4).
edge1(5,7).
edge1(4,2).
edge1(5,2).
edge1(2,7).
edge1(7,9).
edge1(2,9).
edge1(4,8).
edge1(4,9).
edge1(9,5).
edge1(4,5).
%%==========================================================
main :- 
    vertices(Vs), subset( Vs, S), 
    length(S, LengthS), minCliqueSize(MCS), LengthS >= MCS,
    isClique(S), 
    write(S), nl, fail.
main :- halt.


isClique(S):- 
    findall(U-V, (edge(U,V), member(U, S), member(V, S), U < V), Lits),
    length(S, N),
    ObjCardinality is (N*(N-1))/2,
    length(Lits, ActCardinality),
    ObjCardinality == ActCardinality.

% 1 --- 2
% |  X  |
% 3 --- 4
%(1,2) (1,3)(1,4) (n*n-1)/2
%(2,3) (2,4)
%(3,4)

isClique(S):- 
    findall(edge(U,V), (member(U, S), member(V, S), U \= V), Lits),
    length(S, N),
    ObjCardinality is (N*(N-1))/2,
    length(Lits, ActCardinality),
    ObjCardinality == ActCardinality.




% 25. Complete the following predicate in prolog.
%    nthRoot( N, K, R ) === "Given positive integers N and K, the integer part of the Nth root of K is R".
%    Example: the integer part of the 2th root (square root) of 16 is 4.
%    Example: the integer part of the 3rd root (cubic root) of 8 is 2.
%    Example: the integer part of the 4th root of 16 is 2.
%    Example: the integer part of the 4th root of 15 is 1.

nthRoot( N, K, R ):- Aux is K ^ (1/N), R is floor(Aux). 

% nthRoot(N, K, R) :-
%     between(0, K, R),
%     R_power is integer(RN),
%     R_power =< K,
%     (R + 1)  N > K.




% 26. Complete the following predicate in prolog.
% allSSSS(L) (allSquareSummingSubSequences) ===
% "Given a sequence of positive integers L, write all non-empty subsequences of L
% whose sum is a perfect square, in the following format":
% ?- allSSSS([6,3,4,5,6,9,8,5,2,3,4]).
% 9-[6,3]
% 49-[3,4,5,6,9,8,5,2,3,4]
% 4-[4]
% 9-[4,5]
% 9-[9]
% 9-[2,3,4]
% 4-[4]

subsequence(L, SS) :-
    append(_, S1, L),
    append(SS, _, S1),
    SS \= [].

isPerfectSquare(X) :- 
    Sqrt is round(sqrt(X)),
    Result is Sqrt*Sqrt,
    X == Result.

listIsPerfectSquare([], 0).
listIsPerfectSquare([H|T], Sum) :- listIsPerfectSquare(T, Sum2), Sum is Sum2 + H.

allSSSS(L):- 
    subsequence(L, SS),
    listIsPerfectSquare(SS, Sum),
    isPerfectSquare(Sum),
    write(Sum-SS), nl, 
    fail.
allSSSS(_).