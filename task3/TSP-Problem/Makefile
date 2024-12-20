CC = g++

CFLAGS = -std=c++20

default: make

make: main.o geneticAlg.o userParse.o
	$(CC) $(CFLAGS) -o main main.o geneticAlg.o userParse.o -lm


geneticAlg.o: geneticAlg.cpp geneticAlg.hpp
	$(CC) $(CFLAGS) -c geneticAlg.cpp

userParse.o: userParse.cpp userParse.hpp
	$(CC) $(CFLAGS) -c userParse.cpp


main.o: main.cpp geneticAlg.hpp userParse.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) *.o *~ main
