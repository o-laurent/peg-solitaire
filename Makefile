all: solitaire

solitaire: structures.o uiBoard.o data.o rules.o main.o
	gcc -o solitaire structures.o uiBoard.o data.o rules.o main.o

structures.o: structures.c
	gcc -Wall structures.c -o structures.o -c 

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