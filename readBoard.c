#include <stdio.h>
#include <stdlib.h>

typedef enum state {ball, empty, out} state;

void printBoardV(state **board, char lineNb, char colNb) {
    printf("\n");
    for (int i=0; i<lineNb+1 ; i++) {
        if (i==0 || i==lineNb) {
            printf("  ");
            printf("\033[0;31m"); //Red
            for (int j=0 ; j<colNb ; j++) {
                printf("%d ", j);
            }
            printf("\033[0m");
            printf("\n");
        }
        for (int j=0; j<colNb+1 ; j++) {
            if (j<10) {
                if ((j==0 || j==colNb) && i!=lineNb) {
                    printf("\033[0;34m"); //Blue
                    printf("%d ", i);
                    printf("\033[0m");
                }
                if (i<lineNb && j<colNb && board[i][j]==ball) {
                    printf("\033[1m");
                    printf("o ");
                    printf("\033[0m");
                }
                else if (i<lineNb && j<colNb && board[i][j]==empty) {
                    printf("\033[37;2m"); //Grey 
                    printf("X ");
                    printf("\033[0m");
                }
                else {
                    printf("  ");
                }
            }
            else if (j<100) {
                if ((j==0 || j==colNb) && i!=lineNb) {
                    printf("\033[0;34m"); //Blue
                    printf("%d  ", i);
                    printf("\033[0m");
                }
                if (i<lineNb && j<colNb && board[i][j]==ball) {
                    printf("\033[1m");
                    printf("o  ");
                    printf("\033[0m");
                }
                else if (i<lineNb && j<colNb && board[i][j]==empty) {
                    printf("\033[37;2m"); //Grey 
                    printf("X  ");
                    printf("\033[0m");
                }
                else {
                    printf("   ");
                }
            }
            
        }
        printf("\n");
    }
    printf("\n");
}

void printBoard(state **board) {
    printf("\n");
    for (int i=0 ; i<8 ; i++) {
        if (i==0 || i==7) {
            printf("  ");
            printf("\033[0;31m"); //Red
            for (int j=0 ; j<7 ; j++) {
                printf("%d ", j);
            }
            printf("\033[0m");
            printf("\n");
        }
        for (int j=0 ; j<8 ; j++) {
            if ((j==0 || j==7) && i!=7) {
                printf("\033[0;34m"); //Blue
                printf("%d ", i);
                printf("\033[0m");
            }
            if (i<7 && j<7 && board[i][j]==ball) {
                printf("\033[1m");
                printf("o ");
                printf("\033[0m");
            }
            else if (i<7 && j<7 && board[i][j]==empty) {
                printf("\033[37;2m"); //Grey 
                printf("X ");
                printf("\033[0m");
            }
            else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


state** readBoard (char* fileName, char* lineNb, char* colNb) { //je pense que l'erreur est dans l'arg
	FILE* fichier = fopen(fileName, "r");
	if (fichier==NULL){		
        printf("ERREUR lors de la lecture du fichier model.\n");
        printf("En l'absence de model.txt, nous passons en mode 'Partie Standard'.\n");
        printf("Si vous souahiter faire une partie personnalisée, veuillez ajouter un fichier model.txt dans le fichier data.\n");
		state** board = malloc(sizeof(*board) * (*lineNb));
        for (int i=0; i<*lineNb; i++) {
                board[i] = malloc(sizeof(**board)*(*colNb));
        }
        //board = initBoard(board)
        return board;	
	}
	else{	
		int s[123] = {0}; //tableau du nbr de caractères par lignes
		int l = 0;//numero de la ligne
		char c = fgetc(fichier);
        printf("%c\n",c);
		while(c!=EOF){
            if (c!='\n') {
                s[l]++;
                c = fgetc(fichier);
            }
            else if (c=='\n') {
                (*lineNb)++;
                l++;//on descend d'une ligne qd on a '\0'
                c = fgetc(fichier);
                if (c==EOF) { //The last line is empty
                    l--;
                }
            }
            else {
                c = fgetc(fichier);
            }
            printf("%c\n", c);
		}
        

		fclose(fichier);	
		//trouvons le nbr max de caractère dans une ligne pour savoir la taille de la grille qu' on fera
		l = 0;	
		while (l<*lineNb){
			if (s[l]>*colNb){
				(*colNb) = s[l];
			}
			l++;
		}
        state** board = malloc(sizeof(*board) * (*lineNb));
        for (int i=0; i<*lineNb; i++) {
                board[i] = malloc(sizeof(**board)*(*colNb));
        }
		l = 0; 
        int i = 0;
		FILE* fichier = fopen("data/model.txt", "r");
		while (l<*lineNb){
			i = 0;
            c = fgetc(fichier);
			while(i<s[l]){
                if (c==' ') {
                    board[l][i] = out;
                }
				else if (c=='x') {
					board[l][i] = ball;
				}
				else if (c=='.') {
					board[l][i] = empty;
				}
                else {
                    printf("ERREUR");
                }
				i++;
                c = fgetc(fichier);
			}
			while (i<*colNb) {
				board[l][i] = out;
				i++;
			}
            l++;
		}
        return board;
    }
}

int main() {
    char lineNb = 0;
    char colNb = 0;
    state** board = readBoard("data/model.txt", &lineNb, &colNb);
    //printBoard(board);
    printBoardV(board, lineNb, colNb);
    return 0;
}