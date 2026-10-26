#include "partie.h"

#include <stdio.h>
#include <stdlib.h>

#include "affichageterminal.h"
#include "mcts.h"

void partie(int contre_ia) {
  situation s;
  creation_situation(&s);
  while (!s.finie) {
    action a;
    if (contre_ia && s.trait == 1) {
      a = choisir_action_mcts(&s, ITERATIONS_IA);
      printf("L'IA choisit : ");
      affichage_action(a);
      printf("\n");
    } else {
      affichage(&s);
      action liste[NB_ACTIONS_MAX];
      int n = lister_actions(&s, liste);
      for (int i = 0; i < n; i++) {
        printf("  %2d : ", i);
        affichage_action(liste[i]);
        printf("\n");
      }
      int choix = -1;
      while (choix < 0 || choix >= n) {
        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1) exit(0);
      }
      a = liste[choix];
    }
    appliquer_action(&s, a);
  }
  printf("\nFin de la partie : %d points contre %d. ", s.joueurs[0].compteur_points_joueur,
         s.joueurs[1].compteur_points_joueur);
  if (s.gagnant < 0) printf("Égalité !\n");
  else printf("%s gagne !\n", contre_ia && s.gagnant == 1 ? "L'IA" : s.gagnant == 0 ? "Le joueur 1" : "Le joueur 2");
}
