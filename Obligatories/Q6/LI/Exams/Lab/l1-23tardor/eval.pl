%% --------- [3 points] ---------- %%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Given an expression built up from integers, variables, +, - and *, and
% given an assignment of values to some of the variables, 
% write a Prolog predicate eval that evaluates the expression on the assignment.

% If an expression contains an unassigned variable, the result should be 'evalError'.

% You can use the predicate integer(X), which holds iff X is an integer value.

% For example:
%
% ?- eval((x+y)*(x-y), [assign(x, 2), assign(y, 1)], V).
% V = 3.
% 
% ?- eval(x*x + 1 - y, [assign(x, 3), assign(y, 2)], V).
% V = 8.
%
% ?- eval(x*x + 1 - y, [assign(x, 3)], V).
% V = evalError.

% Hint: write a predicate "my_is" or similar, and use it in eval.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% eval(E, L, V)  holds
%     if the expression E on the assignment L evaluates to the value V
eval(A + B, L, V) :- !,
    eval(A,L,VA),
    eval(B,L,VB),
    my_is(VA+VB,V),
    write(eval-suma),nl.
eval(A - B, L, V) :- !,
    eval(A,L,VA),
    eval(B,L,VB),
    my_is(VA-VB,V),
    write(eval-resta),nl.
eval(A * B, L, V) :- !,
    eval(A,L,VA),
    eval(B,L,VB),
    my_is(VA*VB,V),
    write(eval-mult),nl.
eval(N, _, N) :- integer(N), write(eval-numero),nl,!.
eval(X,L,V) :- member(assign(X,V),L),write(eval-variable),nl,!.
eval(_,_,evalError) :- write(eval-error),nl.

% my_is  holds
%     if the expression E evaluates to the value V
% my_is(evalError + _, evalError) :- !.
% my_is(_ + evalError, evalError) :- !.
my_is(E+F,evalError) :- member(evalError,[E,F]),!.
my_is(E+F,G) :- G is E + F.

% my_is(evalError - _, evalError) :- !.
% my_is(_ - evalError, evalError) :- !.
my_is(E-F,evalError) :- member(evalError, [E,F]),!.
my_is(E-F,G) :- G is E - F.

% my_is(evalError * _, evalError) :- !.
% my_is(_ * evalError, evalError) :- !.
my_is(E*F,evalError) :- member(evalError, [E,F]),!.
my_is(E*F,G) :- G is E * F.
