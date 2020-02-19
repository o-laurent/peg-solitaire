#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "main.h"

int makePossibleMoves(state **board, movementList* moveList) {
    //Generates the linked list which contains all the moves
    int i = 0;
    int j = 0;
    int k = 0;
    int nb = 0;
    movement move;
    for (i=0; i<7; i++) {
        for (j=0; j<7; j++) {
            if (board[i][j]==ball) {
                move.posix = i;
                move.posiy = j;
                for (k=0; k<4; k++) {
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

int moveNb(state **board) {
    //Returns the number of possible moves
    int nb;
    movementList moveList;
    nb = makePossibleMoves(board, &moveList);
    return nb;
}

int moveFixed(state **board, movementList** moveList, unsigned char x, unsigned char y) {
    //Returns the moves
    int nb = 0;
    int k = 0;
    movement move;
    if (board[x][y]==ball) {
        move.posix = x;
        move.posiy = y;
        for (k=0; k<4; k++) {
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

void initBoard(state **board) {
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

int ballNb(state **board) {
    //Counts the number of balls on the board
    int count =0;
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            if (board[i][j]==ball) {
                count++;
            }
        }
    }
    return count;
}

int correctMove(state **board, movement* move) {
    int ok;
    //Check if the position is ball and if the next positions are empty
    int x = move->posix;
    int y = move->posiy;
    direction dir = move->dir;
    if (board[x][y]==ball){
        if ((dir==north) && x!=0 && x!=1 && (board[x-1][y]==ball) && (board[x-2][y]==empty)) {
            ok = 1;
        }
        else if ((dir==south) && x!=5 && x!=6 && (board[x+1][y]==ball) && (board[x+2][y]==empty)) {
            ok = 1;
        }
        else if ((dir==east) && y!=5 && y!=6 && (board[x][y+1]==ball) && (board[x][y+2]==empty)) {
            ok = 1;
        }
        else if ((dir==west) && y!=0 && y!=1 && (board[x][y-1]==ball) && (board[x][y-2]==empty)) {
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

int possibleMove(state **board) {
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

void doMove(state **board, movement* move) {
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

void userMove(state **board, int* pquit) {
    //Allows the user to chose the movement he desires
    char dir;
    char line[1024];
    movement move;
    int goodMove = 0; //True if a correct movement is recorded
    movementList* moveList = malloc(sizeof(movementList));
    while (!goodMove) {
        //Print the board
        printBoardV(board, 7, 7);    
        printf("Entrez la coordonnée ");
        printf("\033[0;34m");
        printf("verticale ");
        printf("\033[0m");
        printf("de la balle à déplacer\n");
        fgets(line, 1024, stdin);
        sscanf(line, "%hhd", &(move.posix));
        move.posix--;
        
        //if user doesn't want to quit
        if (move.posix != -2) {

            printf("Entrez la coordonnée ");
            printf("\033[0;31m");
            printf("horizontale ");
            printf("\033[0m");
            printf("de la balle à déplacer\n");
            fgets(line, 1024, stdin);
            sscanf(line, "%hhd", &(move.posiy));
            move.posiy--;
            //if user doesn't want to quit
            if (move.posiy != -2) {
                printf("\n");

                int ok = 0;
                if (moveFixed(board, &moveList, move.posix, move.posiy)==1) {
                    ok = 1;
                    move = moveList->move;
                    goodMove = correctMove(board, &move);
                }
                else if (board[move.posix][move.posiy]==ball) {
                    while(!ok && !goodMove) {
                        printf("Entrez la direction du mouvement (n, s, e, o) : \n");
                        fgets(line, 1024, stdin);
                        sscanf(line, "%c", &dir);

                        //if user doesn't want to quit
                        if (dir != -1) {

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
                        
                            goodMove = correctMove(board, &move);
                            printf("%d \n", goodMove);
                            if (goodMove==0){
                                printf("\033[1;31m"); //Red
                                printf("Erreur utilisateur\n");
                                printf("\033[0m");
                                sleep(0.5);
                                printf("Ce mouvement n'est pas possible. Veuillez en proposer un autre :\n");
                                sleep(1.5);
                            } 
                        }  
                        else if (dir == -1) {
                            *pquit = 1;
                            goodMove = 1;
                        }
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
            else if (move.posiy == -2) {
                *pquit = 1;
                goodMove = 1;
            }
        }
        else if (move.posix == -2) {
            *pquit = 1;
            goodMove = 1;
        }
    }
    if (*pquit==0) {
        doMove(board, &move);
    }
}

void printBoard(state **board) {
    printf("\n");
    for (int i=0 ; i<8 ; i++) {
        if (i==0 || i==7) {
            printf("  ");
            printf("\033[0;31m"); //Red
            for (int j=0 ; j<7 ; j++) {
                printf("%d ", j+1);
            }
            printf("\033[0m");
            printf("\n");
        }
        for (int j=0 ; j<8 ; j++) {
            if ((j==0 || j==7) && i!=7) {
                printf("\033[0;34m"); //Blue
                printf("%d ", i+1);
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

int userGame(int* pquit, trajectory** pTrajectory, state** board, int* turn ) {
    //Initialising the board and the trajectory
    (*pTrajectory)->next = NULL;
    (*pTrajectory)->board = board;

    state** newBoard = malloc(sizeof(*newBoard) * 7);
    for (int i=0;i<7;i++) {
        newBoard[i] = malloc(sizeof(**newBoard)*7);
    }

    while (possibleMove(board) && (!(*pquit))){
        free(newBoard);
        newBoard = malloc(sizeof(*newBoard) * 7);
        for (int i=0;i<7;i++) {
            newBoard[i] = malloc(sizeof(**newBoard)*7);
        }
        copyBoard(board, newBoard);

        //printf("Valeur : %f", cost_f(newBoard));
        printf("----------   Début du tour %d ----------\n", *turn);
        userMove(newBoard, pquit);
        (*turn)++;

        board = malloc(sizeof(*board) * 7);
        for (int i=0;i<7;i++) {
            board[i] = malloc(sizeof(**board)*7);
        }
        copyBoard(newBoard, board);

        *pTrajectory = consT(board, *pTrajectory);
    }
    return ballNb((*pTrajectory)->board);
}

int main(){ 
    state **board = malloc(sizeof(*board) * 7);
    char status;
    time_t secondsStart; 
    time_t secondsEnd; 
    char line[1024];
    int ballNumber = 36;
    int quit = 0;
    int* pquit = &quit;

    //Check if there is a saved game to load 
    int savedGame = isThereASavedGame();
    time_t savedTime = 0;
    int turn = 1;

    //intro
    printf("Bienvenue dans le Solitaire v1.0\n");
    printf("\n");

    //Chose the mode
    printf("Appuyez sur '0' pour les règles du jeu, '1' pour jouer ou '2' pour une résolution automatique.\nAppuyez à tout moment sur '-1' pour quitter la partie :\n");
    fgets(line, 1024, stdin);
    sscanf(line, "%hhd", &status);

    //checking for input errors
    while (status!=1 && status!=2 && status!=-1) {
        if (status==0){
            printf("Le solitaire est, comme son nom l’indique, un jeu où l’on n’a aucun adversaire.\n"
            "Le but est de déplacer des billes sur un plateau, de les ôter petit à petit selon une règle précise "
            "jusqu’à ce qu’il ne reste qu’une seule bille au centre.\nLe joueur va prendre une bille et sauter par "
            "dessus la seconde se trouvant à coté pour aller rejoindre le trou vide.\nLa bille qui aura été sautée est alors sortie du jeu.\n"
            "Il faut savoir qu’à chaque coup, le joueur ne peut prendre qu’une seule bille à la fois et que cette dernière est prise par une autre "
            "bille venant verticalement ou horizontalement à elle.\n\n");
	        printf("Appuyez sur '0' pour les règles du jeu, '1' pour jouer ou '2' pour une résolution automatique.\nAppuyez à tout moment sur '-1' pour quitter la partie :\n");
	        fgets(line, 1024, stdin);
            sscanf(line, "%hhd", &status);//Tutorial 
	    }
        else {
            printf("Erreur lors de l'entrée. Veuillez réessayer;\n");
            printf("Appuyez sur '0' pour les règles du jeu, '1' pour jouer ou '2' pour une résolution automatique.\nAppuyez à tout moment sur '-1' pour quitter la partie :\n");
            fgets(line, 1024, stdin);
            sscanf(line, "%hhd", &status);
        }}

    //game
    if (status==1) {
        //Allocating the board
        state **board = malloc(sizeof(*board) * 7);  //Table which will contain the first configuration
        long long int returned[2];
        for (int i=0;i<7;i++) {
            board[i] = malloc(sizeof(**board)*7);
        }
        //Personalized game ?
        char perso;
        do {
            printf("Voulez-vous utiliser un modèle personnalisé ? (o/n)\n");
            fgets(line, 1024, stdin);
            sscanf(line, "%c", &perso);
        }
        while (perso!='o' && perso!='O' && perso!='N' && perso!='n' && perso!='\n');
        if (perso=='N' || perso=='n' || perso=='\n') {
            initBoard(board);
        }
        else {
            char lineNb = 0;
            char colNb = 0;
            board = readBoard("data/model.txt", &lineNb, &colNb);
        }

        //Load saved game ?
        if (savedGame) { //ask whether the user wants to load game or not
            char resume; //'o' if the user wants to resume the game
            printf("\n");
            printf("Voulez-vous continuer la partie précédente ? (o/n)\n");
            fgets(line, 1024, stdin);
            sscanf(line, "%c", &resume);
            while (resume!='o' && resume!='O' && resume!='N' && resume!='n' && resume!='\n') {
                printf("\n");
                printf("Erreur lors de l'entrée. Veuillez réessayer\n");
                printf("Voulez-vous continuer la partie précédente ? (o/n)\n");
                fgets(line, 1024, stdin);
                sscanf(line, "%c", &resume);
            }
            if (resume=='o'||resume=='o'||resume=='\n') {
                loadGame(board, returned);
                turn = returned[0];
                savedTime = (double)returned[1];
                remove("data/save.txt");
            }
        }
        time(&secondsStart); 
        trajectory* pTrajectory = malloc(sizeof(trajectory));
        //
        ballNumber = userGame(pquit, &pTrajectory, board, &turn);
        //
        time(&secondsEnd); 
        printBoardV(pTrajectory->board, 7, 7);
        if (*pquit!=1) {
            printf("Après %.2lf minutes, la partie s'est terminée avec %d billes sur le plateau. \n", ((double)secondsEnd-(double)secondsStart+savedTime)/60, ballNumber);
            printf("Bravo !\n");
            //history of the game
            //nb of games
            implementStats((double)secondsEnd-(double)secondsStart+savedTime);
            int x = readNumberOfGames();
            double y = totalPlayingTime();
            printf("\n");
            printf("Historique de Jeu \n");
            printf("Nombre de parties jouées: %d\n", x);
            printf("Temps total de jeu: %lf minutes\n", (y+(double)secondsEnd-(double)secondsStart)/60);
        }
        else {
            char save;
            //ask the user if he wants to save game
            printf("\n");
            printf("Voulez-vous sauvegarder la partie ? (o/n)\n");
            fgets(line, 1024, stdin);
            sscanf(line, "%c", &save);
            while (save!='o' && save!='n') {
                printf("\n");
                printf("Erreur lors de l'entrée. Veuillez réessayer;\n");
                printf("Voulez-vous sauvegarder la partie ? (o/n)\n");
                fgets(line, 1024, stdin);
                sscanf(line, "%c", &save);
            }
            if (save=='o') {
                saveGame(pTrajectory->board, turn, (double)secondsEnd-(double)secondsStart+savedTime);
                printf("\n");
                printf("La partie a été sauvegardée !\n");
            }
        }
    }

    if (status==2) {
        -1; //autosolve
        //show solution or not
    }

    printf("\n");
    printf("Développé par Anthony Aoun, Maria El Haddad, Olivier Laurent et Johhny Yammine dans le cadre du projet de IN103 : Algorithmique en C. \n\n");

    printf("\n");
    printf("Merci d'avoir joué. Au revoir ^~^\n");

    return 0;
}