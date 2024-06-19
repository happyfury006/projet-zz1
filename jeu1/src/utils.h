#ifndef GARDIEN_UNIQUE_UTILS_H
#define GARDIEN_UNIQUE_UTILS_H

#include<stdio.h>

enum formes{        // faire le lien entre la forme et un entier
    cube = 0,
    cone = 1,
    cylindre = 2,
    sphere = 3
}forme;

typedef struct list {
    int value;          
    struct list * next;
} list;



// fichier d'entete classique ou l'on declare les types necessaires,            
// les fonctions implementees dans le fichier .c                                
// les declaration de variables globales externes   


#endif