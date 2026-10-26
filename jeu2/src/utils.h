#ifndef GARDIEN_UNIQUE_UTILS_H
#define GARDIEN_UNIQUE_UTILS_H

// Constantes et fonctions communes au jeu, à l'IA et à l'interface

#define NB_RESSOURCE 5
#define NB_CONSTRUCTION 5
#define TAILLE_MARCHE 5
#define POINTS_VICTOIRE 10
#define MAIN_DE_BASE 3          // cartes en main, plus une par chevalier face A
#define ECHANGES_PIOCHE_MAX 2   // échanges avec la pioche par tour

enum construction {
  ROUTE = 0,
  CHEVALIER = 1,
  COLONIE = 2,
  VILLE = 3,
  CARTE_DEVELOPPEMENT = 4
};
enum ressource { BOIS = 0, ARGILE = 1, MOUTON = 2, MINERAI = 3, BLE = 4 };

int randomiser(int N);
int nbr_carte_liste(const int liste[], int N);
int tirer_carte(int tas[NB_RESSOURCE]);

#endif
