#ifndef GARDIEN_UNIQUE_UTILS_H
#define GARDIEN_UNIQUE_UTILS_H

#define TAILLE_GUIDE 5
#define NB_RESSOURCE 5
#define NB_CONSTRUCTION 5
#define TAILLE_MARCHER 5

enum construction {ROUTE = 0, CHEVALIER = 1,COLONIE = 2, VILLE = 3, CARTE_DEVELOPPEMENT = 4};
enum ressource {BOIS = 0, ARGILE = 1, MOUTON = 2, MINERAI = 3, BLE = 4};

int random(int N);
int nbr_carte_liste(int liste[], int N);

#endif