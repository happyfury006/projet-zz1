#ifndef GARDIEN_UNIQUE_UTILS_H
#define GARDIEN_UNIQUE_UTILS_H

#include<stdio.h>


enum formes{        // faire le lien entre la forme et un entier
    cube = 0,
    cone = 1,
    cylindre = 2,
    sphere = 3
};

// extern enum formes forme;
typedef struct piece {      //structure d'une pièce
    int formes;             //forme de la pièce
    int joueur;             //0=>joueur1=>piece blanche | 1=>joueur2=>piece noir
} piece;

typedef struct list {
    piece* piece;          
    struct list * next;
} list;


int estdanslaliste(piece* piece,list * listdejaparcouru);
void ajoutliste(piece* piece,list * listdejaparcouru);
// fichier d'entete classique ou l'on declare les types necessaires,            
// les fonctions implementees dans le fichier .c                                
// les declaration de variables globales externes   


#endif