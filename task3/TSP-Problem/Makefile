CC = g++

CFLAGS = -std=c++23

LDFLAGS = -lm -lbenchmark -lpthread

BENCHMARK_OUT_FILE = "output.json"
BENCHMARK_OUT_FORMAT = json

TEST ?= OFF
BENCHMARK_OUT ?= OFF

SRC = main.cpp geneticAlg.cpp userParse.cpp
OBJ = $(SRC:.cpp=.o)
PROG = main

.PHONY: make run clean

default: make 

make: $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS)


geneticAlg.o: geneticAlg.cpp geneticAlg.hpp
	$(CC) $(CFLAGS) -c geneticAlg.cpp

userParse.o: userParse.cpp userParse.hpp
	$(CC) $(CFLAGS) -c userParse.cpp

main.o: main.cpp geneticAlg.hpp userParse.hpp
ifeq ($(TEST), ON)
	$(CC) $(CFLAGS) -c main.cpp -DTEST
else
	$(CC) $(CFLAGS) -c main.cpp
endif

run: $(PROG)
ifeq ($(BENCHMARK_OUT), ON)
	./$(PROG) --benchmark_out=$(BENCHMARK_OUT_FILE) --benchmark_out_format=$(BENCHMARK_OUT_FORMAT)
else 
	./$(PROG)
endif

clean:
	$(RM) $(OBJ) $(PROG)
