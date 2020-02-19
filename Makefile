all: solitaire

solitaire: data.o main.o
	gcc -o solitaire data.o main.o

main.o: main.c
	gcc -Wall main.c -o main.o -c 

data.o: data.c
	gcc -Wall data.c -o data.o -c 

clean:
	rm -rf *.o