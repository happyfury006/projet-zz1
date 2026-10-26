#ifndef GARDIEN_UNIQUE_AFFICHAGETERMINAL_H
#define GARDIEN_UNIQUE_AFFICHAGETERMINAL_H

#include "mcts.h"
#include "situation.h"

extern const char *NOMS_RESSOURCES[NB_RESSOURCE];
extern const char *NOMS_CONSTRUCTIONS[NB_CONSTRUCTION];

void affichage(const situation *s);
void affichage_action(action a);

#endif
