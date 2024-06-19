#ifndef GARDIEN_UNIQUE_JEU_H
#define GARDIEN_UNIQUE_JEU_H

#include<stdio.h>

// fichier d'entete classique ou l'on declare les types necessaires,            
// les fonctions implementees dans le fichier .c                                
// les declaration de variables globales externes   

enum forme{        // faire le lien entre la forme et un entier
    cube = 0,
    cone = 1,
    cylindre = 2,
    sphere = 3
}forme;


typedef struct piece {      //structure d'une pièce
    enum forme;             //forme de la pièce
    int joueur;             //0=>joueur1=>piece blanche | 1=>joueur2=>piece noir
    int x;                  //position en x de la pièce sur le plateau
    int y;                  //position en y de la pièce sur le plateau
} piece;


typedef struct list {
    int value;          
    struct list * next;
} list;


typedef struct joueur {
    int numJoueur;          //0=>joueur1=>piece blanche | 1=>joueur2=>piece noir
    int ia;                 //0=>joueur humain | >0 profondeur de l'arbre parcourue
    int compteurCylindre;   //nbr de cylindre restant
    int compteurCarre;
    int compteurCone;
    int compteurSphère;
} joueur;


#endif