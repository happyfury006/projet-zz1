#ifndef GARDIEN_UNIQUE_COUPS_H
#define GARDIEN_UNIQUE_COUPS_H

#include "liste_chainee.h"
#include "regles.h"


void generer_combinaisons_main(int *main, int taille, liste_chainee* liste);
liste_chainee* init_defausse(sitjoueur* sit);

#endif // GARDIEN_UNIQUE_COUPS_H