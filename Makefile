all: solitaire

solitaire: structures.o autosolve.o uiBoard.o data.o rules.o main.o
	gcc -o solitaire structures.o autosolve.o uiBoard.o data.o rules.o main.o -O3

structures.o: structures.c
	gcc -Wall structures.c -o structures.o -c -O3

autosolve.o: autosolve.c
	gcc -Wall autosolve.c -o autosolve.o -c -O3

uiBoard.o: uiBoard.c
	gcc -Wall uiBoard.c -o uiBoard.o -c -O3

data.o: data.c
	gcc -Wall data.c -o data.o -c -O3

rules.o: rules.c
	gcc -Wall rules.c -o rules.o -c -O3

clean_o:
	rm -rf *.o

clean:
	rm -rf *.o
	rm solitaire