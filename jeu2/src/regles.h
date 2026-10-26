#ifndef GARDIEN_UNIQUE_REGLES_H
#define GARDIEN_UNIQUE_REGLES_H

#include <stdbool.h>

#include "situation.h"

// Coût de chaque construction, en cartes ressource
extern const int GUIDE_CONSTRUCTION[NB_CONSTRUCTION][NB_RESSOURCE];

bool valide_construction(const situation *s, int construction);
bool valide_echange_marchee(const situation *s, int ressourcemain, int ressource);
bool valide_echange_pioche(const situation *s, int ressourcemain);

#endif
