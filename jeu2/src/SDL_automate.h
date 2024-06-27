#ifndef GARDIEN_UNIQUE_SLD_AUTOMATE_H
#define GARDIEN_UNIQUE_SLD_AUTOMATE_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "situation.h"
#include "regles.h"
#include "victoire.h"
#include "action.h"

#define GRID_WIDTH 4
#define GRID_HEIGHT 4
#define GRID1_WIDTH 6
#define GRID1_HEIGHT 1
#define NB_CARTES 22 // Mise à jour du nombre total de cartes
#define WINDOW_HAUTEUR 1200
#define WINDOW_LARGEUR 1600
#define TAILLE_CARTE_W 100
#define TAILLE_CARTE_H 150
#define GRID_CARTE_WIDTH 6
#define GRID_CARTE_HEIGHT 6

typedef struct emplacement_carte{
    int x;
    int y;
} emplacement_carte;

typedef struct cadrillage{
    struct carte* emplacement[GRID_CARTE_WIDTH][GRID_CARTE_HEIGHT];
}cadrillage;


#endif