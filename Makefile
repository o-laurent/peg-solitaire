all: solitaire

solitaire: structures.o feasible.o autosolve.o uiBoard.o data.o rules.o main.o
	gcc -o solitaire structures.o feasible.o autosolve.o uiBoard.o data.o rules.o main.o -ggdb3

structures.o: structures.c
	gcc -Wall structures.c -o structures.o -c 

feasible.o: feasible.c
	gcc -Wall feasible.c -o feasible.o -c 

autosolve.o: autosolve.c
	gcc -Wall autosolve.c -o autosolve.o -c 

uiBoard.o: uiBoard.c
	gcc -Wall uiBoard.c -o uiBoard.o -c 

data.o: data.c
	gcc -Wall data.c -o data.o -c 

rules.o: rules.c
	gcc -Wall rules.c -o rules.o -c 

clean_o:
	rm -rf *.o

clean:
	rm -rf *.o
	rm solitaire