% Define a predicate ipl(T,K) that is true if K is the internal path length of the tree T.
% We represent a tree by a term t(X,F), where X denotes the root and F is the list containing
% the forest of subtrees. For example, the tree
% example 1:   a
%             /|\
%            f c b
%            |  / \
%            g d   e
%
% is represented by the term T = t(a,[t(f,[t(g,[])]),t(c,[]),t(b,[t(d,[]),t(e,[])])]).
% The internal path length of a tree is the total sum of the path lengths from the root to all 
% nodes of the tree. For example, T has an internal path length of 0 + 1 + 2 + 1 + 1 + 2 + 2 = 9.
%                                                                  ^a  ^f  ^g  ^c  ^b  ^d  ^e
example( 1, t(a,[t(f,[t(g,[])]),t(c,[]),t(b,[t(d,[]),t(e,[])])]) ).  % internal path length = 9

% example 2:     a
%               / \
%              b   c
%                 / \
%                d   e
%
example( 2, t(a,[t(b,[]),t(c,[t(d,[]),t(e,[])])]) ).                 % internal path length = 6

% example 3:     a
%               / \
%              b   c
%                 / \
%                d   e
%               / \
%              f   g
%
example( 3, t(a,[t(b,[]),t(c,[t(d,[t(f,[]),t(g,[])]),t(e,[])])]) ).  % internal path length = 12


%% ipl(T,K) holds
%%   if the internal path length of the tree T is K:
%%   "the total sum of the path lengths from the root to all its nodes is K"
ipl(T,K) :- ipl(T,0,K).

%% ipl(T,D,K) holds
%%   if the (sub)tree T, located at depth D wrt the root, has internal path length K:
%%   "the total sum of the path lengths from the root to all its nodes is K"
ipl(t(r,[]),D,D).
ipl(t(_,F),D,K) :-  
    D1 is D+1, % Bajamos 1 en profundidad
    ipl_forest(F,D1,KF), % Vemos la suma de todos los hijos
    K is D + KF. % Sumamos D + la suma de todos los hijos
	    
ipl_forest([],_,0).
ipl_forest([T|Ts],D,K) :-
    ipl(T,D,K1), % Calculamos el IPL del primer subarbol T a profundidad D
    ipl_forest(Ts,D,K2), % Calculamos el resto del bosque con la misma profundidad
    K is K1 + K2. % Sumamos ambos valores

main(N) :- example(N,T), ipl(T,K), write(K), nl.

