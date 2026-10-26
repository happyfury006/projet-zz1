#ifndef GARDIEN_UNIQUE_SITUATION_H
#define GARDIEN_UNIQUE_SITUATION_H

#include <stdbool.h>

#include "utils.h"

typedef struct sitjoueur {
  int mainjoueur[NB_RESSOURCE];             // cartes ressource en main
  int tab_constru_joueur[NB_CONSTRUCTION];  // constructions posées
  int compteur_points_joueur;
  int nb_echanges_marchee;   // échanges avec le marché par tour (routes face A)
  int nb_cartes_mainjoueur;  // taille de la main (chevaliers face A)
} sitjoueur;

// Toute la partie : les deux joueurs et ce qu'ils partagent. Dans la première
// version, chaque joueur gardait sa propre copie de la pioche et du marché.
typedef struct situation {
  sitjoueur joueurs[2];
  int pioche[NB_RESSOURCE];
  int defausse[NB_RESSOURCE];
  int marchee[NB_RESSOURCE];               // cartes du marché, par ressource
  int tab_constru_board[NB_CONSTRUCTION];  // cartes construction restantes
  int trait;                               // joueur qui joue (0 ou 1)
  int tour;
  int echanges_pioche_restants;
  int echanges_marchee_restants;
  bool a_construit;  // une seule construction par tour
  bool finie;
  int gagnant;  // 0 ou 1, -1 en cas d'égalité
} situation;

void creation_situation(situation *s);

#endif
