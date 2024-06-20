#include "IA.h"
#include "jeu.h"
#include <math.h>
#include <stdlib.h>


grille* grillecopie(grille* acopier) {
    grille* copie = (grille*)malloc(sizeof(grille));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (acopier->grid[i][j] != NULL) {
                copie->grid[i][j] = (piece*)malloc(sizeof(piece));
                *(copie->grid[i][j]) = *(acopier->grid[i][j]);
            } else {
                copie->grid[i][j] = NULL;
            }
        }
    }
    copie->valeur = acopier->valeur;
    return copie;
}

arbre generecoup(joueur joueur,grille plat){
    int prof = 0;
    arbre* arb= malloc(sizeof(arbre));
    arb->plateau=plat;
    arb->plateau->valeur=evaluation(plat);
    for(int i=0; i<4; i++)
    {
        if (joueur.piecerestante[i][1]>0)
        {
            for(int j=0; j<4; j++)
            {
                for(int k=0; k<4; k++)
                {
                    if(valide(i, joueur.numJoueur, j, k, plat->grid))
                    {
                        grille platcopie=grillecopie(plat);
                        platcopie=ajoutpiece(platcopie,joueur.piecerestante[i][0],j,k);
                        if (prof<PROFONDEUR)
                        {
                            prof+=1;
                            arbre* sousarb = arb->fils[0];
                            sousarb->derniercoup.x = j;
                            sousarb->derniercoup.y = k;
                            sousarb->derniercoup.joueur = joueur.numJoueur;
                            sousarb->derniercoup.forme = joueur.piecerestante[i][0];
                            sousarb=generecoup(abs(joueur.numJoueur-1),platcopie);
                        }
                        prof-=1;
                    }
                }
            }
        }
    }
    return arb;
}


int minimax(arbre* noeud, int profondeur, int maximizingPlayer) {
    if (profondeur == 0) 
    {
        return evaluer_plateau(noeud->plateau);
    }

    if (maximizingPlayer) 
    {
        int maxEval = INT_MIN;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) 
        {
            int eval = minimax(noeud->fils[i], profondeur - 1, 0);
            if (eval > maxEval) 
            {
                maxEval = eval;
            }
        }
        return maxEval;
    } 
    else 
    {
        int minEval = INT_MAX;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) 
        {
            int eval = minimax(noeud->fils[i], profondeur - 1, 1);
            if (eval < minEval) 
            {
                minEval = eval;
            }
        }
        return minEval;
    }
}


coups trouver_meilleur_coup(arbre* racine, int profondeur) {
    int meilleur_valeur = INT_MIN;
    coups meilleur_coup;
    for (int i = 0; i < N && racine->fils[i] != NULL; i++) 
    {
        int valeur = minimax(racine->fils[i], profondeur - 1, 0);
        if (valeur > meilleur_valeur) 
        {
            meilleur_valeur = valeur;
            meilleur_coup = racine->fils[i]->derniercoup;
        }
    }
    return meilleur_coup;
}