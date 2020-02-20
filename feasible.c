#include "feasible.h"


int ruleOftheThree(state** board) {
    //Returns 0 if the board is not feasible according to the ruleOfTheThree

    /*Use do while
    variable stop : quand stop = 1, on arrête
    i
    j
    endBoard = board avec une bille seulement en (i,j)
    do {
        int square3b[3][3] carré 3*3 qui correspond au board
        int square2b[2][2] carré 2*2 qui correspond au board
        int square3e[3][3] carré 3*3 qui correspond au endboard
        int square2e[2][2] carré 2*2 qui correspond au endboard

        square3b = board2Square3(board)
        square3b = useEquiv(square3b)
        square2b = square32Square2(square3b)

        square3e = board2Square3(endBoard)
        square3e = useEquiv(square3e)
        square2e = square32Square2(square3e)
        stop = squareEqual(square2e,square2b)
    }

    while (!stop and conditions sur i j : on a tout testé)*/
    return 1;
}

/*
int** board2Square3(state** board) {
    //Transforms the board to a 3*3 square with the usual transmations 
    Au dessus de cube on fait descendre positivement (la case (i,j) perd 1, celle du dessous perd 1 et celle d'encore en dessous gagne 1)
    A gauche du cube on fait droite positivement (la case (i,j) perd 1, celle de droite perd 1 et celle d'encore de droite gagne 1)
    A droite du cube on fait gauche positivement (la case (i,j) perd 1, celle de gauche perd 1 et celle d'encore de gauche gagne 1)
    En dessous du cube on fait monter positivement (la case (i,j) perd 1, celle du dessus perd 1 et celle d'encore en dessus gagne 1)
}

int** useEquiv(int square2[2][2]) {
    // tu appliques d'abord les les 2 dernières règles 
    Puis ensuite les premières dans les 6 directions (3verticales, 3 horizontales) avec des if 

}

int** square32Square2(int square3[3][3]) {
    // Juste des sommes (regarde  sur le site)

}

int squareEqual(int square1[2][2], int square2[2][2]) {
    //returns 1 if all coeffs are the same
}
*/