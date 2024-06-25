#ifndef GARDIEN_UNIQUE_SITUATION_H
#define GARDIEN_UNIQUE_SITUATION_H


#include "utils.h"

typedef struct situation {
  int joueur;
  int mainjoueur[NB_RESSOURCE];
  int compteur_points_joueur;
  int nb_echanges_marchee;
  int nb_cartes_mainjoueur;
  int pioche[NB_RESSOURCE];
  
  int defausse[NB_RESSOURCE];
  int tab_constru_joueur[NB_CONSTRUCTION];
  int tab_constru_advers[NB_CONSTRUCTION];
  int tab_constru_board[NB_CONSTRUCTION];
  int marchee[TAILLE_MARCHER];

} sitjoueur;

sitjoueur* creation_situation(int joueur);
sitjoueur* initilisation_depart(sitjoueur* joueur);
void destruction_situation(sitjoueur* s);
#endif // GARDIEN_UNIQUE_SITUATION_H