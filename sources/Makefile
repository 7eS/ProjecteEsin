OPCIONS = -g -O0 -Wall -Wextra  -std=c++11 -ansi -Wimplicit-fallthrough=0 

program.exe: driver_maze.o cambra.o laberint.o teseus.o dedalus.o check.o
	g++ -o program.exe driver_maze.o cambra.o laberint.o teseus.o dedalus.o check.o -lesin


driver_maze.o: driver_maze.cpp cambra.hpp cambra.rep laberint.rep teseus.hpp dedalus.hpp particio.rep particio.hpp particio.t
	g++ -c driver_maze.cpp $(OPCIONS)
	
check.o: check.cpp laberint.cpp laberint.hpp laberint.rep
	g++ -c check.cpp $(OPCIONS)

teseus.o: teseus.cpp teseus.hpp laberint.cpp laberint.rep laberint.hpp
	g++ -c teseus.cpp $(OPCIONS)

dedalus.o: dedalus.cpp dedalus.hpp laberint.cpp laberint.hpp laberint.rep particio.t particio.rep particio.hpp
	g++ -c dedalus.cpp $(OPCIONS)

laberint.o: laberint.cpp laberint.hpp laberint.rep cambra.cpp cambra.hpp cambra.rep
	g++ -c laberint.cpp $(OPCIONS)

cambra.o: cambra.cpp cambra.hpp cambra.rep paret.hpp 
	g++ -c cambra.cpp $(OPCIONS)

paret.o: paret.hpp
	g++ -c paret.hpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
