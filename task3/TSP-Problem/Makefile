CC = g++

CFLAGS = -std=c++23

LIBS = -lm -lbenchmark -lpthread

default: make

make: main.o geneticAlg.o userParse.o
	$(CC) $(CFLAGS) -o main main.o geneticAlg.o userParse.o $(LIBS)

geneticAlg.o: geneticAlg.cpp geneticAlg.hpp
	$(CC) $(CFLAGS) -c geneticAlg.cpp

userParse.o: userParse.cpp userParse.hpp
	$(CC) $(CFLAGS) -c userParse.cpp

main.o: main.cpp geneticAlg.hpp userParse.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) *.o *~ main
