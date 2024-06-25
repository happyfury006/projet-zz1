#ifndef GARDIEN_UNIQUE_ACTION_H
#define GARDIEN_UNIQUE_ACTION_H

// #include <stdio.h>
// #include <stdarg.h>
// #include <stdlib.h>
// #include <time.h>
#include "situation.h"


//void deplacement(int joueur); 

void defausser(sitjoueur* joueur1,sitjoueur* joueur2, int ressource1);
void piocher(sitjoueur* joueur1,sitjoueur* joueur2, int nombre_carte);
void initialisation_marchee(sitjoueur* joueur1,sitjoueur* joueur2);
void echanger_marchee(sitjoueur* joueur1,sitjoueur* joueur2,int ressourcemain, int ressource);
void echanger_pioche(sitjoueur* joueur1,sitjoueur* joueur2, int num_ressources, ...);


#endif // GARDIEN_UNIQUE_ACTION_H