#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "main.h"


int makePossibleMoves(state board[7][7], movementList* moveList) {
    //Generates the linked list which contains all the moves
    int i = 0;
    int j = 0;
    int k = 0;
    int nb = 0;
    movement move;
    for (i=0 ; i<7 ; i++) {
        for (j=0 ; j<7 ; j++) {
            if (board[i][j]==ball) {
                move.posix = i;
                move.posiy = j;
                for (k=0 ; k<4 ; k++) {
                    move.dir = k;
                    if (correctMove(board, &move)) {
                        consML(&move, moveList);
                        nb++;
                    }
                }
            }
        }
    }
    return nb;
}

int moveNb(state board[7][7]) {
    //Returns the number of possible moves
    int nb;
    movementList moveList;
    nb = makePossibleMoves(board, &moveList);
    return nb;
}

int moveFixed(state board[7][7], movementList** moveList, unsigned char x, unsigned char y) {
    //Returns the moves
    int nb = 0;
    int k = 0;
    movement move;
    if (board[x][y]==ball) {
        move.posix = x;
        move.posiy = y;
        for (k=0 ; k<4 ; k++) {
            move.dir = k;
            if (correctMove(board, &move)) {
                *moveList = consML(&move, *moveList);
                nb++;
            }
        }
    }
    move = (*moveList)->move;
    return nb;
}

void initBoard(state board[7][7]) {
    //Initialise the board to a French solitaire
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            if ((i%6==0 && j%6==0) || (i%6==0 && j==1) || (i==1 && j%6==0) || (i%6==0 && j==5) || (i==5 && j%6==0)) {
                board[i][j] = out;
            }
            else if (i==j && i==3) {
                board[i][j] = empty; 
            }
            else {
                board[i][j] = ball;
            }
        }
    }
}

int ballNb(state board[7][7]) {
    //Counts the number of balls on the board
    int count =0;
    for (int i=0; i<7; i++) {
        for (int j=0 ; j<7 ; j++) {
            if (board[i][j]==ball) {
                count++;
            }
        }
    }
    return count;
}

int correctMove(state board[7][7], movement* move) {
    int ok;
    //Check if the position is ball and if the next positions are empty
    int x = move->posix;
    int y = move->posiy;
    direction dir = move->dir;
    if (board[x][y]==ball){
        if ((dir==north) && (board[x-1][y]==ball) && (board[x-2][y]==empty)) {
            ok = 1;
        }
        else if ((dir==south) && (board[x+1][y]==ball) && (board[x+2][y]==empty)) {
            ok = 1;
        }
        else if ((dir==east) && (board[x][y+1]==ball) && (board[x][y+2]==empty)) {
            ok = 1;
        }
        else if ((dir==west) && (board[x][y-1]==ball) && (board[x][y-2]==empty)) {
            ok = 1;
        }
        else {
            ok = 0;
        }
    }
    else {
        ok = 0;
        printf("UNEXPECTED ERROR 1");
    }
    return ok;
}

int possibleMove(state board[7][7]) {
    //Returns 1 if one move can still be done
    int doable;
    if ((ballNb(board)>=2) && (moveNb(board)>=1)) {
        //ballNb for optimality (allows not to go through moveNb)
        doable = 1;
    }
    else {
        //If there is only one ball, one can not play anymore
        doable = 0;
    }
    return doable;
}   

void doMove(state board[7][7], movement* move) {
    //Makes the move
    //You must check that the move is correct before calling this function !
    int x = move->posix;
    int y = move->posiy;
    if (move->dir==north) {
        board[x][y] = empty;
        board[x-1][y] = empty;
        board[x-2][y] = ball;
    }
    else if (move->dir==south) {
        board[x][y] = empty;
        board[x+1][y] = empty;
        board[x+2][y] = ball;
    }
    else if (move->dir==east) {
        board[x][y] = empty;
        board[x][y+1] = empty;
        board[x][y+2] = ball;
    }
    else if (move->dir==west) {
        board[x][y] = empty;
        board[x][y-1] = empty;
        board[x][y-2] = ball;
    }
    else {
        printf("UNEXPECTED ERROR");
    }
}

void userMove(state board[7][7]) {
    //Allows the user to chose the movement he desires
    char dir;
    char line[1024];
    movement move;
    int status = 0; //True if a correct movement is recorded
    movementList* moveList = malloc(sizeof(movementList));
    while (!status) {
        //Print the board
        printBoard(board);
        printf("Entrez la coordonnée ");
        printf("\033[0;34m");
        printf("verticale ");
        printf("\033[0m");
        printf("de la balle à déplacer\n");
        fgets(line, 1024, stdin);
        sscanf(line, "%hhd", &(move.posix));

        printf("Entrez la coordonnée ");
        printf("\033[0;31m");
        printf("horizontale ");
        printf("\033[0m");
        printf("de la balle à déplacer\n");
        fgets(line, 1024, stdin);
        sscanf(line, "%hhd", &(move.posiy));
        printf("\n");

        int ok = 0;
        if (moveFixed(board, &moveList, move.posix, move.posiy)==1) {
            ok = 1;
            move = moveList->move;
            status = correctMove(board, &move);
        }
        else if (board[move.posix][move.posiy]==ball) {
            while(!ok && !status) {
                printf("Entrez la direction du mouvement (n, s, e, o) : \n");
                fgets(line, 1024, stdin);
                sscanf(line, "%c", &dir);
                if (dir=='n') {
                    ok++;
                    move.dir = north;
                }
                else if (dir=='s') {
                    ok++;
                    move.dir = south;
                }
                else if (dir=='e') {
                    ok++;
                    move.dir = east;
                }
                else if (dir=='o') {
                    ok++;
                    move.dir = west;
                }
                else {
                    ok =0;
                    printf("Erreur lors de l'entrée \n");
                }
            }
            status = correctMove(board, &move);
            printf("%d \n", status);
            if (status==0){
                printf("\033[1;31m"); //Red
                printf("Erreur utilisateur\n");
                printf("\033[0m");
                sleep(0.5);
                printf("Ce mouvement n'est pas possible. Veuillez en proposer un autre :\n");
                sleep(1.5);
            } 
        }
        else {
            printf("\033[1;31m"); //Red
            printf("Erreur utilisateur\n");
            printf("\033[0m");
            sleep(0.5);
            printf("Le mouvement proposé ne correspond pas à une bille.\nVeuillez en proposer un autre :\n");
            sleep(1.5);
        }
    }
    doMove(board, &move);
    
}

void printBoard(state board[7][7]) {
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
            if (j<7 && board[i][j]==ball && i!=7) {
                printf("\033[1m");
                printf("o ");
                printf("\033[0m");
            }
            else if (j<7 && board[i][j]==empty && i!=7) {
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

int userGame() {
    //Define 7x7 board and a counter
    trajectory uTrajectory;
    state board[7][7];
    int turn = 1;

    //Initialise the board
    initBoard(board);
    uTrajectory ;
    while (possibleMove(board)){
        printf("----------   Début du tour %d ----------\n", turn);
        userMove(board);
        turn++;
    }
    return ballNb(board);
}

int main(){ 
    unsigned char status;
    time_t secondsStart; 
    time_t secondsEnd; 
    char line[1024];
    int ballNumber;

    //intro
    printf("Bienvenue dans le Solitaire v1.0\n");
    printf("\n");

    //Chose the mode
    printf("Appuyez sur '0' pour les règles du jeu, '1' pour jouer ou '2' pour une résolution automatique :\n");
    fgets(line, 1024, stdin);
    sscanf(line, "%hhd", &status);

    //checking for input errors
    while (status!=1 && status!=2) {
        if (status==0){
            printf("Le solitaire est, comme son nom l’indique, un jeu où l’on n’a aucun adversaire.\nLe but est de déplacer des billes sur un plateau,de les ôter petit à petit selon une règle précise jusqu’à ce qu’il ne reste qu’une seule bille au centre.\nLe joueur va prendre une bille et sauter par dessus la seconde se trouvant à coté pour aller rejoindre le trou vide.\nLa bille qui aura été sautée est alors sortie du jeu.\nIl faut savoir qu’à chaque coup,le joueur ne peut prendre qu’une seule bille à la fois et que cette dernière est prise par une autre bille venant verticalement ou horizontalement à elle.\n\n");
	        printf("Appuyez sur '0' pour les règles du jeu, '1' pour jouer ou '2' pour une résolution automatique :\n");
	        fgets(line, 1024, stdin);
            sscanf(line, "%hhd", &status);//Tutorial 
	    }
	else {
        printf("Erreur lors de l'entrée. Veuillez réessayer;\n");
        printf("Appuyez sur '0' pour les règles du jeu, '1' pour jouer ou '2' pour une résolution automatique :\n");
        fgets(line, 1024, stdin);
        sscanf(line, "%hhd", &status);
    }}

    //game
    if (status==1) {
        time(&secondsStart); 
        ballNumber = userGame();
        time(&secondsEnd); 
        printf("Après %lf minutes, la partie s'est terminée avec %d billes sur le plateau. \n", ((double)secondsEnd-(double)secondsStart)/60, ballNumber);
        printf("Bravo !\n");
    }

    if (status==2) {
        -1; //autoresolve
        //show solution or not
    }

    printf("\n");
    printf("Développé par Anthony Aoun, Maria El Haddad, Olivier Laurent et Johhny Yammine dans le cadre du projet de IN103 : Algorithmique en C. \n\n");

    printf("\n");
    printf("Merci d'avoir joué. Au revoir ^~^\n");
    return 0;
}
