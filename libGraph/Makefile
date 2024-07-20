TESTS = ./tests
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
LIB_NAMES = -lGraph
SRC = ./src
TESTS_SRC = $(SRC)/unit_tests
FLAGS = -std=c99 -flto -O3 -Wall -Wextra

# Obter todos os arquivos de teste
UNIT_TESTS = $(wildcard $(TESTS_SRC)/*.c)

# Gerar nomes de executáveis para os arquivos de teste
TEST_EXECUTABLES = $(patsubst $(TESTS_SRC)/%.c, $(TESTS)/%, $(UNIT_TESTS))

all: lib tests

lib: 	$(BIN)/List.o 			\
	 	$(BIN)/List_W.o 		\
		$(BIN)/Queue.o			\
		$(BIN)/Stack.o			\
		$(BIN)/PriorityQueue.o	\
		$(BIN)/Util.o		\
		$(BIN)/CCUtil.o			\
		$(BIN)/L_Graph.o		\
		$(BIN)/M_Graph.o		\
		$(BIN)/MW_Graph.o		\
		$(BIN)/LW_Graph.o
	ar -rcs $(LIB)/libGraph.a $(BIN)/*.o

main: $(SRC)/main.c $(SRC)/main2.c
	gcc $(FLAGS) $(SRC)/main.c $(BIN)/*.o $(LIB_NAMES) -L $(LIB) -I $(INCLUDE) -o $(TESTS)/main

# Target para compilar todos os testes
tests: $(TEST_EXECUTABLES)

# Regra para compilar cada arquivo de teste em um executável
$(TESTS)/%: $(TESTS_SRC)/%.c
	gcc $(FLAGS) -o $@ $< $(BIN)/*.o

# Compila códigos objeto
$(BIN)/%.o: $(SRC)/%.c
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

clear:
	rm $(BIN)/*.o $(TESTS)/* $(LIB)/*.a
	touch $(TESTS)/.gitkeep

cls:
	del /Q "$(BIN)\*.o" "$(TESTS)\*.exe" "$(LIB)\*.a"