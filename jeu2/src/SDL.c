#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"

#define GRID_WIDTH 4
#define GRID_HEIGHT 4
#define NB_CARTES 13


void init_grille(emplacement_carte grille[GRID_WIDTH][GRID_HEIGHT]) {
    emplacement_carte temp[GRID_WIDTH][GRID_HEIGHT] = 
    {
        {{419, 230}, {562, 230}, {703, 230}, {848, 230}},
        {{419, 380}, {562, 380}, {703, 380}, {848, 380}},
        {{419, 530}, {562, 530}, {703, 530}, {848, 530}},
        {{419, 680}, {562, 680}, {703, 680}, {848, 680}}
    };

    // Copier les valeurs dans le tableau passé en paramètre
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            grille[i][j] = temp[i][j];
        }
    }
}

int init_cartes(tab_carte_construction* cartes, SDL_Renderer* renderer, const char* image_paths[], emplacement_carte grille[GRID_WIDTH][GRID_HEIGHT]) {
    
    for (int i = 0; i < NB_CARTES; ++i) {
        cartes->tab_carte_construction[i] = (carte*)malloc(sizeof(carte));
        if (!cartes->tab_carte_construction[i]) {
            printf("Erreur de malloc pour la carte %d\n", i);
            return 0;
        }

        cartes->tab_carte_construction[i]->texture = IMG_LoadTexture(renderer, image_paths[i]);
        if (!cartes->tab_carte_construction[i]->texture) {
            printf("Erreur IMG_LoadTexture: %s\n", IMG_GetError());
            return 0;
        }

        cartes->tab_carte_construction[i]->type = i % 2;  // Par exemple, alternance entre route et chevalier
        cartes->tab_carte_construction[i]->nbr_points = i + 1; // Par exemple, un nombre de points arbitraire
        cartes->tab_carte_construction[i]->rect.x = grille[i % GRID_WIDTH][i / GRID_WIDTH].x; // Position basée sur la grille
        cartes->tab_carte_construction[i]->rect.y = grille[i % GRID_WIDTH][i / GRID_WIDTH].y; // Position basée sur la grille
        cartes->tab_carte_construction[i]->rect.w = 100; // Largeur arbitraire
        cartes->tab_carte_construction[i]->rect.h = 150; // Hauteur arbitraire
    }
    return 1;
}

void destroy_cartes(tab_carte_construction* cartes) {
    for (int i = 0; i < NB_CARTES; ++i) {
        if (cartes->tab_carte_construction[i]) {
            if (cartes->tab_carte_construction[i]->texture) {
                SDL_DestroyTexture(cartes->tab_carte_construction[i]->texture);
            }
            free(cartes->tab_carte_construction[i]);
        }
    }
}

int init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur IMG_Init: %s\n", IMG_GetError());
        SDL_Quit();
        return 0;
    }

    *window = SDL_CreateWindow("Cartes SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1300, 900, 0);
    if (!*window) {
        printf("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        IMG_Quit();
        SDL_Quit();
        return 0;
    }

    return 1;
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer, tab_carte_construction* cartes) {
    destroy_cartes(cartes);
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

int mainSDL(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!init(&window, &renderer)) {
        return 1;
    }

    // Chemins vers vos images
    const char *image_paths[NB_CARTES] = {
        "../Images/fondblanc.png",
        "../Images/argile.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
    };

    // Créer et initialiser une grille de positions
    emplacement_carte grille[GRID_WIDTH][GRID_HEIGHT];
    init_grille(grille);

    // Créer une structure de cartes
    tab_carte_construction cartes;

    if (!init_cartes(&cartes, renderer, image_paths, grille)) {
        cleanup(window, renderer, &cartes);
        return 1;
    }

    // Charger la texture du background
    SDL_Texture *background_texture = IMG_LoadTexture(renderer, image_paths[0]);
    if (!background_texture) {
        printf("Erreur IMG_LoadTexture pour le background: %s\n", IMG_GetError());
        cleanup(window, renderer, &cartes);
        return 1;
    }

    // Boucle principale
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);

        // Afficher le background sur toute la fenêtre
        SDL_Rect dest_rect = {0, 0, 1300, 900};
        SDL_RenderCopy(renderer, background_texture, NULL, &dest_rect);

        // Afficher la première carte en arrière-plan
        if (cartes.tab_carte_construction[0]) {
            SDL_RenderCopy(renderer, cartes.tab_carte_construction[0]->texture, NULL, &cartes.tab_carte_construction[0]->rect);
        }

        // Afficher les autres cartes sur l
    
        for (int i = 1; i < NB_CARTES; ++i) {
            SDL_RenderCopy(renderer, cartes.tab_carte_construction[i]->texture, NULL, &cartes.tab_carte_construction[i]->rect);
        }

        SDL_RenderPresent(renderer);
    }

    // Libérer les ressources
    SDL_DestroyTexture(background_texture);
    cleanup(window, renderer, &cartes);

    return 0;
}