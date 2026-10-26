#include "affichageterminal.h"

#include <stdio.h>

const char *NOMS_RESSOURCES[NB_RESSOURCE] = {"bois", "argile", "mouton", "minerai", "blé"};
const char *NOMS_CONSTRUCTIONS[NB_CONSTRUCTION] = {"route", "chevalier", "colonie", "ville", "développement"};

static void affichage_tas(const char *titre, const int tas[NB_RESSOURCE]) {
  printf("%-10s", titre);
  for (int r = 0; r < NB_RESSOURCE; r++) printf(" %s:%d", NOMS_RESSOURCES[r], tas[r]);
  printf("\n");
}

void affichage(const situation *s) {
  printf("\n===== Tour %d, joueur %d =====\n", s->tour, s->trait + 1);
  for (int j = 0; j < 2; j++) {
    const sitjoueur *joueur = &s->joueurs[j];
    printf("Joueur %d : %d points |", j + 1, joueur->compteur_points_joueur);
    for (int c = 0; c < NB_CONSTRUCTION; c++) printf(" %s:%d", NOMS_CONSTRUCTIONS[c], joueur->tab_constru_joueur[c]);
    printf("\n");
  }
  affichage_tas("Marché", s->marchee);
  printf("Pioche : %d cartes\n", nbr_carte_liste(s->pioche, NB_RESSOURCE));
  affichage_tas("Votre main", s->joueurs[s->trait].mainjoueur);
  printf("Échanges restants : %d avec la pioche, %d avec le marché%s\n", s->echanges_pioche_restants,
         s->echanges_marchee_restants, s->a_construit ? " (déjà construit ce tour)" : "");
}

void affichage_action(action a) {
  switch (a.type) {
    case ECHANGE_MARCHEE:
      printf("échanger 1 %s contre 1 %s du marché", NOMS_RESSOURCES[a.a], NOMS_RESSOURCES[a.b]);
      break;
    case ECHANGE_PIOCHE: printf("défausser 1 %s et piocher", NOMS_RESSOURCES[a.a]); break;
    case CONSTRUIRE: printf("construire : %s", NOMS_CONSTRUCTIONS[a.a]); break;
    case FIN_TOUR: printf("finir le tour"); break;
  }
}
