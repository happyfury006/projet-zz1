#include "utils.h"

#include <stdlib.h>

int randomiser(int N) { return rand() % N; }

int nbr_carte_liste(const int liste[], int N) {
  int compteur = 0;
  for (int i = 0; i < N; i++) {
    compteur += liste[i];
  }
  return compteur;
}

// Retire une carte au hasard d'un tas (pioche, marché...) en respectant les
// proportions : avec 11 bois et 15 moutons, un mouton sort plus souvent.
// Renvoie la ressource tirée, ou -1 si le tas est vide.
int tirer_carte(int tas[NB_RESSOURCE]) {
  int total = nbr_carte_liste(tas, NB_RESSOURCE);
  if (total == 0) return -1;
  int n = randomiser(total);
  for (int r = 0; r < NB_RESSOURCE; r++) {
    if (n < tas[r]) {
      tas[r]--;
      return r;
    }
    n -= tas[r];
  }
  return -1;
}
