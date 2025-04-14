!g1. // initial goal

+!g3: g <- .print("g3 achieved!").

+!g1: true <- !g2; .print("end g1").
+!g2: true <- !g3; .print("end g2").
+!g3: not fail <- !g4; .print("end g3"); !!g3.
+!g4: true <- !g5; .print("end g4").
+!g5: true <- .print("end g5 without reaching goal"); +fail.

+!g3: fail <- .print("handling g3 failure"); +g; !!g3.
