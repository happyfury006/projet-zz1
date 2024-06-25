#ifdef GARDIEN_UNIQUE_SITUATION_H
#define GARDIEN_UNIQUE_SITUATION_H

enum ressource {BOIS =1, ARGILE=2, PIERRE=3, MOUTON=4, FOIN=5};

typedef struct situation{
  int joueur;
  int mainjoueur[5];
  int compteur_points_joueur;
  int nb_echanges;
  int nb_cartes_mainjoueur;
  int pioche[5];
  int nb_cartes_pioche;
  int defausse[5];
  int tab_constru_joueur[4];
  int tab_constru_advers[4];
  int tab_constru_board[4];
  int marcher[5];

}situation;

situation* creation_situation(int joueur, int mainjoueur[5], int compteur_points_joueur, int nb_echanges, int nb_cartes_mainjoueur, int pioche[5], int nb_cartes_pioche, int defausse[5], int tab_constru_joueur[4], int tab_constru_advers[4], int tab_constru_board[4], int marcher[5]);

#endif // GARDIEN_UNIQUE_SITUATION_H