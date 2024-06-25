#ifndef GARDIEN_UNIQUE_ACTION_H
#define GARDIEN_UNIQUE_ACTION_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

int random(int N);
int nbr_carte_liste(int liste[], int N);

void deplacement(int joueur);
void construction(sitjoueur* joueur1, int construction);  

void defausse(sitjoueur* joueur1,sitjoueur* joueur2, int ressource1);
void pioche(sitjoueur* joueur1,sitjoueur* joueur2);

void echange_marche(sitjoueur* joueur1,sitjoueur* joueur2);
void echange_pioche(sitjoueur* joueur1,sitjoueur* joueur2, int num_ressources, ...);


#endif // GARDIEN_UNIQUE_ACTION_H