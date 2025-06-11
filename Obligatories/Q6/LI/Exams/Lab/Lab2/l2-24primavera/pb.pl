
%% ----------- [2.5 points] ---------- %%


/*
A *pseudo-boolean* (PB) constraint is a formula of the form

  a1 x1 + ... + an xn >= a0

where
  a0, a1, ..., an  are non-negative integers, and
      x1, ..., xn  are Boolean variables (that is, they take values 0 or 1).

An interpretation (that is, a Boolean assignment to the variables) is a model
of the PB constraint if the inequality holds when variables are instantiated
according to the assignment.

For instance, x1 + 3 x2 + 3 x3 >= 4 is a PB constraint,
and the interpretation [x1, x2, x3] = [1, 0, 1] is a model.
However, [x1, x2, x3] = [1, 0, 0] is not a model.

Logical consequence of PB constraints is defined using the notion of
model like with propositional formulas, i.e., given two PB constraints
A >= R, and B >= S, we say that  A >= R |= B >= S  iff any model of
A >= R is also a model of B >= S.
Hint: remember that, given two propositional formulas F anf G,
G is a logical consequence of F, denoted F |= G, iff the formula
F & -G is unsatisfiable. 

Using Constraint Logic Programming, complete the following predicates:

(1) implies: implies(Premise, Consequence) holds iff
Consequence is a logical consequence of Premise, i.e., Premise |= Consequence.

(2) does_not_imply: does_not_imply(Premise, Consequence, X) holds iff
Consequence is *not* a logical consequence of Premise,
and, in that case, X is a counterexample that the logical consequence
does not hold, i.e., X is a model of Premise, but is not of Consequence. 

Below, a PB constraint is represented as the list of coefficients on
the left-hand side together with '>=' and the right-hand side. For
example, x1 + 3 x2 + 3 x3 >= 4 would be represented as [1, 3, 3] >= 4.

Assume that the left-hand sides of the premise and the consequence
have the same length.

For instance,

  ?- implies([1, 3, 3] >= 4, [1, 1, 1] >= 2).
  true

should hold, because  1 x1 + 1 x2 + 1 x3 >= 2  is a logical consequence
of  1 x1 + 3 x2 + 3 x3 >= 4.

However,

  ?- implies([1, 3, 3] >= 4, [1, 1, 1] >= 3).
  false

should not.

Similarly, 

  ?- does_not_imply([1, 3, 3] >= 4, [1, 1, 1] >= 3, X).
  X = [0, 1, 1]

should hold, because  1 x1 + 1 x2 + 1 x3 >= 3  is *not* a logical
consequence of  1 x1 + 3 x2 + 3 x3 >= 4,
and [x1, x2, x3] = [0, 1, 1] is a counterexample, whereas

  ?- does_not_imply([1, 3, 3] >= 4, [1, 1, 1] >= 2, X).
  false

should not, because  1 x1 + 1 x2 + 1 x3 >= 2  is a logical
consequence of  1 x1 + 3 x2 + 3 x3 >= 4.
*/


:- use_module(library(clpfd)).

% instance(ID, A >= R, B >= S).
instance(a, [1, 3, 3] >= 4, [1, 1, 1] >= 2).              %% implies
instance(b, [1, 3, 3] >= 4, [1, 1, 1] >= 3).              %% does not imply
instance(c, [4, 3, 4, 3, 2] >= 5, [2, 1, 2, 2, 1] >= 3).  %% does not imply


% does_not_imply(A >= R, B >= S, X) holds iff B >= S is *not* a logical
%     consequence of A >= R, and, in that case, X is a counterexample 
does_not_imply(A >= R, B >= S, X) :-
  %1: Variables and domains:
    length(A, N),
    length(X, N),
    ...
  %2: Constraints:
    ...
  %3: Labeling:
    label(X),
  %4: Result:
    true. %% A >= R does not imply B >= S, and X is a counterexample


% implies(A >= R, B >= S) holds iff B >= S is a logical consequence
%     of A >= R
implies(A >= R, B >= S) :-
    does_not_imply(A >= R, B >= S, _), !,
    ...
...


main(N) :-
    instance(N, Premise, Consequence),
    implies(Premise, Consequence), !,
    write(implies(Premise, Consequence)), nl.
main(N) :-
    instance(N, Premise, Consequence),
    write(does_not_imply(Premise, Consequence)), nl.
