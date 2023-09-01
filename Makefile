SRC_DIR=peg_solitaire
BIN_DIR=bin

all: solitaire

solitaire: structures.o autosolve.o uiBoard.o data.o rules.o main.o
	gcc -o solitaire.app $(BIN_DIR)/structures.o $(BIN_DIR)/autosolve.o $(BIN_DIR)/uiBoard.o $(BIN_DIR)/data.o $(BIN_DIR)/rules.o $(BIN_DIR)/main.o -O3

structures.o:
	gcc -Wall $(SRC_DIR)/structures.c -o $(BIN_DIR)/structures.o -c -O3

autosolve.o:
	gcc -Wall $(SRC_DIR)/autosolve.c -o $(BIN_DIR)/autosolve.o -c -O3

uiBoard.o:
	gcc -Wall $(SRC_DIR)/uiBoard.c -o $(BIN_DIR)/uiBoard.o -c -O3

data.o:
	gcc -Wall $(SRC_DIR)/data.c -o $(BIN_DIR)/data.o -c -O3

rules.o:
	gcc -Wall $(SRC_DIR)/rules.c -o $(BIN_DIR)/rules.o -c -O3

main.o:
	gcc -Wall $(SRC_DIR)/main.c -o $(BIN_DIR)/main.o -c -O3

clean_o:
	rm -rf *.o

clean:
	rm -rf *.o
	rm solitaire