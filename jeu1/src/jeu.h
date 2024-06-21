#ifndef GARDIEN_UNIQUE_JEU_H
#define GARDIEN_UNIQUE_JEU_H

#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

// fichier d'entete classique ou l'on declare les types necessaires,
// les fonctions implementees dans le fichier .c
// les declaration de variables globales externes

typedef struct grille {
  struct piece *grid[4][4];
  int valeur;
} grille;

joueur *creerjoueur(int numJoueur, int ia);
piece *creerPiece(int forme, joueur *player);
grille *creationplateau();
bool valideligne(int x, int joueur, int forme, grille *plateau);
bool validecolonne(int y, int joueur, int forme, grille *plateau);
bool valideregion(int x, int y, int joueur, int forme, grille *plateau);
bool valide(int forme, int joueur, int x, int y, grille *plateau);
grille *ajoutpiece(grille *plateau, int forme, joueur *joueur, int x, int y);
void affichageplateau(grille *plateau);
bool victoireligne(int x, grille *plateau);
bool victoirecolonne(int y, grille *plateau);
bool chercheregion(int x, int y, grille *plateau, list *lparcouru);
bool victoireregion(int x, int y, grille *plateau);
bool victoire(grille *plateau, int x, int y);
grille *demandepiece(grille *plateau, joueur *joueur);
void jeuencours1VSIA();
bool jeuencours1VS1();

#endif