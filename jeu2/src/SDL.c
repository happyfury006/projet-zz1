#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"

const int WINDOW_LARGEUR = 1300;
const int WINDOW_HAUTEUR = 900;

void end_sdl(int ok, const char* msg, SDL_Window* window, SDL_Renderer* renderer) 
{
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

void initialisation(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* bg_texture, SDL_Texture* carte_emplacement) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Les colons avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
    if (!window) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    bg_texture = IMG_LoadTexture(renderer, "../Images/fondblanc.png");
    carte_emplacement = IMG_LoadTexture(renderer, "../Images/emplacement_carte.png");
}

void render_extra_textures(SDL_Texture* texture1, SDL_Texture* texture2, SDL_Renderer *renderer) {
    SDL_Rect source1 = {0}, source2 = {0};
    SDL_QueryTexture(texture1, NULL, NULL, &source1.w, &source1.h);
    SDL_QueryTexture(texture2, NULL, NULL, &source2.w, &source2.h);

    SDL_Rect destination1 = {0};
    destination1.w = source1.w;
    destination1.h = source1.h;
    destination1.x = 0;
    destination1.y = 110;

    SDL_Rect destination2 = {0};
    destination2.w = source2.w;
    destination2.h = source2.h;
    destination2.x = WINDOW_LARGEUR - destination2.w;
    destination2.y = WINDOW_HAUTEUR - destination2.h - 110;

    SDL_RenderCopy(renderer, texture1, &source1, &destination1);
    SDL_RenderCopy(renderer, texture2, &source2, &destination2);
}

void display(SDL_Texture* extra_texture1, SDL_Texture* extra_texture2, SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    render_extra_textures(extra_texture1, extra_texture2, renderer);
    SDL_RenderPresent(renderer);
}

void destruction(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyTexture(texture);
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

    initialisation(window, renderer, bg_texture, carte_emplacement);

    if (bg_texture == NULL || carte_emplacement == NULL) {
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }

    // int selected_piece = -1;
    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // handle_events(&event, pieces, 16, &selected_piece, tableau);
            display(carte_emplacement, NULL, renderer);
            SDL_Delay(16); // Pour les 60fps
        }
    }

    destruction(carte_emplacement, window, renderer);

    return 0;
}
