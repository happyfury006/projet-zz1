#include "situation.h"

#include <string.h>

#include "action.h"

void creation_situation(situation *s) {
  memset(s, 0, sizeof *s);
  // chaque joueur commence avec une route et un chevalier, face A
  for (int j = 0; j < 2; j++) {
    sitjoueur *joueur = &s->joueurs[j];
    joueur->tab_constru_joueur[ROUTE] = 1;
    joueur->tab_constru_joueur[CHEVALIER] = 1;
    joueur->nb_echanges_marchee = 1;
    joueur->nb_cartes_mainjoueur = MAIN_DE_BASE + 1;
  }

  // cartes ressource de la pioche
  s->pioche[BOIS] = 11;
  s->pioche[ARGILE] = 11;
  s->pioche[MOUTON] = 15;
  s->pioche[BLE] = 14;
  s->pioche[MINERAI] = 11;

  // cartes construction disponibles (les routes et chevaliers de départ en moins)
  s->tab_constru_board[ROUTE] = 9 - 2;
  s->tab_constru_board[CHEVALIER] = 14 - 2;
  s->tab_constru_board[COLONIE] = 15;
  s->tab_constru_board[VILLE] = 15;
  s->tab_constru_board[CARTE_DEVELOPPEMENT] = 9;

  initialisation_marchee(s);
  s->trait = 0;
  s->tour = 1;
  s->gagnant = -1;
  // le joueur 2 complète sa main tout de suite, le joueur 1 au début de son tour
  completer_main(s, 1);
  debut_tour(s);
}
