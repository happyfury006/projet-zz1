#ifndef GARDIEN_UNIQUE_JEU_H
#define GARDIEN_UNIQUE_JEU_H

#include<stdio.h>

// fichier d'entete classique ou l'on declare les types necessaires,            
// les fonctions implementees dans le fichier .c                                
// les declaration de variables globales externes   

enum formes{        // faire le lien entre la forme et un entier
    cube = 0,
    cone = 1,
    cylindre = 2,
    sphere = 3
}formes;


typedef struct piece {      //structure d'une pièce
    enum formes;             //forme de la pièce
    int joueur;             //0=>joueur1=>piece blanche | 1=>joueur2=>piece noir
} piece;


typedef struct list {
    int value;          
    struct list * next;
} list;


typedef struct joueur {
    int numJoueur;              //0=>joueur1=>piece blanche | 1=>joueur2=>piece noir
    int ia;                     //0=>joueur humain | >0 profondeur de l'arbre parcourue
    int piecerestante[4][2];    //tableau des pieces restantes
} joueur;


typedef struct grille {
    piece grid[4][4];
}grille;

piece creerPiece(forme forme,int player);
grille creationplateau();
void victoireligne(int x,grille plateau);
void victoirecolonne(int y, grille plateau);
void victoireregion(int x, int y, grille plateau);
void victoire(grille plateau, int x, int y);

#endif