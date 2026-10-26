#ifndef GARDIEN_UNIQUE_ACTION_H
#define GARDIEN_UNIQUE_ACTION_H

#include <stdbool.h>

#include "situation.h"

bool piocher(situation *s, int joueur, int nombre_carte);
void completer_main(situation *s, int joueur);
void initialisation_marchee(situation *s);
void defausser(situation *s, int ressource);
bool echanger_marchee(situation *s, int ressourcemain, int ressource);
bool echanger_pioche(situation *s, int ressourcemain);
void debut_tour(situation *s);
void fin_tour(situation *s);

#endif
