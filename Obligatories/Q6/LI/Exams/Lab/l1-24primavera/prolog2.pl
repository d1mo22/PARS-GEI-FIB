%% --------- [2.5 points] ---------- %%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Acme Corporation is organized in departments, and groups its
%% projects and the workers who work in them, as shown below.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% project( dept, projId, listOfWorkers ).
project( prod, proj1,  [w1, w5] ).
project( prod, proj2,  [w1, w2, w3] ).
project( prod, proj3,  [w1, w3] ).
project( prod, proj4,  [w2, w4, w6, w8] ).
project( prod, proj5,  [w2, w4, w5] ).
project( prod, proj6,  [w6, w7] ).
project( prod, proj7,  [w3, w7] ).
project( prod, proj8,  [w6, w7, w8] ).
project( r+d,  proj9,  [w9, w11] ).
project( r+d,  proj10, [w10, w12] ).
project( r+d,  proj11, [w10, w11] ).
project( r+d,  proj12, [w9, w12] ).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Complete the predicates dept_lprojs/2, share_some_worker/1 and main/2,
%% in order to operate as required.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% dept_lprojs(+D, -L): holds if L is the list of projects of dept. D 
dept_lprojs(D,L) :-
    findall(P, project(D,P,_),L).     % <---- Complete this
    % Busca todos los proyectos P, tales que tengan como departamento D
% share_some_worker(+L): given a list of projects L,
%                        holds if there exist some worker in TWO or MORE of the projects of L
% For example:
% ?- share_some_worker([proj1,proj3,proj6]).
% true.
share_some_worker(L) :-
    % X es el primer proyecto de la lista R es el resto
    select(X, L, R),
    member(Y,R),
    project(_,X,LX), % LX son todos los miembros del projecto X
    project(_,Y,LY), % LY son todos los miembros del proyecto Y
    member(W,LX), member(W,LY),!.
    % ...               % <---- Complete this


% Given a dept D, and an integer MinSize, the predicate main/2 writes all different subsets
% of the projects of dept. D (subsets of size >= MinSize) that do not share any worker.
% It writes them in descending order of subset size.
% Among subsets of the same size, any order is allowed.
% Note that this predicate can never fail.
% For example:
% ?- main(prod,3).
% [proj1,proj4,proj7]
% [proj3,proj5,proj6]
% [proj3,proj5,proj8]
% true.
% ?- main(r+d,6).
% true.
main(D,MinSize) :-
    dept_lprojs(D,L),
    length(L, M), 
    between(0,M,K), N is M-K, N>=MinSize,
    subsetOfSize(N,L,S),
    \+ share_some_worker(S),
    write(S),nl,fail.
    % ...               % <---- Complete this
main(_,_).              % <---- Complete this

% You can find this predicate useful:
% subsetOfSize(+N, +L, -S): given a natural N, and a set L (a list),
%                           holds if S is subset of L with cardinality N
subsetOfSize(0,_,[]) :- !.
subsetOfSize(N,[X|L],[X|S]) :- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ) :-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).

