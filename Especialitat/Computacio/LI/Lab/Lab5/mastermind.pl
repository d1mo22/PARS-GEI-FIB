% C.1 
exactas([], [], 0).
exactas([C|Codi], [I|Intent], E) :-
    C == I, !,  
    exactas(Codi, Intent, E1),
    E is E1 + 1.
exactas([_|Codi], [_|Intent], E) :-
    exactas(Codi, Intent, E).

totales(Codi, Intent, T) :-
    cuenta_colores(Codi, CodiCuenta),
    cuenta_colores(Intent, IntentCuenta),
    coincidencias_totales(CodiCuenta, IntentCuenta, T).

cuenta_colores(Lista, Cuenta) :-
    cuenta_colores(Lista, [v, b, g, l, t, m], Cuenta).

cuenta_colores(_, [], []).
cuenta_colores(Lista, [Color|Colores], [[Color, N]|Resto]) :-
    contar_ocurrencias(Color, Lista, N),
    cuenta_colores(Lista, Colores, Resto).

contar_ocurrencias(_, [], 0).
contar_ocurrencias(Color, [Color|Resto], N) :- !,
    contar_ocurrencias(Color, Resto, N1),
    N is N1 + 1.
contar_ocurrencias(Color, [_|Resto], N) :-
    contar_ocurrencias(Color, Resto, N).

coincidencias_totales([], _, 0).
coincidencias_totales([[Color, N1]|Resto], IntentCuenta, T) :-
    buscar_color(Color, IntentCuenta, N2),
    Min is min(N1, N2),
    coincidencias_totales(Resto, IntentCuenta, T1),
    T is T1 + Min.

buscar_color(_, [], 0).
buscar_color(Color, [[Color, N]|_], N) :- !.
buscar_color(Color, [[_|_]|Resto], N) :-
    buscar_color(Color, Resto, N).

resposta(Codi, Intent, E, D) :-
    exactas(Codi, Intent, E),
    totales(Codi, Intent, T),
    D is T - E, !.

% C.2 
color(b).
color(g).
color(l).
color(t).
color(m).

intents([ [ [v,b,g,l], [1,1] ], [ [m,t,g,l], [1,0] ], [ [g,l,g,l], [0,0] ],
         [ [v,b,m,m], [1,1] ], [ [v,t,b,t], [2,2] ] ]).

generar_codigo([A, B, C, D]) :-
    color(A),
    color(B),
    color(C),
    color(D).

consistente(Codigo, [Intent, [E, D]]) :-
    resposta(Codigo, Intent, E, D).

consistente_todos(_, []).
consistente_todos(Codigo, [Intento|Resto]) :-
    consistente(Codigo, Intento),
    consistente_todos(Codigo, Resto).

nouIntent(A) :-
    generar_codigo(A),
    intents(Intentos),
    consistente_todos(A, Intentos), !.
