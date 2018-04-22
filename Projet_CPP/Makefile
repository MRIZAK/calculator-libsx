CXXFLAGS = -std=c++11 -Wall -g -O0
SRC = main.cpp callback.cpp Affichage.cpp Pile.cpp 
SRC_TEST= callback.cpp Affichage.cpp Pile.cpp Test_Pile.cpp Test_Affichage.cpp
INC = Affichage.hpp callback.hpp Pile.hpp Catch.hpp
OBJ = $(SRC:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)

all:
	make main-calc

main-calc: $(OBJ)
	g++ -o $@ $^ -lsx

test-calc: $(OBJ_TEST)
	g++ -o $@ $^ -lsx

main.o: main.cpp

Affichage.o:Affichage.cpp Affichage.hpp

callback.o: callback.cpp callback.hpp

Pile.o:Pile.cpp Pile.hpp

Test_Affichage.o: Test_Affichage.cpp Catch.hpp

Test_Pile.o:Test_Pile.cpp Catch.hpp

cleaner: clean
	rm -f main-calc
	rm -f test-calc

clean:
	rm -f *.o

test:
	make test-calc

