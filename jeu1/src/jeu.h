#ifndef GARDIEN_UNIQUE_JEU_H
#define GARDIEN_UNIQUE_JEU_H

#include<stdio.h>
#include <stdbool.h>
#include "utils.h"


// fichier d'entete classique ou l'on declare les types necessaires,            
// les fonctions implementees dans le fichier .c                                
// les declaration de variables globales externes   

// enum formes{        // faire le lien entre la forme et un entier
//     cube = 0,
//     cone = 1,
//     cylindre = 2,
//     sphere = 3
// }formes;


typedef struct piece {      //structure d'une pièce
    int formes;             //forme de la pièce
    int joueur;             //0=>joueur1=>piece blanche | 1=>joueur2=>piece noir
} piece;


typedef struct joueur {
    int numJoueur;              //0=>joueur1=>piece blanche | 1=>joueur2=>piece noir
    int ia;                     //0=>joueur humain | >0 profondeur de l'arbre parcourue
    int piecerestante[4][2];    //tableau des pieces restantes
} joueur;


typedef struct grille {
    piece* grid[4][4];
    int valeur;                  
}grille;

piece creerPiece(int forme,int player);
grille creationplateau();
bool victoireligne(int x,grille plateau);
bool victoirecolonne(int y, grille plateau);
bool cherccheregion(int x, int y, grille plateau,list * lparcouru);
bool victoireregion(int x, int y, grille plateau);
bool victoire(grille plateau, int x, int y);
grille ajoutpiece(grille plateau, piece pieceajoutee, int x, int y);
void affichageplateau(grille plateau);


#endif