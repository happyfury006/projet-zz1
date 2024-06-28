#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

// Dimensions de la fenêtre
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Dimensions du rectangle
const int RECT_WIDTH = 100;
const int RECT_HEIGHT = 100;

// Fonction pour afficher du texte
void afficherTexte(SDL_Renderer *renderer, TTF_Font *font, const char *texte,
                   int x, int y) {
  SDL_Color textColor = {0, 0, 0, 255}; // Noir
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, texte, textColor);
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
  SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(textTexture);
}

// Fonction pour afficher une texture centrée sur l'écran
void afficherTextureCentree(SDL_Renderer *renderer, SDL_Texture *texture) {
  int texW, texH;
  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
  SDL_Rect dstRect = {(WINDOW_WIDTH - texW) / 2, (WINDOW_HEIGHT - texH) / 2,
                      texW, texH};
  SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

// Fonction pour gérer le clic et incrémenter le compteur de clics
void gererClic(int *clickCount, int x, int y) {
  if (x >= 0 && x < RECT_WIDTH && y >= 0 && y < RECT_HEIGHT) {
    (*clickCount)++;
    // Réinitialiser à 1 lorsque le compteur atteint 4
    if (*clickCount == 4) {
      *clickCount = 1;
    }
  }
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
    return 1;
  }

  if (TTF_Init() == -1) {
    printf("Erreur d'initialisation de SDL_ttf: %s\n", TTF_GetError());
    SDL_Quit();
    return 1;
  }

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    printf("Erreur d'initialisation de SDL_image: %s\n", IMG_GetError());
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
      "Compteur de clics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Erreur de création du renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  TTF_Font *font = TTF_OpenFont("../Police/arial.ttf", 24);
  if (!font) {
    printf("Erreur de chargement de la police: %s\n", TTF_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  int clickCount = 1; // Initialiser le compteur à 1
  int quit = 0;
  SDL_Event e;

  sitjoueur joueur;
  joueur.compteur_points_joueur =
      0; // Initialiser les points du joueur à partir de la structure

  // Charger la texture à afficher lorsque les points du joueur atteignent 10
  SDL_Texture *victoire_texture =
      IMG_LoadTexture(renderer, "../Images/victoire.png");
  if (!victoire_texture) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        gererClic(&clickCount, x, y);
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
    SDL_RenderClear(renderer);

    SDL_Rect rect = {0, 0, RECT_WIDTH, RECT_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bleu
    SDL_RenderFillRect(renderer, &rect);

    // Afficher le compteur de clics
    char countText[50];
    sprintf(countText, "Phase: %d", clickCount);
    afficherTexte(renderer, font, countText, 10, RECT_HEIGHT + 10);

    // Afficher les points du joueur à partir de la structure
    char pointsText[50];
    sprintf(pointsText, "Points Joueur: %d", joueur.compteur_points_joueur);
    afficherTexte(renderer, font, pointsText, 10, RECT_HEIGHT + 50);

    // Si les points du joueur atteignent 10, afficher la texture centrée
    if (joueur.compteur_points_joueur == 10) {
      afficherTextureCentree(renderer, victoire_texture);
    }

    SDL_RenderPresent(renderer);
  }

  // Libérer la mémoire des ressources
  SDL_DestroyTexture(victoire_texture);
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
