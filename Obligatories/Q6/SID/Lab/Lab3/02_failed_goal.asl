!g. // goal declaration
    // but now there is no context!

+!g: g <- .print("goal achieved").
+!g: c1 <- !sg1; !g. // plan for g under context {c1}
+!g: c2 <- !sg2; !g. // plan for g under context {c2}
// ...
+!g: cn <- !sgn; !g. // plan for g under context {cn}
+!g <- .print("goal g has failed!").

+!sg1 <- .print("executing subgoal1"); +g.
+!sg2 <- .print("executing subgoal2"); +g.
// ...
+!sgn <- .print("executing subgoaln"); +g.
