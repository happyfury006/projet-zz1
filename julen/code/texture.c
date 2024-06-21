#include "texture.h"
#include "sdl.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>

// void end_sdl(char ok, const char* msg, SDL_Window* window, SDL_Renderer*
// renderer) {
//     char msg_formated[255];
//     int l;

//     if (!ok) {
//         strncpy(msg_formated, msg, 250);
//         l = strlen(msg_formated);
//         strcpy(msg_formated + l, " : %s\n");

//         SDL_Log(msg_formated, SDL_GetError());
//     }

//     if (renderer != NULL) {
//         SDL_DestroyRenderer(renderer);
//         renderer = NULL;
//     }
//     if (window != NULL) {
//         SDL_DestroyWindow(window);
//         window = NULL;
//     }

//     SDL_Quit();

//     if (!ok) {
//         exit(EXIT_FAILURE);
//     }
// }

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

  SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

  destination = window_dimensions;

  SDL_RenderCopy(renderer, my_texture, &source, &destination);
  SDL_RenderPresent(renderer);
  SDL_Delay(2000);
}

void play_with_texture_3(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

  SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

  float zoom = 0.5;
  int nb_it = 200;
  destination.w = source.w * zoom;
  destination.h = source.h * zoom;
  destination.x = (window_dimensions.w - destination.w) / 2;
  // float h = window_dimensions.h - destination.h;
  float w = window_dimensions.w - destination.w;

  float speed = 100.0;

  for (int i = 0; i < nb_it; ++i) {
    destination.x += speed;
    if (destination.x > destination.w) {
      destination.x = 0;
    }

    SDL_RenderClear(renderer);

    SDL_SetTextureAlphaMod(my_texture, 255);
    SDL_RenderCopy(renderer, my_texture, &source, &destination);
    SDL_RenderPresent(renderer);
    SDL_Delay(30);
  }
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *bg = NULL;

  SDL_DisplayMode screen;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

  window = SDL_CreateWindow("Texture Animation", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w, screen.h,
                            SDL_WINDOW_OPENGL);
  if (window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  bg = IMG_LoadTexture(renderer, "./image/desert_tatoine2.jpg");
  if (bg == NULL)
    end_sdl(0, "Echec du chargement de l'image dans la texture", window,
            renderer);

  play_with_texture_3(bg, window, renderer);

  SDL_Delay(3000);

  IMG_Quit();
  SDL_RenderClear(renderer);

  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}
