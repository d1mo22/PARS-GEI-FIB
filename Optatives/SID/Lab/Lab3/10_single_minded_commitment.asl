g :- a1 | a2.
fail :- a3.

!g.
c3.

+!g: g <- .print("goal g has succeeded").

+!g : c1 & not fail <- +a1; !g.
+!g : c2 & not fail <- +a2; !g.
+!g : c3 & not fail <- +a3; !g.

+!g: fail <- -a1; -a2; -a3; -fail; .print("goal g has failed"); !g2. // goal has failed
+!g: true <- !g. // keep trying

+!g2 <- .print("goal g2 has succeeded").
