CXXFLAGS = -std=c++11 -Wall -g -O0
SRC = main.cpp callback.cpp Affichage.cpp
INC = Affichage.hpp callback.hpp
OBJ = $(SRC:.cpp=.o)


test: $(OBJ)
	g++ -o $@ $^ -lsx

main.o: main.cpp

Affichage.o:Affichage.cpp Affichage.hpp

callback.o: callback.cpp callback.hpp

cleaner: clean
	rm -f test

clean:
	rm -f *.o