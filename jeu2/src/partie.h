#ifndef GARDIEN_UNIQUE_PARTIE_H
#define GARDIEN_UNIQUE_PARTIE_H

#include "situation.h"
#include "utils.h"


void init_partie(sitjoueur* joueur1,sitjoueur* joueur2);
void phase_echange(sitjoueur* joueur1,sitjoueur* joueur2);
void phase_pioche(sitjoueur* joueur1,sitjoueur* joueur2);
void phase_construction(sitjoueur* joueur1,sitjoueur* joueur2);
void partie(sitjoueur* joueur1,sitjoueur* joueur2 );

#endif