#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "utils.h"



carte* creation_carte(int carte_construction)
{
    carte* carte1 = malloc(sizeof(carte));
    if (carte1 != NULL)
    {
        carte1->type=carte_construction;
        carte1->nbr_points=0;
        carte1->selected=0;
        carte1->posee=0;
        carte1->texture=NULL;
    }
    return carte1;
}

tab_carte_construction creation_tab_carte_construction()
{
    tab_carte_construction tab;
    for (int i = 0; i < NB_CONSTRUCTION+2; i++)
    {
        switch (i)
        {
        case 2:
            tab.tab_carte_construction[i]=creation_carte(2);
            tab.tab_carte_construction[i]->nbr_points=1;
            break;
        case 3:
            tab.tab_carte_construction[i]=creation_carte(3);
            tab.tab_carte_construction[i]->nbr_points=2;
            break;
        case 4:
            tab.tab_carte_construction[i]=creation_carte(4);
            tab.tab_carte_construction[i]->nbr_points=3;
            break;
        case 5://Face B de la carte ROUTE
            tab.tab_carte_construction[i]=creation_carte(5);
            tab.tab_carte_construction[i]->nbr_points=1;
            break;
        case 6://Face B de la carte CHEVALIER
            tab.tab_carte_construction[i]=creation_carte(6);
            tab.tab_carte_construction[i]->nbr_points=1;
            break;
        default:
        tab.tab_carte_construction[i]=creation_carte(i);
            break;
        }
        
    }
    return tab;
}

int randomiser(int N) 
{
    
    return rand() % N;
}

int nbr_carte_liste(int liste[], int N)
{
    int compteur=0;
    for (int i=0; i<N; i++)
    {
        compteur+=liste[i];
    }
    return compteur;
}


unsigned long hash(int echange_pioche[5], int construction, int carte_donnee_marche[5], int carte_recu_marche[5]) {
    unsigned long hash = 5381;
    int i;

    // Hash the echange_pioche array
    for (i = 0; i < 5; i++) {
        hash = ((hash << 5) + hash) + echange_pioche[i]; // hash * 33 + echange_pioche[i]
    }

    // Hash the construction integer
    hash = ((hash << 5) + hash) + construction;

    // Hash the carte_donnee_marche array
    for (i = 0; i < 5; i++) {
        hash = ((hash << 5) + hash) + carte_donnee_marche[i]; // hash * 33 + carte_donnee_marche[i]
    }

    // Hash the carte_recu_marche array
    for (i = 0; i < 5; i++) {
        hash = ((hash << 5) + hash) + carte_recu_marche[i]; // hash * 33 + carte_recu_marche[i]
    }

    return hash;
}

