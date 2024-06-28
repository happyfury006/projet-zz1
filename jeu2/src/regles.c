#include "regles.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

tabconstruction creation_guide_construction() {
  tabconstruction tab;
  for (int i = 0; i < TAILLE_GUIDE; i++) {
    for (int j = 0; j < NB_RESSOURCE; j++) {
      tab.tabconstruction[i].tabressource[j] = 0;
    }
  }
  return tab;
}
tabconstruction guide_construction() {
  tabconstruction tab = creation_guide_construction();
  tab.tabconstruction[ROUTE].tabressource[BOIS] = 1;
  tab.tabconstruction[ROUTE].tabressource[ARGILE] = 1;
  tab.tabconstruction[CHEVALIER].tabressource[MOUTON] = 1;
  tab.tabconstruction[CHEVALIER].tabressource[BLE] = 1;
  tab.tabconstruction[CHEVALIER].tabressource[MINERAI] = 1;
  tab.tabconstruction[COLONIE].tabressource[BOIS] = 1;
  tab.tabconstruction[COLONIE].tabressource[ARGILE] = 1;
  tab.tabconstruction[COLONIE].tabressource[MOUTON] = 1;
  tab.tabconstruction[COLONIE].tabressource[BLE] = 1;
  tab.tabconstruction[VILLE].tabressource[MINERAI] = 3;
  tab.tabconstruction[VILLE].tabressource[BLE] = 2;
  tab.tabconstruction[CARTE_DEVELOPPEMENT].tabressource[MINERAI] = 1;
  tab.tabconstruction[CARTE_DEVELOPPEMENT].tabressource[MOUTON] = 3;
  return tab;
}

void destruction_guide_construction(tabconstruction *tab) { free(tab); }

bool valide_construction(sitjoueur *joueur, int construction) {
  tabconstruction tab = guide_construction();

  for (int i = 0; i < NB_RESSOURCE; i++) {
    if (joueur->mainjoueur[i] <
        tab.tabconstruction[construction].tabressource[i]) {
      return false;
    }
    if (construction == VILLE) {
      if (joueur->tab_constru_joueur[construction - 1] -
              joueur->tab_constru_joueur[construction] ==
          0) {
        return false;
      }
    }
  }
  return true;
}