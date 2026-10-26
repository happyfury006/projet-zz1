#include "victoire.h"

// Le premier à 10 points gagne
bool victoire_point_obj(const sitjoueur *joueur) {
  return joueur->compteur_points_joueur >= POINTS_VICTOIRE;
}

// La pioche est vide : le joueur qui a le plus de points gagne
void terminer_partie(situation *s) {
  int p0 = s->joueurs[0].compteur_points_joueur;
  int p1 = s->joueurs[1].compteur_points_joueur;
  s->finie = true;
  s->gagnant = p0 > p1 ? 0 : p1 > p0 ? 1 : -1;
}
