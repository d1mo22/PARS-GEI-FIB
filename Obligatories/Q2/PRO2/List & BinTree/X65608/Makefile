OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Estudiant.o BinTreeIOEst.o
	g++ -o program.exe program.o Estudiant.o BinTreeIOEst.o
	rm *.o

program.o: program.cc PRO2Excepcio.hh BinTree.hh BinTreeIOEst.hh Estudiant.hh
	g++ -c program.cc $(OPCIONS)

Estudiant.o: Estudiant.cc PRO2Excepcio.hh Estudiant.hh
	g++ -c Estudiant.cc $(OPCIONS)

BinTreeIOEst.o: BinTreeIOEst.cc BinTree.hh BinTreeIOEst.hh Estudiant.hh
	g++ -c BinTreeIOEst.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
