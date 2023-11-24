Amb aquesta carpeta estan els algoritmes necessaris per generar i recórrer laberints.

Per generar els laberints fem servir Lab_gen.cc.
Per recórrer els laberints amb DFS/BFS farem servir els seus respectius .cc.
Tots 3 programes tenen al principi 2 paràmetres que són el nombre de files i columnes que vulguem.

fer servir tant per generar o recórrer laberints nxm.
També tenim dues carpetes (Laberintos/Laberintos_100) a la primera carpeta trobem els 100 laberints generats amb dimensions 1000x1000, 
mentre que a la segona trobem els 100 laberints generats amb dimensions 100x100.

Per facilitar la compilació del programa tenim un Makefile que ens compila tots 3 programes.

A l'hora de realitzar la generació dels laberints tenim un script amb Bash (Laberinto.sh) que ens permet generar n laberints 
i els guarda tots a la carpeta indicada al principi del codi.

Finalment, l'script (Algo.sh) que ens permet a partir d'una carpeta executar tant el DFS com BFS 
per cada un dels laberints que hi trobem a la carpeta.

Cal tenir en compte que si els paràmetres de files o columnes dels algoritmes DFS/BFS 
són diferents dels que hem fet servir a l'hora de generar els laberints no funcionarà.
