#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "uiBoard.h"


//Printing functions
void printBoardV(state** board, char lineNb, char colNb) {
    //Prints the Board on the terminal
    printf("\n");
    for (int i=0; i<lineNb+1; i++) {
        if (i==0||i==lineNb) { //Up and Down Red number lines
            printf("  ");
            printf("\033[0;31m"); //Red
            for (int j=0 ; j<colNb ; j++) {
                printf("%d ", j+1);
            }
            printf("\033[0m");
            printf("\n");
        }
        for (int j=0; j<colNb+1 ; j++) {
            if (j<10) { //Only one digit : one space between the prints
                if ((j==0 || j==colNb) && i!=lineNb) { //Right and Left Blue number columns
                    printf("\033[0;34m"); //Blue
                    printf("%d ", i+1);
                    printf("\033[0m");
                }
                if (i<lineNb && j<colNb && board[i][j]==ball) {
                    printf("\033[1m");
                    printf("o ");
                    printf("\033[0m");
                }
                else if (i<lineNb && j<colNb && board[i][j]==empty) {
                    printf("\033[37;2m"); //Grey 
                    printf("x ");
                    printf("\033[0m");
                }
                else {
                    printf("  ");
                }
            }
            else if (j<100) { //Double space to tackle the fact that 10 takes to positions
                if ((j==0||j==colNb) && i!=lineNb) {
                    printf("\033[0;34m"); //Blue
                    printf("%d  ", i+1);
                    printf("\033[0m");
                }
                if (i<lineNb && j<colNb && board[i][j]==ball) {
                    printf("\033[1m");
                    printf("o  ");
                    printf("\033[0m");
                }
                else if (i<lineNb && j<colNb && board[i][j]==empty) {
                    printf("\033[37;2m"); //Grey 
                    printf("x  ");
                    printf("\033[0m");
                }
                else {
                    printf("  ");
                }
            }
            
        }
        printf("\n");
    }
    printf("\n");
}

void printTrajectory(trajectory* trajOrigin) {
    //Prints the whole trajectory on the terminal
    int turn = 1;
    do {
        printf("----------   Début du tour %d ----------\n", turn);
        printBoardV(trajOrigin->board, 7, 7);
        trajOrigin = trajOrigin->next;
        turn++;
        sleep(2);
    }
    while(trajOrigin!=NULL);
}

void printTrajectoryN(trajectoryNode* trajOrigin) {
    //Prints the whole trajectory on the terminal
    int turn = 1;
    printf("---------- Début de la trajectoire ----------\n");
    do {
        sleep(1.5);
        printf("----------   Début du tour %d ----------\n", turn);
        printBoardV(trajOrigin->cNode->board, 7, 7);
        trajOrigin->cNode = trajOrigin->cNode->child;
        turn++;
    }
    while(trajOrigin->cNode!=NULL);
    printf("---------- Fin de la trajectoire ----------\n");
}

//Saving functions
void rmTrajectory() {
    remove("data/trajectory.txt");
}

void saveTrajectory(trajectory* trajOrigin) {
    FILE* out;
    int turn = 0;
    out = fopen ("data/trajectory.txt", "wa");
    fprintf(out,"Début de la partie : \n\n");
    if (out == NULL) {
        printf("La sauvegarde a échoué. Le fichier spécifié pour la sauvegarde n'existe pas.\n");
    }
    do{
        fprintf(out, "----------   Début du tour %d ----------\n", turn);
        for (int i=0; i<7; i++) {
            for (int j=0; j<7; j++) {
                if (trajOrigin->board[i][j]==ball) {
                    fprintf(out, "o ");
                }
                else if (trajOrigin->board[i][j]==empty) {
                    fprintf(out, "x ");
                }
                else {
                    fprintf(out, "  ");
                }
            }
            fprintf(out, "\n");
        }
        trajOrigin = trajOrigin->next;
        turn++;
    }
    while(trajOrigin!=NULL);
    fclose(out);
};


//Reading function
state** readBoard (char* fileName, char* lineNb, char* colNb) {
    //reads the board depicted in fileName
    *lineNb = 0;
    *colNb = 0;
	FILE* fichier = fopen(fileName, "r");
	if (fichier==NULL) { //The model does not exist		
        printf("ERREUR lors de la lecture du fichier model.txt.\n");
        printf("En l'absence de model.txt, nous passons en mode 'Partie Standard'.\n");
        printf("Si vous souhaitez faire une partie personnalisée, veuillez ajouter un fichier model.txt dans le dossier data et relancer le jeu.\n");
		state** board = malloc(sizeof(*board)*(7));
        for (int i=0; i<7; i++) {
                board[i] = malloc(sizeof(**board)*(7));
        }
        initBoard(board);
        return board;	
	}
	else{	
		int s[123] = {0}; //tableau du nbr de caractères par lignes
		int l = 0;//numero de la ligne
		char c = fgetc(fichier);
		while (c!=EOF) {
            if (c!='\n') {
                s[l]++;
                c = fgetc(fichier);
            }
            else {
                (*lineNb)++;
                l++;//on descend d'une ligne qd on a '\n'
                c = fgetc(fichier);
                if (c==EOF) { //The last line is empty
                    l--;
                }
            }
		}
        

		fclose(fichier);	
		//trouvons le nbr max de caractère dans une ligne pour savoir la taille de la grille qu'on fera
		l = 0;	
		while (l<*lineNb) {
			if (s[l]>*colNb) {
				*colNb = s[l];
			}
			l++;
		}
        printf("Le nombre de lignes est %d et de colonnes : %d", *lineNb, *colNb);
        state** board = malloc(sizeof(*board)*(*lineNb));
        for (int i=0; i<*lineNb; i++) {
                board[i] = malloc(sizeof(**board)*(*colNb));
        }
		l = 0; 
        int i = 0;
		FILE* fichier = fopen("data/model.txt", "r");
		while (l<*lineNb) {
			i = 0;
            c = fgetc(fichier);
			while (i<s[l]) {
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
                    printf("Erreur dans le fichier data/model.txt.\n Veuillez utiliser uniquement 'x' et '.'.\n");
                    board[l][i] = empty; //If there is a wrong caracter, say it's empty
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