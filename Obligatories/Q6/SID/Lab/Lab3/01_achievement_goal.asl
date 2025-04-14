!g. // goal declaration
c1. // context (a fact)

+!g: g <- .print("goal achieved").
+!g: c1 <- !sg1; !g. // plan for g under context {c1}
+!g: c2 <- !sg2; !g. // plan for g under context {c2}
// ...
+!g: cn <- !sgn; !g. // plan for g under context {cn}

+!sg1 <- .print("executing subgoal1"); +g.
+!sg2 <- .print("executing subgoal2"); +g.
// ...
+!sgn <- .print("executing subgoaln"); +g.
