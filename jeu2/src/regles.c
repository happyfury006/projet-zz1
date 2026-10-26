#include "regles.h"

//                                                     bois argile mouton minerai blé
const int GUIDE_CONSTRUCTION[NB_CONSTRUCTION][NB_RESSOURCE] = {
    [ROUTE] = {1, 1, 0, 0, 0},
    [CHEVALIER] = {0, 0, 1, 1, 1},
    [COLONIE] = {1, 1, 1, 0, 1},
    [VILLE] = {0, 0, 0, 3, 2},
    [CARTE_DEVELOPPEMENT] = {0, 0, 3, 1, 0},
};

bool valide_construction(const situation *s, int construction) {
  const sitjoueur *joueur = &s->joueurs[s->trait];
  if (s->finie || s->a_construit || s->tab_constru_board[construction] == 0) {
    return false;
  }
  for (int r = 0; r < NB_RESSOURCE; r++) {
    if (joueur->mainjoueur[r] < GUIDE_CONSTRUCTION[construction][r]) return false;
  }
  // une ville remplace une colonie : il faut une colonie pas encore améliorée
  if (construction == VILLE &&
      joueur->tab_constru_joueur[COLONIE] <= joueur->tab_constru_joueur[VILLE]) {
    return false;
  }
  return true;
}

bool valide_echange_marchee(const situation *s, int ressourcemain, int ressource) {
  return !s->finie && s->echanges_marchee_restants > 0 && ressourcemain != ressource &&
         s->joueurs[s->trait].mainjoueur[ressourcemain] > 0 && s->marchee[ressource] > 0;
}

bool valide_echange_pioche(const situation *s, int ressourcemain) {
  return !s->finie && s->echanges_pioche_restants > 0 &&
         s->joueurs[s->trait].mainjoueur[ressourcemain] > 0 &&
         nbr_carte_liste(s->pioche, NB_RESSOURCE) > 0;
}
