#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"

const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 900;
const int NB_CARTES_PAR_LIGNE = 4;      // Nombre de cartes par ligne
const int NB_LIGNES_CARTES = 4;          // Nombre de lignes de cartes
const float CARTES_SCALE = 0.2;          // Facteur de réduction de taille des cartes (0.3 = 30% de la taille d'origine)

void end_sdl(int ok, const char* msg, SDL_Window* window, SDL_Renderer* renderer) {
    char msg_formated[255];
    int l;
    if (!ok) {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");
        SDL_Log(msg_formated, SDL_GetError());
    }
    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

void initialisation(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** bg_texture, SDL_Texture** carte_emplacement) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *window = SDL_CreateWindow("Les colons avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!*window) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    *bg_texture = IMG_LoadTexture(*renderer, "Images/fondblanc.png");
    if (!*bg_texture) {
        printf("Erreur lors du chargement de l'image de fond: %s\n", SDL_GetError());
    }

    *carte_emplacement = IMG_LoadTexture(*renderer, "Images/emp_carte.png");
    if (!*carte_emplacement) {
        printf("Erreur lors du chargement de l'image de carte: %s\n", SDL_GetError());
    }
}

void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void display(SDL_Texture* bg_texture, SDL_Texture* carte_emplacement, SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    // Affichage du background
    render_texture(bg_texture, renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Dimensions des cartes après mise à l'échelle
    int card_width, card_height;
    SDL_QueryTexture(carte_emplacement, NULL, NULL, &card_width, &card_height);
    card_width *= CARTES_SCALE;
    card_height *= CARTES_SCALE;

    // Calcul de l'espacement entre les cartes
    int horizontal_spacing = (WINDOW_WIDTH - NB_CARTES_PAR_LIGNE * card_width) / (NB_CARTES_PAR_LIGNE + 1);
    int vertical_spacing = (WINDOW_HEIGHT - NB_LIGNES_CARTES * card_height) / (NB_LIGNES_CARTES + 1);

    // Affichage de toutes les lignes de cartes
    for (int j = 0; j < NB_LIGNES_CARTES; ++j) {
        for (int i = 0; i < NB_CARTES_PAR_LIGNE; ++i) {
            int x = horizontal_spacing + i * (card_width + horizontal_spacing);
            int y = vertical_spacing + j * (card_height + vertical_spacing);
            render_texture(carte_emplacement, renderer, x, y, card_width, card_height);
        }
    }

    SDL_RenderPresent(renderer);
}

void destruction(SDL_Texture* bg_texture, SDL_Texture* carte_emplacement, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(carte_emplacement);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* bg_texture = NULL;
    SDL_Texture* carte_emplacement = NULL;

    initialisation(&window, &renderer, &bg_texture, &carte_emplacement);

    if (bg_texture == NULL || carte_emplacement == NULL) {
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                destruction(bg_texture, carte_emplacement, window, renderer);
                return 0;
            }
        }

        display(bg_texture, carte_emplacement, renderer);
        SDL_Delay(16); // Pour les 60fps
    }

    destruction(bg_texture, carte_emplacement, window, renderer);

    return 0;
}
