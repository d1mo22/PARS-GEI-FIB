:- use_module(library(clpfd)).

%% A (6-sided) "letter dice" has on each side a different letter.
%% Find four of them, with the 24 letters abcdefghijklmnoprstuvwxy such
%% that you can make all the following words: bake, onyx, echo, oval,
%% gird, smug, jump, torn, luck, viny, lush, wrap, fame.

% Some helpful predicates:

word( [b,a,k,e] ).
word( [o,n,y,x] ).
word( [e,c,h,o] ).
word( [o,v,a,l] ).
word( [g,i,r,d] ).
word( [s,m,u,g] ).
word( [j,u,m,p] ).
word( [t,o,r,n] ).
word( [l,u,c,k] ).
word( [v,i,n,y] ).
word( [l,u,s,h] ).
word( [w,r,a,p] ).
word( [f,a,m,e] ).

% num(?X, ?N)   "La lletra X és a la posició N de la llista"
num(X,N):- nth1( N, [a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,r,s,t,u,v,w,x,y], X ).

main:-
    length(D1,6),
    length(D2,6),
    length(D3,6),
    length(D4,6),
    %instanciar
    D1 ins 1..24,
    D2 ins 1..24,
    D3 ins 1..24,
    D4 ins 1..24,
    append([D1,D2,D3,D4], Vars),
    all_distinct(Vars),
    findall([N1, N2, N3, N4], (word([A, B, C, D]), num(A, N1), num(B, N2), num(C, N3), num(D, N4)), Words),
    findall([X,Y],(member(S, Words), member(X, S), member(Y, S), X < Y), Temp),
    sort(Temp, Incompatibilities),

    diff(D1, Incompatibilities),
    diff(D2, Incompatibilities),
    diff(D3, Incompatibilities),
    diff(D4, Incompatibilities),
    
    poner_orden(D1),
    poner_orden(D2),
    poner_orden(D3),
    poner_orden(D4),
    labeling([ff],Vars),
    writeN(D1), 
    writeN(D2), 
    writeN(D3), 
    writeN(D4), halt.
    
writeN(D):- findall(X,(member(N,D),num(X,N)),L), write(L), nl, !.

%a partir de aquí todo es mío
diff(_, []):-!.
diff(Dado,[[X,Y]|L]):-
    individual(Dado, [X,Y]),
    diff(Dado,L).

individual([],_):- !.
individual([X|L],L2):-
    ultimoFOR(X,L,L2),
    individual(L,L2).

ultimoFOR(_,[],_):-!.
ultimoFOR(X,[Y|L], L2):-
    checkeo(X,Y,L2),
    ultimoFOR(X,L,L2).

checkeo(P1,P2,[X,Y]):-
    P1 #\= X #\/ P2 #\= Y.



poner_orden([X,Y | L]):- X #< Y, poner_orden([Y|L]).
poner_orden([X,Y]):- X #< Y, !.