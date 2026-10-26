#ifndef GARDIEN_UNIQUE_IA_H
#define GARDIEN_UNIQUE_IA_H

#include "jeu.h"

// Minimax avec élagage alpha-bêta, écrit sous la forme « negamax » : le score
// est toujours vu du joueur qui a le trait, et on inverse le signe à chaque
// niveau. L'arbre n'est jamais stocké : on joue le coup sur le plateau, on
// explore récursivement, puis on l'annule.

#define VICTOIRE 1000  // score d'une partie gagnée (moins le nombre de coups)

int minmaxalphabeta(grille *plateau, int profondeur, int alpha, int beta);
int profondeurconseillee(const grille *plateau);
coups trouver_meilleur_coup(grille *plateau, int profondeur, int *score);

#endif
