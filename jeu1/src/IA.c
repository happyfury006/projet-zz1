#include "IA.h"
#include "jeu.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>


grille* grillecopie(grille* acopier) {
    grille* copie = (grille*)malloc(sizeof(grille));          //allocation de la copie
    for (int i = 0; i < 4; i++)                               //parcours de la grille
    {                                
        for (int j = 0; j < 4; j++)                             
        {
            if (acopier->grid[i][j] != NULL)                  //si la case n'est pas vide
            {
                copie->grid[i][j] = (piece*)malloc(sizeof(piece));      //on alloue la piece
                *(copie->grid[i][j]) = *(acopier->grid[i][j]);           //on copie la piece dans la copie
            } 
            else 
            {
                copie->grid[i][j] = NULL;
            }
        }
    }
    copie->valeur = acopier->valeur;                         //copie de la valeur
    return copie;
}


arbre* generecoup(joueur j,grille* plat,int profondeur){
    int index=0;
    arbre* arb= (arbre*)malloc(sizeof(arbre));
    arb->plateau=plat;
    for(int i=0; i<4; i++)
    {
        if (j.piecerestante[i][1]>0)
        {
            for(int j=0; j<4; j++)
            {
                for(int k=0; k<4; k++)
                {
                    if(valide(i, j.numJoueur, j, k, plat->grid))
                    {
                        grille platcopie=grillecopie(plat);
                        platcopie=ajoutpiece(platcopie,j.piecerestante[i][0],j,k);
                        if (index<profondeur)
                        {
                            index+=1;
                            arbre* sousarb = arb->fils[0];
                            sousarb->derniercoup.x = j;
                            sousarb->derniercoup.y = k;
                            sousarb->derniercoup.j = j.numJoueur;
                            sousarb->derniercoup.forme = j.piecerestante[i][0];
                            sousarb=generecoup(abs(j.numJoueur-1),platcopie);
                        }
                        prof-=1;
                    }
                }
            }
        }
    }
    return arb;
}


int minmax(arbre* noeud, int profondeur, int maximizingPlayer) {
    if (profondeur == 0)             //si c'est une feuille (de notre profondeur)
    {
        return evaluation(noeud->plateau);
    }

    if (maximizingPlayer)             //on maximise pour le joueur
    {
        int maxEval = INT_MIN;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) 
        {
            int eval = minmax(noeud->fils[i], profondeur - 1, 0);
            if (eval > maxEval) 
            {
                maxEval = eval;
            }
        }
        return maxEval;
    } 
    else                                //on minimise pour l'adversaire
    {
        int minEval = INT_MAX;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) 
        {
            int eval = minmax(noeud->fils[i], profondeur - 1, 1);
            if (eval < minEval) 
            {
                minEval = eval;
            }
        }
        return minEval;
    }
}


