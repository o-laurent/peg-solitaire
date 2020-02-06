all: solitaire

solitaire: solitaire.o
	gcc -o solitaire solitaire.o

solitaire.o: main.c
	gcc -o solitaire.o -c main.c -Wall

clean:
	rm -rf *.o