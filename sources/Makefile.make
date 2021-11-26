CC = g++
OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11


all: dynamic

driver_maze.exe: driver_maze.o check.o cambra.o laberint.o particio.t teseus.o dedalus.o
	g++ -o driver_maze.exe driver_maze.o check.o cambra.o laberint.o particio.t teseus.o dedalus.o -lesin
	rm *.o

teseus.o: solution.cpp llista.hpp
	g++ -Wall -c teseus.cpp $(OPCIONS)

dedalus.o: solution.cpp llista.hpp
	g++ -Wall -c dedalus.cpp $(OPCIONS)

laberint.o: solution.cpp llista.hpp
	g++ -Wall -c laberint.cpp $(OPCIONS)

cambra.o: cambra.cpp 
	g++ -Wall -c cambra.cpp $(OPCIONS)

paret.o: paret.hpp
	g++ -Wall -c paret.hpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
