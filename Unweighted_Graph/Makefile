APP = ./app
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
LIB_NAMES = -lGraph
SRC = ./src
FLAGS = -flto -O3 -Wall -Wextra

all: lib main

lib: 	$(BIN)/List.o 		\
		$(BIN)/Queue.o		\
		$(BIN)/M_UGraph.o 	\
		$(BIN)/L_UGraph.o 	
	ar -rcs $(LIB)/libGraph.a $(BIN)/*.o

main: $(SRC)/main.c $(SRC)/main2.c
	gcc -g $(FLAGS) $(SRC)/main.c $(BIN)/*.o $(LIB_NAMES) -L $(LIB) -I $(INCLUDE) -o $(APP)/main
	gcc -g $(FLAGS) $(SRC)/main2.c $(BIN)/*.o $(LIB_NAMES) -L $(LIB) -I $(INCLUDE) -o $(APP)/main2

$(BIN)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

run:
	./app/main2

clear:
	rm $(BIN)/* $(APP)/* $(LIB)/*