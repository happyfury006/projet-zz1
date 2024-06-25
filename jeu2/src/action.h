#ifdef GARDIEN_UNIQUE_ACTION_H
#define GARDIEN_UNIQUE_ACTION_H

void echange_marcher(int joueur, int *mainjoueur, int *marcher, int *nb_cartes_pioche, int *defausse, int *nb_cartes_mainjoueur, int *nb_echanges);
void echanger(int joueur, int *mainjoueur, int *marcher, int *pioche, int *nb_cartes_pioche, int *defausse, int *nb_cartes_mainjoueur, int *nb_echanges);


void deplacement(int joueur)
void construction(int joueur, int *main_joueur , int *tab_constru_joueur, int *tab_constru_board, int *marcher);  
void defausse(int joueur, int *main_joueur, int *defausse, int *nb_cartes_mainjoueur);
void pioche(int joueur, int *main_joueur, int *pioche, int *nb_cartes_pioche, int *nb_cartes_mainjoueur);

#endif // GARDIEN_UNIQUE_ACTION_H