#ifndef GARDIEN_UNIQUE_MCTS_H
#define GARDIEN_UNIQUE_MCTS_H

#include "situation.h"

// Une action d'un tour : échange avec le marché, échange avec la pioche,
// construction ou fin du tour
typedef enum { ECHANGE_MARCHEE, ECHANGE_PIOCHE, CONSTRUIRE, FIN_TOUR } type_action;

typedef struct action {
  type_action type;
  int a;  // ressource donnée, ou construction
  int b;  // ressource prise au marché
} action;

#define NB_ACTIONS_MAX (NB_RESSOURCE * NB_RESSOURCE + NB_RESSOURCE + NB_CONSTRUCTION + 1)
#define ITERATIONS_IA 3000

int lister_actions(const situation *s, action liste[NB_ACTIONS_MAX]);
void appliquer_action(situation *s, action a);
action choisir_action_glouton(const situation *s);
action choisir_action_mcts(const situation *s, int iterations);

#endif
