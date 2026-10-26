#include "construction.h"

#include "action.h"
#include "regles.h"
#include "victoire.h"

// Effet de chaque carte, d'après son texte :
// - route : face A (1re, 3e...) un échange avec le marché de plus par tour, face B 1 point
// - chevalier : face A une carte de plus en main, face B 1 point
// - colonie : 1 point
// - ville : 2 points, et « jour du marché » : le marché est défaussé et remplacé
// - développement : 3 points
bool construction(situation *s, int construc) {
  if (!valide_construction(s, construc)) return false;
  sitjoueur *joueur = &s->joueurs[s->trait];

  // les ressources dépensées vont à la défausse
  for (int r = 0; r < NB_RESSOURCE; r++) {
    for (int k = 0; k < GUIDE_CONSTRUCTION[construc][r]; k++) defausser(s, r);
  }
  s->tab_constru_board[construc]--;
  joueur->tab_constru_joueur[construc]++;
  bool face_a = joueur->tab_constru_joueur[construc] % 2 == 1;

  switch (construc) {
    case ROUTE:
      if (face_a) {
        joueur->nb_echanges_marchee++;
        s->echanges_marchee_restants++;  // utilisable dès ce tour
      } else {
        joueur->compteur_points_joueur += 1;
      }
      break;
    case CHEVALIER:
      if (face_a) joueur->nb_cartes_mainjoueur++;
      else joueur->compteur_points_joueur += 1;
      break;
    case COLONIE:
      joueur->compteur_points_joueur += 1;
      break;
    case VILLE:
      joueur->compteur_points_joueur += 2;
      for (int r = 0; r < NB_RESSOURCE; r++) {  // jour du marché
        s->defausse[r] += s->marchee[r];
        s->marchee[r] = 0;
      }
      initialisation_marchee(s);
      break;
    case CARTE_DEVELOPPEMENT:
      joueur->compteur_points_joueur += 3;
      break;
  }
  s->a_construit = true;
  if (victoire_point_obj(joueur)) {
    s->finie = true;
    s->gagnant = s->trait;
  }
  return true;
}
