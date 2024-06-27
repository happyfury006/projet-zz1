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
#define NB_CARTES 22 // Mise à jour du nombre total de cartes
#define WINDOW_HAUTEUR 1200
#define WINDOW_LARGEUR 1600


void init_grille(emplacement_carte grille[GRID_HEIGHT][GRID_WIDTH]) {
    emplacement_carte temp[GRID_HEIGHT][GRID_WIDTH] = {
        { {500, 230}, {600, 230}, {700, 230}, {800, 230} },
        { {500, 380}, {600, 380}, {700, 380}, {800, 380} },
        { {500, 530}, {600, 530}, {700, 530}, {800, 530} },
        { {500, 680}, {600, 680}, {700, 680}, {800, 680} }
    };

    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grille[i][j] = temp[i][j];
        }
    }
}

void init_main_ia(emplacement_carte grille_ia[GRID1_HEIGHT][GRID1_WIDTH]) {
    emplacement_carte temp[GRID1_HEIGHT][GRID1_WIDTH] = {
        { {350, 10}, {450, 10}, {550, 10}, {650, 10}, {750, 10}, {850, 10} }
    };

    for (int i = 0; i < GRID1_WIDTH; ++i) {
        grille_ia[0][i] = temp[0][i];
    }
}

int init_cartes(tab_carte_construction* cartes, SDL_Renderer* renderer, const char* image_paths[], emplacement_carte grille[GRID_HEIGHT][GRID_WIDTH], emplacement_carte grille1[GRID1_HEIGHT][GRID1_WIDTH]) {
    SDL_Texture* texture_routeA = IMG_LoadTexture(renderer, image_paths[9]);
    if (!texture_routeA) {
        printf("Erreur IMG_LoadTexture pour routeA: %s\n", IMG_GetError());
        return 0;
    }

    SDL_Texture* texture_chevalierA = IMG_LoadTexture(renderer, image_paths[2]);
    if (!texture_chevalierA) {
        printf("Erreur IMG_LoadTexture pour chevalierA: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        return 0;
    }

    SDL_Texture* texture_ville = IMG_LoadTexture(renderer, image_paths[7]);
    if (!texture_ville) {
        printf("Erreur IMG_LoadTexture pour ville: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        return 0;
    }

    SDL_Texture* texture_developpement = IMG_LoadTexture(renderer, image_paths[10]);
    if (!texture_developpement) {
        printf("Erreur IMG_LoadTexture pour développement: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SDL_DestroyTexture(texture_ville);
        return 0;
    }

    SDL_Texture* texture_emp_carte = IMG_LoadTexture(renderer, image_paths[11]);
    if (!texture_emp_carte) {
        printf("Erreur IMG_LoadTexture pour emp_carte: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        return 0;
    }

    cartes->tab_carte_construction[0] = (carte*)malloc(sizeof(carte));
    cartes->tab_carte_construction[0]->texture = texture_routeA;
    cartes->tab_carte_construction[0]->rect.x = grille[1][0].x;
    cartes->tab_carte_construction[0]->rect.y = grille[1][0].y;
    cartes->tab_carte_construction[0]->rect.w = 100;
    cartes->tab_carte_construction[0]->rect.h = 150;

    cartes->tab_carte_construction[1] = (carte*)malloc(sizeof(carte));
    cartes->tab_carte_construction[1]->texture = texture_chevalierA;
    cartes->tab_carte_construction[1]->rect.x = grille[1][1].x;
    cartes->tab_carte_construction[1]->rect.y = grille[1][1].y;
    cartes->tab_carte_construction[1]->rect.w = 100;
    cartes->tab_carte_construction[1]->rect.h = 150;

    cartes->tab_carte_construction[2] = (carte*)malloc(sizeof(carte));
    cartes->tab_carte_construction[2]->texture = texture_ville;
    cartes->tab_carte_construction[2]->rect.x = grille[1][2].x;
    cartes->tab_carte_construction[2]->rect.y = grille[1][2].y;
    cartes->tab_carte_construction[2]->rect.w = 100;
    cartes->tab_carte_construction[2]->rect.h = 150;

    cartes->tab_carte_construction[3] = (carte*)malloc(sizeof(carte));
    cartes->tab_carte_construction[3]->texture = texture_developpement;
    cartes->tab_carte_construction[3]->rect.x = grille[1][3].x;
    cartes->tab_carte_construction[3]->rect.y = grille[1][3].y;
    cartes->tab_carte_construction[3]->rect.w = 100;
    cartes->tab_carte_construction[3]->rect.h = 150;

    int index = 4;
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (!(i == 1 && j < 4)) {
                cartes->tab_carte_construction[index] = (carte*)malloc(sizeof(carte));
                cartes->tab_carte_construction[index]->texture = texture_emp_carte;
                cartes->tab_carte_construction[index]->rect.x = grille[i][j].x;
                cartes->tab_carte_construction[index]->rect.y = grille[i][j].y;
                cartes->tab_carte_construction[index]->rect.w = 100;
                cartes->tab_carte_construction[index]->rect.h = 150;
                ++index;
            }
        }
    }

    for (int i = 0; i < GRID1_HEIGHT; ++i) {
        for (int j = 0; j < GRID1_WIDTH; ++j) {
            cartes->tab_carte_construction[index] = (carte*)malloc(sizeof(carte));
            cartes->tab_carte_construction[index]->texture = texture_emp_carte;
            cartes->tab_carte_construction[index]->rect.x = grille1[i][j].x;
            cartes->tab_carte_construction[index]->rect.y = grille1[i][j].y;
            cartes->tab_carte_construction[index]->rect.w = 100;
            cartes->tab_carte_construction[index]->rect.h = 150;
            ++index;
        }
    }

    return 1;
}

void display(SDL_Texture* bg_texture, tab_carte_construction* cartes, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

    for (int i = 0; i < NB_CARTES; ++i) {
        if (cartes->tab_carte_construction[i]) {
            SDL_RenderCopy(renderer, cartes->tab_carte_construction[i]->texture, NULL, &cartes->tab_carte_construction[i]->rect);
            printf("Carte %d : x = %d, y = %d, w = %d, h = %d\n", i, cartes->tab_carte_construction[i]->rect.x, cartes->tab_carte_construction[i]->rect.y, cartes->tab_carte_construction[i]->rect.w, cartes->tab_carte_construction[i]->rect.h);
        } else {
            printf("Carte %d est NULL\n", i);
        }
    }

    SDL_RenderPresent(renderer);
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

    *window = SDL_CreateWindow("Cartes SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 1200, 0);
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

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!init(&window, &renderer)) {
        return 1;
    }

    const char *image_paths[NB_CARTES] = {
        "../Images/fondblanc.png",
        "../Images/ressource_argile.png",
        "../Images/chevalierA.png",
        "../Images/colonie.png",
        "../Images/dos.png",
        "../Images/ressource_ble.png",
        "../Images/ressource_bois.png",
        "../Images/ville.png",
        "../Images/ressource_minerai.png",
        "../Images/routeA.png",
        "../Images/developpement_eglise.png",
        "../Images/emp_carte.png",
    };

    emplacement_carte grille[GRID_HEIGHT][GRID_WIDTH];
    init_grille(grille);

    emplacement_carte grille_ia[GRID1_HEIGHT][GRID1_WIDTH];
    init_main_ia(grille_ia);

    tab_carte_construction cartes;
    memset(&cartes, 0, sizeof(tab_carte_construction));

    if (!init_cartes(&cartes, renderer, image_paths, grille, grille_ia)) {
        cleanup(window, renderer, &cartes);
        return 1;
    }

    SDL_Texture* bg_texture = IMG_LoadTexture(renderer, image_paths[0]);
    if (!bg_texture) {
        printf("Erreur IMG_LoadTexture pour bg_texture: %s\n", IMG_GetError());
        cleanup(window, renderer, &cartes);
        return 1;
    }

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        display(bg_texture, &cartes, renderer);
    }

    SDL_DestroyTexture(bg_texture);
    cleanup(window, renderer, &cartes);

    return 0;
}
