#ifndef GARDIEN_UNIQUE_IA_H
#define GARDIEN_UNIQUE_IA_H

#include <stdio.h>
#include "jeu.h"
#define N 4*16

// fichier d'entete classique ou l'on declare les types necessaires,            
// les fonctions implementees dans le fichier .c                                
// les declaration de variables globales externes   

typedef struct arbre{       //structure de l'arbre
    grille* plateau;          //noeud : plateau actualisé
    arbre fils[N];             //enfants : un tableau de sous arbres
} arbre;


#endif