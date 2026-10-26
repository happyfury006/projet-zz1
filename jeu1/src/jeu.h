#ifndef GARDIEN_UNIQUE_JEU_H
#define GARDIEN_UNIQUE_JEU_H

#include <stdbool.h>

#include "utils.h"

// Règles du Quantik
// - Chacun pose à tour de rôle une de ses pièces sur une case vide.
// - Interdit de poser une forme dans une ligne, une colonne ou un carré où
//   l'adversaire a déjà posé cette même forme.
// - Gagne celui qui pose la 4e forme différente d'une ligne, d'une colonne ou
//   d'un carré, quelle que soit la couleur des pièces déjà posées.
// - Un joueur qui ne peut plus jouer a perdu.

typedef struct grille {
  int forme[TAILLE][TAILLE];        // vide ou une des quatre formes
  int joueur[TAILLE][TAILLE];       // personne, joueur1 ou joueur2
  int restantes[2][NB_FORMES + 1];  // pièces restantes, par joueur et par forme
  int trait;                        // joueur qui doit jouer
  int nbcoups;                      // nombre de pièces posées
} grille;

typedef struct coups {
  int x;  // ligne
  int y;  // colonne
  int forme;
} coups;

void creationplateau(grille *plateau);
int region(int x, int y);
bool valide(const grille *plateau, int numJoueur, int forme, int x, int y);
int coupspossibles(const grille *plateau, coups liste[NB_COUPS_MAX]);
void jouercoup(grille *plateau, coups coup);
void annulercoup(grille *plateau, coups coup);
bool victoire(const grille *plateau, int x, int y);
bool coupgagnant(grille *plateau, coups coup);
void affichageplateau(const grille *plateau);

#endif
