#include "action.h"

#include "regles.h"
#include "victoire.h"

// Le joueur pioche des cartes ; renvoie faux si la pioche s'est vidée avant
bool piocher(situation *s, int joueur, int nombre_carte) {
  for (int i = 0; i < nombre_carte; i++) {
    int r = tirer_carte(s->pioche);
    if (r < 0) return false;
    s->joueurs[joueur].mainjoueur[r]++;
  }
  return true;
}

// Complète la main jusqu'à sa taille. Si la pioche ne suffit pas, la partie
// s'arrête : le joueur qui a le plus de points gagne.
void completer_main(situation *s, int joueur) {
  sitjoueur *j = &s->joueurs[joueur];
  int manque = j->nb_cartes_mainjoueur - nbr_carte_liste(j->mainjoueur, NB_RESSOURCE);
  if (manque > 0 && !piocher(s, joueur, manque)) {
    terminer_partie(s);
  }
}

void initialisation_marchee(situation *s) {
  for (int i = 0; i < TAILLE_MARCHE; i++) {
    int r = tirer_carte(s->pioche);
    if (r >= 0) s->marchee[r]++;
  }
}

void defausser(situation *s, int ressource) {
  s->joueurs[s->trait].mainjoueur[ressource]--;
  s->defausse[ressource]++;
}

// Une carte de la main contre une carte du marché
bool echanger_marchee(situation *s, int ressourcemain, int ressource) {
  if (!valide_echange_marchee(s, ressourcemain, ressource)) return false;
  sitjoueur *j = &s->joueurs[s->trait];
  j->mainjoueur[ressourcemain]--;
  j->mainjoueur[ressource]++;
  s->marchee[ressourcemain]++;
  s->marchee[ressource]--;
  s->echanges_marchee_restants--;
  return true;
}

// Une carte de la main va à la défausse, et on en pioche une autre
bool echanger_pioche(situation *s, int ressourcemain) {
  if (!valide_echange_pioche(s, ressourcemain)) return false;
  defausser(s, ressourcemain);
  piocher(s, s->trait, 1);
  s->echanges_pioche_restants--;
  return true;
}

// Début du tour : on complète sa main et on remet les compteurs d'échanges
void debut_tour(situation *s) {
  completer_main(s, s->trait);
  s->echanges_pioche_restants = ECHANGES_PIOCHE_MAX;
  s->echanges_marchee_restants = s->joueurs[s->trait].nb_echanges_marchee;
  s->a_construit = false;
}

void fin_tour(situation *s) {
  if (s->finie) return;
  s->trait = 1 - s->trait;
  if (s->trait == 0) s->tour++;
  debut_tour(s);
}
