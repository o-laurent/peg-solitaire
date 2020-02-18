#ifndef AUTOSOLVE_C_
#define AUTOSOLVE_C_
#include <stdio.h>
#include <stdlib.h>
#include "autosolve.h"
#include "structures.h"
#include "main.h"
#endif

float cost_f(state** board){
    float cost = 0;
    for(int i=0; i<7;i++){
        for(int j=0; j<7;j++){
            if(board[i][j]==ball){
                for(int k=i;k<7;k++){
                    for(int q=j; q<7; q++){
                        if (board[k][q]==ball) {
                            cost = cost+(k-i)*(k-i)+(q-j)*(q-j);
                        }
                    }
                } 
            }
        }
    }
    return cost;
}

/*tant que non stop 
    on regarde si il y a des mouvements possibles 
        On construit la lignée 
            On trie la lignée 
                On choisit les deux meilleurs et on supprime les autres 
                    si stop != 0 on arrête
                    sinon on réitère le raisonnement 
*/

/*stop = 0;
trajectory* autosolve(trajectory* pTrajectory) {
    if (stop) {
        return pTrajectory;
    }
    else {
        movement move;
        int i;
        int j;
        for (i=0 ; i<7 ; i++) {
            for (j=0 ; j<7 ; j++) {
                if (pTrajectory->board[i][j]==ball) {
                    move.posix = i;
                    move.posiy = j;
                    for (k=0 ; k<4 ; k++) {
                        move.dir = k;
                        if (correctMove(pTrajectory->board, &move)) {
                            doMove(move, pTrajcetory->board) Plutôt le next en fait
                            On calcule le coût 
                            On met tout ça dans un noeud frère et ainsi de suite
                            
                        }
                    }
                }
            }
        }
        on trie les fils qu'on a obtenu 
        on sélectionne les 2 meilleurs 
        on applique autosolve sur les 2 trajectoires qui correspondent au meilleur 
        Il faut que les 2 trajectoires soient différentes : peut-être un problème de mémoire ici 
    }
}*/

/*stop = False
#Mouvement
def mouvement(b):
    global a,stop
    if stop:
        return 0
    else :
        for k in range (12, 68+1):
            if billes[b][k] == 1 and not stop:                                                       #doit être une bille
                for i in range (12,68+1):
                    if billes[b][i]==1 :
                        if abcisse[i]==abcisse[k]:
                            if ordonnee[i]+1==ordonnee[k]:
                                if billes[b][i-9] == 0 and abcisse[i-9]==abcisse[i]:
                                    newbilles(a,b)
                                    a += 1                                                           #on incrémente le nbr de mvt
                                    billes[a][k]=0
                                    billes[a][i]=0
                                    billes[a][i-9]=1
                                    trajet.append(a)
                                    mouvement(a)

                                if billes[b][i+18]==0 and abcisse[i+18]==abcisse[i]:
                                    newbilles(a,b)
                                    a += 1
                                    billes[a][k]=0
                                    billes[a][i]=0
                                    billes[a][i+18]=1
                                    trajet.append(a)
                                    mouvement(a)

                        if ordonnee[i]==ordonnee[k]:
                            if abcisse[i]+1==abcisse[k]:
                                if billes[b][i-1] == 0 and ordonnee[i-1]==ordonnee[i]:
                                    newbilles(a,b)
                                    a += 1
                                    billes[a][k]=0
                                    billes[a][i]=0
                                    billes[a][i-1]=1
                                    trajet.append(a)
                                    mouvement(a)

                                if billes[b][i+2]==0 and ordonnee[i+2]==ordonnee[i]:
                                    newbilles(a,b)
                                    a += 1
                                    billes[a][k]=0
                                    billes[a][i]=0
                                    billes[a][i+2]=1
                                    trajet.append(a)
                                    mouvement(a)
    if a%100000 == 0:
        fichier1 = open("Chiffres.txt", "w")
        fichier1.write(str(trajet[-1]))
        fichier1.write("\n")
        fichier1.close
    if billes[trajet[-1]].count(1) <= y :
        stop = True
    else:
        del billes[trajet[-1]],trajet[-1]
*/