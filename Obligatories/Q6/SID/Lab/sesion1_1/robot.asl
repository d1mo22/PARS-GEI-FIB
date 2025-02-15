/* Beliefs */
adyacente(a, b).
adyacente(b, c).
adyacente(c, d).
adyacente(d, a).

localizado(robot, a).
localizado(papel_usado, d).
localizado(papelera, c).


/* Goals */
!tirado(papel_usado, papelera).

/* Events */	
+localizado(robot, X) : localizado(papel_usado, X)
			<- .print("papel cogido en ", X); 
			   -localizado(papel_usado, X); 
			   +llevando(papel_usado).

+localizado(robot, X) : localizado(papelera, X) &
				llevando(papel_usado)
			<- .print("todo el papel tirado a la papelera en ", X).

+!localizado(robot, X) : localizado(robot, X) <- .print("Ha llegado a su destino").
 
+!localizado(robot, X) : localizado(robot, Y) &
				(not (X=Y)) & adyacente(Y,Z) 
			<- .print("mover de ", Y, " a ", Z); 
			   -localizado(robot, Y); 
			   +localizado(robot, Z);
               !localizado(robot, X).
