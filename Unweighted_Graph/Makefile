TESTS = ./tests
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
LIB_NAMES = -lGraph
SRC = ./src
FLAGS = -flto -O3 -Wall -Wextra

all: lib main

lib: 	$(BIN)/List.o 		\
		$(BIN)/Queue.o		\
		$(BIN)/Stack.o		\
		$(BIN)/GraphUtil.o	\
		$(BIN)/CCUtil.o		\
		$(BIN)/L_Graph.o	\
		$(BIN)/M_Graph.o
	ar -rcs $(LIB)/libGraph.a $(BIN)/*.o

main: $(SRC)/main.c $(SRC)/main2.c
	gcc -g $(FLAGS) $(SRC)/main.c $(BIN)/*.o $(LIB_NAMES) -L $(LIB) -I $(INCLUDE) -o $(TESTS)/main
	gcc -g $(FLAGS) $(SRC)/main2.c $(BIN)/*.o $(LIB_NAMES) -L $(LIB) -I $(INCLUDE) -o $(TESTS)/main2

$(BIN)/%.o: $(SRC)/%.c
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

run:
	$(TESTS)/main2

clear:
	rm $(BIN)/* $(TESTS)/* $(LIB)/*