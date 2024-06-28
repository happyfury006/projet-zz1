#include "coups.h"
#include "situation.h"
#include <stdio.h>
#include <stdlib.h>

void generer_combinaisons_main(int *main, int taille, Nodemcts *noeud) {
  // Combinaisons de 2 cartes
  for (int i = 0; i < taille; i++) {
    if (main[i] > 0) {
      for (int j = i; j < taille; j++) {
        if (i == j && main[i] > 1) {
          Conteneur *defausse = initConteneurCouple(i, j);
          Nodemcts *liste = initNodemcts(defausse, NULL, -1);
        } else if (i != j && main[j] > 0) {
          int combinaison[2] = {i, j};
          // insert_tete(liste, combinaison, 2);
        }
      }
    }
  }
  // Combinaisons de 1 carte
  for (int i = 0; i < taille; i++) {
    if (main[i] > 0) {
      int combinaison[1] = {i};
      // insert_tete(liste, combinaison, 1);
    }
  }
}
