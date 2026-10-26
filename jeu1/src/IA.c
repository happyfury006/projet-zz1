#include "IA.h"

#include <stdlib.h>

// Évaluation d'une position non terminale, vue du joueur qui a le trait :
// un joueur qui ne peut plus jouer a perdu, donc garder plus de coups
// possibles que l'adversaire est un avantage.
static int evaluation(grille *plateau) {
  coups liste[NB_COUPS_MAX];
  int moi = coupspossibles(plateau, liste);
  plateau->trait = 1 - plateau->trait;
  int lui = coupspossibles(plateau, liste);
  plateau->trait = 1 - plateau->trait;
  return moi - lui;
}

// Score de la position pour le joueur qui a le trait. Une victoire vaut
// VICTOIRE moins le nombre de pièces posées : l'IA préfère gagner vite et
// perdre le plus tard possible.
int minmaxalphabeta(grille *plateau, int profondeur, int alpha, int beta) {
  coups liste[NB_COUPS_MAX];
  int n = coupspossibles(plateau, liste);
  if (n == 0) {
    return -(VICTOIRE - plateau->nbcoups);  // bloqué : perdu
  }
  for (int i = 0; i < n; i++) {
    if (coupgagnant(plateau, liste[i])) {
      return VICTOIRE - (plateau->nbcoups + 1);
    }
  }
  if (profondeur == 0) {
    return evaluation(plateau);
  }

  int meilleur = -VICTOIRE - 1;
  for (int i = 0; i < n; i++) {
    jouercoup(plateau, liste[i]);
    int score = -minmaxalphabeta(plateau, profondeur - 1, -beta, -alpha);
    annulercoup(plateau, liste[i]);
    if (score > meilleur) meilleur = score;
    if (score > alpha) alpha = score;
    if (alpha >= beta) break;  // l'adversaire n'ira jamais dans cette branche
  }
  return meilleur;
}

// En début de partie il y a jusqu'à 64 coups possibles par tour : on limite la
// profondeur. Dès que le plateau se remplit, l'IA calcule jusqu'à la fin.
int profondeurconseillee(const grille *plateau) {
  if (plateau->nbcoups < 2) return 3;
  if (plateau->nbcoups < 4) return 4;
  if (plateau->nbcoups < 6) return 6;
  return TAILLE * TAILLE;
}

coups trouver_meilleur_coup(grille *plateau, int profondeur, int *score) {
  coups liste[NB_COUPS_MAX];
  int n = coupspossibles(plateau, liste);
  coups meilleurs[NB_COUPS_MAX];
  int nbmeilleurs = 0;
  int meilleur = -VICTOIRE - 1;

  for (int i = 0; i < n; i++) {
    int valeur;
    if (coupgagnant(plateau, liste[i])) {
      valeur = VICTOIRE - (plateau->nbcoups + 1);
    } else {
      jouercoup(plateau, liste[i]);
      // fenêtre élargie de 1 : les coups à égalité gardent leur score exact
      valeur = -minmaxalphabeta(plateau, profondeur - 1, -VICTOIRE - 1, -meilleur + 1);
      annulercoup(plateau, liste[i]);
    }
    if (valeur > meilleur) {
      meilleur = valeur;
      nbmeilleurs = 0;
    }
    if (valeur == meilleur) meilleurs[nbmeilleurs++] = liste[i];
  }

  if (score != NULL) *score = meilleur;
  // parmi les meilleurs coups, on en tire un au hasard pour varier les parties
  return meilleurs[rand() % nbmeilleurs];
}
