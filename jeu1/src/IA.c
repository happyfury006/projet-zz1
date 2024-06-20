#include "IA.h"
#include "jeu.h"
#include <math.h>
#include <stdlib.h>

#define PROFONDEUR 6

grille grillecopie(grille acopier){
    grille* copie = (grille*)malloc(sizeof(grille));
    copie->grid=acopier->grid;
    copie->value=acopier->value;
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