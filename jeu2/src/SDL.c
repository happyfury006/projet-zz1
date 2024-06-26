#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"

#define GRID_WIDTH 4
#define GRID_HEIGHT 4
#define GRID1_WIDTH 6
#define GRID1_HEIGHT 1
#define NB_CARTES 13



void init_grille(emplacement_carte grille[GRID_HEIGHT][GRID_WIDTH]) {
    emplacement_carte temp[GRID_HEIGHT][GRID_WIDTH] = 
    {
        {{400, 230}, {500, 230}, {600, 230}, {700, 230}},
        {{400, 380}, {500, 380}, {600, 380}, {700, 380}},
        {{400, 530}, {500, 530}, {600, 530}, {700, 530}},
        {{400, 680}, {500, 680}, {600, 680}, {700, 680}}
    };

    // Copier les valeurs dans le tableau passé en paramètre
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grille[i][j] = temp[i][j];
        }
    }
}

void init_main_joueur(emplacement_carte grille[GRID1_HEIGHT][GRID1_WIDTH]) {
    emplacement_carte temp[GRID1_HEIGHT][GRID1_WIDTH] =
    {
        {{350, 800}, {450, 800}, {550, 800}, {650, 800}, {750, 800}, {850, 800}}
    };
    for (int i = 0; i < GRID1_WIDTH; ++i) 
    {
        for (int j = 0; j < GRID1_HEIGHT; ++j) 
        {
            grille[j][i] = temp[j][i];
        }
    }
}

void init_main_ia(emplacement_carte grille[GRID1_HEIGHT][GRID1_WIDTH]) {
    emplacement_carte temp[GRID1_HEIGHT][GRID1_WIDTH] =
    {
        {{350, 10}, {450, 10}, {550, 10}, {650, 10}, {750, 10}, {850, 10}}
    };

    for (int i = 0; i < GRID1_WIDTH; ++i) {
        for (int j = 0; j < GRID1_HEIGHT; ++j) {
            grille[j][i] = temp[j][i];
        }
    }
}

int init_cartes(tab_carte_construction* cartes, SDL_Renderer* renderer, const char* image_paths[], emplacement_carte grille[GRID_HEIGHT][GRID_WIDTH]) {
    // Charger les textures pour routeA et chevalier
    SDL_Texture* texture_routeA = IMG_LoadTexture(renderer, "../Images/routeA.png");
    if (!texture_routeA) {
        printf("Erreur IMG_LoadTexture pour routeA: %s\n", IMG_GetError());
        return 0;
    }
    SDL_Texture* texture_chevalier = IMG_LoadTexture(renderer, "../Images/chevalierA.png");
    if (!texture_chevalier) {
        printf("Erreur IMG_LoadTexture pour chevalierA: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        return 0;
    }

    // Positions spécifiques pour routeA
    int routeA_positions[3][2] = {{0, 0}, {1, 0}, {3, 0}};
    // Positions spécifiques pour chevalier
    int chevalier_positions[3][2] = {{0, 1}, {1, 1}, {3, 1}};

    // Assigner les textures "routeA" aux positions spécifiées
    for (int i = 0; i < 3; ++i) {
        int x = routeA_positions[i][0];
        int y = routeA_positions[i][1];
        cartes->tab_carte_construction[i] = (carte*)malloc(sizeof(carte));
        cartes->tab_carte_construction[i]->texture = texture_routeA;
        cartes->tab_carte_construction[i]->rect.x = grille[x][y].x;
        cartes->tab_carte_construction[i]->rect.y = grille[x][y].y;
        cartes->tab_carte_construction[i]->rect.w = 100; // Largeur arbitraire
        cartes->tab_carte_construction[i]->rect.h = 150; // Hauteur arbitraire
    }

    // Assigner les textures "chevalier" aux positions spécifiées
    for (int i = 0; i < 3; ++i) {
        int x = chevalier_positions[i][0];
        int y = chevalier_positions[i][1];
        cartes->tab_carte_construction[i + 3] = (carte*)malloc(sizeof(carte));
        cartes->tab_carte_construction[i + 3]->texture = texture_chevalier;
        cartes->tab_carte_construction[i + 3]->rect.x = grille[x][y].x;
        cartes->tab_carte_construction[i + 3]->rect.y = grille[x][y].y;
        cartes->tab_carte_construction[i + 3]->rect.w = 100; // Largeur arbitraire
        cartes->tab_carte_construction[i + 3]->rect.h = 150; // Hauteur arbitraire
    }

    // Charger les textures restantes
    for (int i = 6; i < NB_CARTES; ++i) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, image_paths[i]);
        if (!texture) {
            printf("Erreur IMG_LoadTexture pour image %d: %s\n", i, IMG_GetError());
            return 0;
        }
        cartes->tab_carte_construction[i] = (carte*)malloc(sizeof(carte));
        cartes->tab_carte_construction[i]->texture = texture;
        cartes->tab_carte_construction[i]->rect.x = grille[i % GRID_WIDTH][i / GRID_WIDTH].x;
        cartes->tab_carte_construction[i]->rect.y = grille[i % GRID_WIDTH][i / GRID_WIDTH].y;
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

void cleanup(SDL_Window* window, SDL_Renderer* renderer, tab_carte_construction* cartes, SDL_Texture* dos_carte_textures[], int dos_carte_count) {
    destroy_cartes(cartes);
    for (int i = 0; i < dos_carte_count; ++i) {
        if (dos_carte_textures[i]) {
            SDL_DestroyTexture(dos_carte_textures[i]);
        }
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
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
        "../Images/ressource_argile.png",
        "../Images/chevalierA.png",
        "../Images/colonie.png",
        "../Images/dos.png",
        "../Images/ressource_ble.png",
        "../Images/ressource_bois.png",
        "../Images/ressource_minerai.png",
        "../Images/ressource_mouton.png",
        "../Images/routeA.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
        "../Images/emp_carte.png",
    };

    // Créer et initialiser une grille de positions
    emplacement_carte grille[GRID_HEIGHT][GRID_WIDTH];
    init_grille(grille);

    // Créer et initialiser une grille de positions pour l'IA
    emplacement_carte grille_ia[GRID1_HEIGHT][GRID1_WIDTH];
    init_main_ia(grille_ia);

    // Créer une structure de cartes
    tab_carte_construction cartes;

    if (!init_cartes(&cartes, renderer, image_paths, grille)) {
        cleanup(window, renderer, &cartes, NULL, 0);
        return 1;
    }

    // Charger la texture du dos_carte
    SDL_Texture* dos_carte_texture = IMG_LoadTexture(renderer, image_paths[4]);
    if (!dos_carte_texture) {
        printf("Erreur IMG_LoadTexture pour dos_carte: %s\n", IMG_GetError());
        cleanup(window, renderer, &cartes, NULL, 0);
        return 1;
    }

    // Charger la texture du background
    SDL_Texture *background_texture = IMG_LoadTexture(renderer, image_paths[0]);
    if (!background_texture) {
        printf("Erreur IMG_LoadTexture pour le background: %s\n", IMG_GetError());
        cleanup(window, renderer, &cartes, &dos_carte_texture, 1);
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

        // Afficher toutes les cartes
        for (int i = 0; i < NB_CARTES; ++i) {
            if (cartes.tab_carte_construction[i]) {
                SDL_RenderCopy(renderer, cartes.tab_carte_construction[i]->texture, NULL, &cartes.tab_carte_construction[i]->rect);
            }
        }

        // Afficher les cartes de dos_carte de l'IA
        for (int i = 0; i < GRID1_WIDTH; ++i) {
            SDL_Rect rect = {grille_ia[0][i].x, grille_ia[0][i].y, 100, 150}; // Taille arbitraire
            SDL_RenderCopy(renderer, dos_carte_texture, NULL, &rect);
        }

        SDL_RenderPresent(renderer);
    }

    // Libérer les ressources
    SDL_DestroyTexture(background_texture);
    cleanup(window, renderer, &cartes, &dos_carte_texture, 1);

    return 0;
}
