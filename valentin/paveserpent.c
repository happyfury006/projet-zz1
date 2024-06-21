#include <SDL2/SDL.h>
#include <stdbool.h>

const int WINDOW_LARGEUR = 800;
const int WINDOW_HAUTEUR = 600;
const int RECT_TAILLE = 50;
const int vit = 5;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(
      "Animation avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Rect rect = {0, (WINDOW_HAUTEUR - RECT_TAILLE) / 2, RECT_TAILLE,
                   RECT_TAILLE};
  SDL_Color couleur = {255, 0, 0, 255}; // Couleur initial : rouge

  bool running = true;
  bool forward = true;

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          // Change la couleur à chaque clique gauche
          couleur.r = rand() % 256;
          couleur.g = rand() % 256;
          couleur.b = rand() % 256;
        }
      }
    }

    if (forward) {
      rect.x += vit;
      if (rect.x + RECT_TAILLE >= WINDOW_LARGEUR) {
        forward = false;
      }
    } else {
      rect.x -= vit;
      if (rect.x <= 0) {
        forward = true;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b,
                           couleur.a);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
