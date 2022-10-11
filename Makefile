CC = g++
LIBS = -lm 
SRC = src
OBJ = ./obj/
INC = ./include/
BIN = ./bin/
OBJS = $(OBJ)/campanha.o $(OBJ)/main.o
HDRS = $(INC)/campanha.hpp
CFLAGS = -g -Wall -c -I$(INC)

EXE = $(BIN)/tp01

all: run

run: $(BIN)/tp01

$(BIN)/tp01: $(OBJS)
	$(CC) -g -o $(BIN)/tp01 $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC)  $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/campanha.o: $(HDRS) $(SRC)/campanha.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/campanha.o $(SRC)/campanha.cpp 

clean:
	rm -f $(EXE)* $(OBJS)* $(BIN)* 
	clear   