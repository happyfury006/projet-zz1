#include "IA.h"
#include "jeu.h"
#include <math.h>

#define PROFONDEUR 6

arbre generecoup(joueur j,grille plat){
    int prof = 0;
    arbre arb= malloc(sizeof(arbre));
    arb->plateau=plat;
    for(int i=0; i<4; i++)
    {
        if (j->piecerestantes[i][1]>0)
        {
            for(int j=0; j<4; j++)
            {
                for(int k=0; k<4; k++)
                {
                    if(valide(i, j, k, plat->grid))
                    {
                        grille platcopie=grillecopie(plat);
                        applique(platcopie,j->piecerestantes[i][0],j,k);
                        if (prof<PROFONDEUR)
                        {
                            prof+=1;
                            arbre sousarb = arb->fils[0];
                            sousarb->derniercoup->x = j;
                            sousarb->derniercoup->y = k;
                            sousarb->derniercoup->joueur = j->numJoueur;
                            sousarb->derniercoup->forme = j->piecerestantes[i][0];
                            sousarb=generecoup(abs(j-1),platcopie);
                        }
                        prof-=1;
                    }
                }
            }
        }
    }
    return arb;
}