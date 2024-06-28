#ifndef GARDIEN_UNIQUE_CONSTRUCTION_H
#define GARDIEN_UNIQUE_CONSTRUCTION_H

#include "situation.h"

void actualiser_board(sitjoueur *joueur1, sitjoueur *joueur2, int construc);
void construction_route(sitjoueur *joueur1, sitjoueur *joueur2, int construc);
void construction_chevalier(sitjoueur *joueur1, sitjoueur *joueur2,
                            int construc);
void construction_colonie(sitjoueur *joueur1, sitjoueur *joueur2, int construc);
void construction_ville(sitjoueur *joueur1, sitjoueur *joueur2, int construc);
void construction_developpement(sitjoueur *joueur1, sitjoueur *joueur2,
                                int construc);
void construction(sitjoueur *joueur1, sitjoueur *joueur2, int construc);

#endif // GARDIEN_UNIQUE_CONSTRUCTION_H