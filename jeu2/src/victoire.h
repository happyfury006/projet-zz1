#ifndef GARDIEN_UNIQUE_VICTOIRE_H
#define GARDIEN_UNIQUE_VICTOIRE_H

#include <stdbool.h>

#include "situation.h"

bool victoire_point_obj(const sitjoueur *joueur);
void terminer_partie(situation *s);

#endif // GARDIEN_UNIQUE_VICTOIRE_H
