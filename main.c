#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "main.h"

int makePossibleMoves(state **board, movementList* moveList) {
    //Generates the linked list which contains all the moves
    //and returns the number of moves that can be done
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
    movementList moveList; //To provide enough arguments (but not used)
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
                *moveList = consML(&move, *moveList); //Utilisation forcée de liste chaînée pour s'entraîner...
                nb++;
            }
        }
    }
    move = (*moveList)->move;
    return nb;
}

void initBoard(state **board) {
    //Initialises the board to a French solitaire
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            if ((i%6==0 && j%6==0) || (i%6==0 && j==1) || (i==1 && j%6==0) || (i%6==0 && j==5) || (i==5 && j%6==0)) {
                board[i][j] = out;
            }
            else if (i==j && i==3) {
                board[i][j-1] = empty; 
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
        printf("%d\n", board[x][y]);
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
        printf("%d\n", move->dir);
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
        printf("de la bille à déplacer\n");
        fgets(line, 1024, stdin);
        sscanf(line, "%hhd", &(move.posix));
        move.posix--; //1 is equivalent to the 0 of the array
        
        //if user doesn't want to quit
        if (move.posix != -2) {

            printf("Entrez la coordonnée ");
            printf("\033[0;31m");
            printf("horizontale ");
            printf("\033[0m");
            printf("de la bille à déplacer\n");
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

int userGame(int* pquit, trajectory** pTrajectory, state** board, int* turn) {
    //Initialising the board and the trajectory
    (*pTrajectory)->next = NULL;
    (*pTrajectory)->board = board;

    state** newBoard = malloc(sizeof(*newBoard) * 7);
    for (int i=0;i<7;i++) {
        newBoard[i] = malloc(sizeof(**newBoard)*7);
    }

    while (possibleMove(board) && (!(*pquit))){
        //If a mouvement is possible and user doesn't want to quit
        free(newBoard);
        newBoard = malloc(sizeof(*newBoard) * 7); //tmpBoard 
        for (int i=0;i<7;i++) {
            newBoard[i] = malloc(sizeof(**newBoard)*7);
        }
        copyBoard(board, newBoard);

        //printf("Valeur : %f", cost_f(newBoard));
        printf("----------   Début du tour %d ----------\n", *turn);
        userMove(newBoard, pquit); //modify tmpBoard 
        (*turn)++;

        board = malloc(sizeof(*board) * 7);
        for (int i=0;i<7;i++) {
            board[i] = malloc(sizeof(**board)*7);
        }
        copyBoard(newBoard, board); //copy board to tmpBoard

        *pTrajectory = consT(board, *pTrajectory); //update the trajectory
    }
    return ballNb((*pTrajectory)->board);
}

int main(){ 
    //Initialisation
    state **board = malloc(sizeof(*board) * 7);
    char status;

    //time vars
    time_t secondsStart; 
    time_t secondsEnd; 

    //to use sscanf (ask multiple questions to the user
    char line[1024];
    int quit = 0;
    int* pquit = &quit;

    //Defining the board's dimensions
    char lineNb = 0;
    char colNb = 0;
    int ballNumber = 0;

    //Check if there is a saved game to load 
    int savedGame = isThereASavedGame();
    time_t savedTime = 0;
    int turn = 1;

    //intro
    printf("Bienvenue dans le Solitaire v1.1\n");
    printf("\n");

    //Chose the mode
    do{
        printf("Appuyez sur '0' pour les règles du jeu et le tutoriel, \n-'1' pour jouer \n-'2' pour une résolution automatique.\nAppuyez à tout moment sur '-1' pour quitter la partie\n");
        fgets(line, 1024, stdin);
        sscanf(line, "%hhd", &status);
        printf("\n");
        if (status==0) { //Rules
            printRules();
            //Tutorial
            char tutorial;
            do {
                printf("Voulez-vous poursuivre sur le tutoriel ? (o/n)\n");
                fgets(line, 1024, stdin);
                sscanf(line, "%c", &tutorial);
                printf("\n\n");
            }
            while (tutorial!='o' && tutorial!='O' && tutorial!='N' && tutorial!='n' && tutorial!='\n');
            if (tutorial=='o'||tutorial=='o'||tutorial=='\n') {
                printf("TUTORIEL EN COURS DE REDACTION \n");
            }
        }
        else if (status!=1 && status!=2 && status!=-1) {
            printf("Erreur lors de l'entrée. Veuillez réessayer;\n");
            printf("Appuyez sur '0' pour les règles du jeu, \n-'1' pour jouer ou \n-'2' pour une résolution automatique.\nAppuyez à tout moment sur '-1' pour quitter la partie\n");
            fgets(line, 1024, stdin);
            sscanf(line, "%c", &status);
        }
    }
    while (status!=1 && status!=2 && status!=-1); //checking for input errors
    

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
            lineNb = 7;
            colNb = 7;
        }
        else {
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
                rmSavedGame();
            }
            else {
                rmTrajectory(); //Delete the saved Trajectory (last game that user doesn't want to resume)
                rmSavedGame();
            }
        }
        else {
            rmTrajectory(); //Delete the saved Trajectory (last game which was finished)
            rmSavedGame();
        }
        time(&secondsStart); 
        trajectory* pTrajectory = malloc(sizeof(trajectory));
        trajectory* ptrajOrigin = pTrajectory;
        //
        ballNumber = userGame(pquit, &pTrajectory, board, &turn);
        //
        time(&secondsEnd); 
        printBoardV(pTrajectory->board, 7, 7);
        if (*pquit!=1) {
            saveTrajectory(ptrajOrigin);
            printf("Après %.2lf minutes, la partie s'est terminée avec %d billes sur le plateau. \n", ((double)secondsEnd-(double)secondsStart+savedTime)/60, ballNumber);
            printf("\033[1;36mBravo !\033[0m\n"); //CHANGE COLOR
            printf("N'hésitez pas à aller récupérer les différentes étapes de la partie dans data/trajectory.txt avant de commencer la prochaine partie !\n");
            //history of the game
            //nb of games
            implementStats((double)secondsEnd-(double)secondsStart+savedTime);
            int x = readNumberOfGames();
            double y = totalPlayedTime();
            printf("%f, %lf, %f, %lf", y, y, y/60, y/60);
            printf("\n\n");
            printf("Historique de Jeu :\n");
            printf("Nombre de parties jouées: %d\n", x);
            printf("Temps total de jeu: %f minutes\n", y/60);
            rmSavedGame();
        }

        else {
            char save;
            //ask whether the user wants to save the game or not
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
                saveTrajectory(ptrajOrigin);
                printf("\n");
                printf("La partie a été sauvegardée !\n");
            }
        }
        free(board);
        freeT_P(pTrajectory);
    }

    else if (status==2) {
        board = readBoard("data/model.txt", &lineNb, &colNb);
        node* cNode = malloc(sizeof(node));
        trajectoryNode* pTrajectory = malloc(sizeof(trajectory));
        trajectoryNode* ptrajOrigin = pTrajectory;
        pTrajectory->cNode = cNode;
        pTrajectory->cNode->board = board;
        pTrajectory->cNode->childNb = 0;
        int boardNb = 0;
        int stop = 0;
        int nodeAlloc = 0;
        int boardAlloc = 0;
        int nodeFree = 0;
        int boardFree = 0;
        pTrajectory = autosolve(pTrajectory, &boardNb, &stop, &nodeAlloc, &nodeFree, &boardAlloc, &boardFree);

        printTrajectoryN(ptrajOrigin);
        printf("Nombre de solutions testées : %d\n", boardNb);
        printf("Nombre de noeuds alloués : %d\n", nodeAlloc);
        printf("Nombre de noeuds libérés : %d\n", nodeFree);
        printf("Nombre de boards alloués : %d\n", boardAlloc);
        printf("Nombre de boards libérés : %d\n", boardFree);
        //show solution or not
    }

    printf("\n");
    printf("Développé par Anthony Aoun, Maria El Haddad, Olivier Laurent et Johnny Yammine dans le cadre du projet de IN103 : Algorithmique en C. \n\n");

    printf("\n");
    printf("Merci d'avoir joué. Au revoir ^~^\n");

    return 0;
}