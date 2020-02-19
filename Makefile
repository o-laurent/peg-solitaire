all: solitaire

solitaire: structures.o readBoard.o data.o main.o
	gcc -o solitaire structures.o readBoard.o data.o main.o

structures.o: main.c
	gcc -Wall structures.c -o structures.o -c 

data.o: data.c
	gcc -Wall data.c -o data.o -c 

readBoard.o: readBoard.c
	gcc -Wall readBoard.c -o readBoard.o -c 

clean:
	rm -rf *.o