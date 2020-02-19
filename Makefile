all: solitaire

solitaire: structures.o uiBoard.o data.o main.o
	gcc -o solitaire structures.o uiBoard.o data.o main.o

structures.o: main.c
	gcc -Wall structures.c -o structures.o -c 

data.o: data.c
	gcc -Wall data.c -o data.o -c 

uiBoard.o: uiBoard.c
	gcc -Wall uiBoard.c -o uiBoard.o -c 

clean:
	rm -rf *.o