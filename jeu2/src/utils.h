#ifndef GARDIEN_UNIQUE_UTILS_H
#define GARDIEN_UNIQUE_UTILS_H

#define TAILLE_GUIDE 5
#define NB_RESSOURCE 5
#define NB_CONSTRUCTION 5
#define TAILLE_MARCHER 5

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct carte{
    int type;                 //0 = route | 1 = chevalier | ...
    int nbr_points;          //nbr_points face 
    SDL_Texture *texture;
    SDL_Rect rect;
    int selected;
    int posee;
}carte;

typedef struct tab_carte_construction {
  struct carte* tab_carte_construction[NB_CONSTRUCTION+2];
} tab_carte_construction;

//Enumeration
enum construction {ROUTE = 0, CHEVALIER = 1,COLONIE = 2, VILLE = 3, CARTE_DEVELOPPEMENT = 4};
enum ressource {BOIS = 0, ARGILE = 1, MOUTON = 2, MINERAI = 3, BLE = 4};

//Fonctions
carte* creation_carte(int type);
tab_carte_construction creation_tab_carte_construction();
int randomiser(int N);
int nbr_carte_liste(int liste[], int N);

#endif