APP = ./app
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
LIB_NAMES = -lGraph
SRC = ./src
FLAGS = -flto -O3 -Wall -Wextra

all: lib main

lib: 	$(BIN)/M_UGraph.o	\
		$(BIN)/L_UGraph.o
	ar -rcs $(LIB)/libGraph.a $(BIN)/*.o

main: $(SRC)/main.c
	gcc $(FLAGS) $< $(BIN)/*.o $(LIB_NAMES) -L $(LIB) -I $(INCLUDE) -o $(APP)/main

$(BIN)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

run:
	./app/main

clear:
	rm $(BIN)/* $(APP)/* $(LIB)/*