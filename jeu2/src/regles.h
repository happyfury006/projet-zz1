#ifndef GARDIEN_UNIQUE_REGLES_H
#define GARDIEN_UNIQUE_REGLES_H
#include "situation.h"
#include <stdbool.h>
#include "utils.h"


typedef struct ressources {
  int tabressource[NB_CONSTRUCTION];
} ressources;
typedef struct tabconstruction {
  struct ressources tabconstruction[NB_CONSTRUCTION];
} tabconstruction;

tabconstruction creation_guide_construction();
tabconstruction guide_construction();
void destruction_guide_construction(tabconstruction* tab);
bool valide_construction(sitjoueur* joueur);

#endif