OPCIONS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Area_de_espera.o Cluster.o Cpu.o Prioritat.o Proces.o
	g++ -o program.exe program.o Area_de_espera.o Cluster.o Cpu.o Prioritat.o Proces.o

Area_de_espera.o: Area_de_espera.cc Area_de_espera.hh
	g++ -c Area_de_espera.cc $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh
	g++ -c Cluster.cc $(OPCIONS)

Cpu.o: Cpu.cc Cpu.hh
	g++ -c Cpu.cc $(OPCIONS)

Prioritat.o: Prioritat.cc Prioritat.hh
	g++ -c Prioritat.cc $(OPCIONS)

Proces.o: Proces.cc Proces.hh
	g++ -c Proces.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

practica.tar:
	tar -cvf practica.tar program.cc Area_de_espera.cc Prioritat.cc Cluster.cc Cpu.cc Proces.cc BinTree.hh Area_de_espera.hh Prioritat.hh Cluster.hh Cpu.hh Proces.hh Makefile

clean:
	rm *.o
	rm *.exe 
