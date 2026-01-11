!g. // goal declaration
c1. // context (a fact)
!test_g_again.

+!g: solution(X) & g <- .print("goal achieved using solution", X).
+!g: not solution(1) & c1 <- !sg1; +solution(1); !g. // plan for g under context {c1}
+!g: not solution(2) & c2 <- !sg2; +solution(2); !g. // plan for g under context {c2}
// ...
+!g: not solution(n) & cn <- !sgn; +solution(n); !g. // plan for g under context {cn}

+!sg1 <- .print("executing subgoal1"); +g.
+!sg2 <- .print("executing subgoal2"); +g.
// ...
+!sgn <- .print("executing subgoaln"); +g.

+!test_g_again <- -c1; -g; +c2; !g.