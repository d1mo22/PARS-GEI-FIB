/* Creencias iniciales */
limit(7).
fact(0, 1).

/* Planes */
+fact(X, Y): limit(L) & X < L <-
   +fact(X + 1, (X + 1) * Y).

+fact(X, Y): limit(L) & X == L <-
   .print("fact ", L, " == ", Y).