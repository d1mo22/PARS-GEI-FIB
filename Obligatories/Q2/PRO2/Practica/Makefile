OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

G++ = g++-10

program.exe: program.o Cluster.o Procesador.o Area_espera.o Prioridad.o Job.o
	g++ $(OPCIONS) -o program.exe program.o Cluster.o Procesador.o Area_espera.o Prioridad.o Job.o

program.o: program.cc
	g++ $(OPCIONS) -c program.cc

Job.o: Job.cc Job.hh
	g++ $(OPCIONS) -c Job.cc

Prioridad.o: Prioridad.cc Prioridad.hh
	g++ $(OPCIONS) -c Prioridad.cc

Procesador.o: Procesador.cc Procesador.hh
	g++ $(OPCIONS) -c Procesador.cc

Cluster.o: Cluster.cc Cluster.hh
	g++ $(OPCIONS) -c Cluster.cc

Area_espera.o: Area_espera.cc Area_espera.hh
	g++ $(OPCIONS) -c Area_espera.cc

clean:
	rm -f *.o
	rm -f *.exe

tar: Makefile program.cc BinTree.hh Job.cc Job.hh Prioridad.cc Prioridad.hh Procesador.cc Procesador.hh Cluster.cc Cluster.hh Area_espera.cc Area_espera.hh
	tar -cvf practica.tar Makefile program.cc BinTree.hh Job.cc Job.hh Prioridad.cc Prioridad.hh Procesador.cc Procesador.hh Cluster.cc Cluster.hh Area_espera.cc Area_espera.hh