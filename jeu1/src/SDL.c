#include "SDL.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

const int WINDOW_LARGEUR = 1000;
const int WINDOW_HAUTEUR = 800;

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

void render_texture_fullscreen(SDL_Texture *texture, SDL_Renderer *renderer) {
    SDL_Rect destination = {0, 0, WINDOW_LARGEUR, WINDOW_HAUTEUR};
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void render_texture_centered(SDL_Texture *texture, SDL_Renderer *renderer) {
    SDL_Rect source = {0};
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

    SDL_Rect destination = {0};
    destination.w = source.w;
    destination.h = source.h;
    destination.x = (WINDOW_LARGEUR - source.w) / 2;
    destination.y = (WINDOW_HAUTEUR - source.h) / 2;

    SDL_RenderCopy(renderer, texture, &source, &destination);
}

void render_pieces_top_and_bottom(SDL_Texture *pieces[], int piece_count, SDL_Renderer *renderer) {
    SDL_Rect destination = {0};
    int piece_width = WINDOW_LARGEUR / (piece_count / 2);

    for (int i = 0; i < piece_count; i++) {
        SDL_QueryTexture(pieces[i], NULL, NULL, &destination.w, &destination.h);

        if (i < 8) {
            // Placer les pièces 0 à 7 en bas du plateau
            destination.x = i * piece_width + (piece_width - destination.w) / 2;
            destination.y = WINDOW_HAUTEUR - destination.h - 1; // 10 pixels au-dessus du bas de la fenêtre
        } else {
            // Placer les pièces 8 à 15 en haut du plateau
            destination.x = (i - 8) * piece_width + (piece_width - destination.w) / 2;
            destination.y = 1; // 10 pixels en dessous du haut de la fenêtre
        }

        SDL_RenderCopy(renderer, pieces[i], NULL, &destination);
    }
}

void display(SDL_Texture* bgv2_texture, SDL_Texture* bg_texture, SDL_Texture* pieces[], SDL_Window* window, SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    render_texture_fullscreen(bgv2_texture, renderer);
    render_texture_centered(bg_texture, renderer);
    render_pieces_top_and_bottom(pieces, 16, renderer);

    SDL_RenderPresent(renderer);
}

int mainSDL(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Quantik avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *bg_texture;
    SDL_Texture *bgv2_texture;
    SDL_Texture *piece[16] = {NULL};

    bg_texture = IMG_LoadTexture(renderer, "../images/plateau.png");
    bgv2_texture = IMG_LoadTexture(renderer, "../images/fondblanc.png");
    piece[0] = IMG_LoadTexture(renderer, "../images/coneblanc.png");
    piece[2] = IMG_LoadTexture(renderer, "../images/cubeblanc.png");
    piece[4] = IMG_LoadTexture(renderer, "../images/cylindreblanc.png");
    piece[6] = IMG_LoadTexture(renderer, "../images/sphereblanche.png");
    piece[8] = IMG_LoadTexture(renderer, "../images/conenoir.png");
    piece[10] = IMG_LoadTexture(renderer, "../images/cubenoir.png");
    piece[12] = IMG_LoadTexture(renderer, "../images/cylindrenoir.png");
    piece[14] = IMG_LoadTexture(renderer, "../images/spherenoir.png");

    piece[1] = piece[0];
    piece[3] = piece[2];
    piece[5] = piece[4];
    piece[7] = piece[6];
    piece[9] = piece[8];
    piece[11] = piece[10];
    piece[13] = piece[12];
    piece[15] = piece[14];

    if (bg_texture == NULL || bgv2_texture == NULL) {
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }

    display(bgv2_texture, bg_texture, piece, window, renderer);

    SDL_Delay(5000);

    for (int i = 0; i < 16; i++) {
        if (piece[i]) SDL_DestroyTexture(piece[i]);
    }
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bgv2_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}