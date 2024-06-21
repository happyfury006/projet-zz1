#include "sprite.h"
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
// Nécessaire pour la fonction IMG_Load
// Penser au flag -lsdl2_image à la compilation
//...

void animationparallax(SDL_Texture *bg_texture, SDL_Texture *anakin_texture,
                       SDL_Texture *sebulba_texture,
                       SDL_Texture *destroyer_texture, SDL_Window *window,
                       SDL_Renderer *renderer) {
  SDL_Rect source_bg = {0}, window_dimensions = {0}, destination_bg[3] = {{0}};
  SDL_Rect source_anakin = {0}, destination_anakin = {0};
  SDL_Rect source_sebulba = {0}, destination_sebulba = {0};
  SDL_Rect source_destroyer = {0}, destination_destroyer = {0};

  SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
  SDL_QueryTexture(bg_texture, NULL, NULL, &source_bg.w, &source_bg.h);
  SDL_QueryTexture(anakin_texture, NULL, NULL, &source_anakin.w,
                   &source_anakin.h);
  SDL_QueryTexture(sebulba_texture, NULL, NULL, &source_sebulba.w,
                   &source_sebulba.h);
  SDL_QueryTexture(destroyer_texture, NULL, NULL, &source_destroyer.w,
                   &source_destroyer.h);

  source_bg.w *= 1;
  source_bg.h *= 0.8;
  // Initialisation de la position de l'image de fond
  for (int i = 0; i < 3; i++) {
    destination_bg[i].w = source_bg.w;
    destination_bg[i].h = source_bg.h;
    destination_bg[i].x = i * source_bg.w;
    destination_bg[i].y = 0; // Start from the top of the window
  }
  // Initialisation de la position de l'image de anakin
  destination_anakin.w = source_anakin.w;
  destination_anakin.h = source_anakin.h;
  destination_anakin.x =
      (window_dimensions.w - destination_anakin.w) / 2; // Center horizontally
  destination_anakin.y = (window_dimensions.h) * 0.7;   // vertically
  // Initialisation de la position de l'image de sebulba
  destination_sebulba.w = source_sebulba.w;
  destination_sebulba.h = source_sebulba.h;
  destination_sebulba.x =
      (window_dimensions.w - destination_sebulba.w) * 2; // Center horizontally
  destination_sebulba.y = (window_dimensions.h) * 0.6;   //  vertically
  // Initialisation de la position de l'image de destroyer
  destination_destroyer.w = source_destroyer.w;
  destination_destroyer.h = source_destroyer.h;
  destination_destroyer.x =
      (window_dimensions.w - destination_destroyer.w); // horizontally Right
  destination_destroyer.y = 100;                       //  vertically

  float speedbg = 10.0;
  float speedanakin = 1.0;
  float speedsebulba = 5.0;
  float speedestroyer = 0.0;

  int direction = 0; // 0: right, 1: down, 2: left, 3: up
  int initial_x = destination_anakin.x;
  //  int initial_y = destination_anakin.y;
  SDL_bool running = SDL_TRUE;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = SDL_FALSE;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          destination_anakin.y -= 10 * speedanakin;
          break;
        case SDLK_DOWN:
          destination_anakin.y += 10 * speedanakin;
          break;
        case SDLK_LEFT:
          destination_anakin.x -= 10 * speedanakin;
          break;
        case SDLK_RIGHT:
          destination_anakin.x += 10 * speedanakin;
          break;
        }
        initial_x = destination_anakin.x;
        //  initial_y = destination_anakin.y;
      }
    }

    // Animation vaiseau anakin en petit rectangle au tour de sa position
    // initiale qui change
    switch (direction) {
    case 0: // Move right
      destination_anakin.x += 2 * speedanakin;
      if (destination_anakin.x >= initial_x + 5) {
        direction = 1;
      }
      break;
    // case 1: // Move down
    //     destination_anakin.y += speedanakin;
    //     if (destination_anakin.y >= initial_y + 2) {
    //         direction = 2;
    //     }
    //     break;
    case 1: // Move left
      destination_anakin.x -= speedanakin;
      if (destination_anakin.x <= initial_x - 5) {
        direction = 0;
      }
      break;
      // case 3: // Move up
      //     destination_anakin.y -= speedanakin;
      //     if (destination_anakin.y <= initial_y - 2) {
      //         direction = 0;
      //     }
      //     break;
    }

    for (int i = 0; i < 3; i++) {
      destination_bg[i].x -= speedbg;
      if (destination_bg[i].x <= -destination_bg[i].w) {
        destination_bg[i].x =
            destination_bg[(i + 2) % 3].x + destination_bg[(i + 2) % 3].w;
      }
    }
    // Animation de sebulba
    destination_sebulba.x -= speedsebulba;

    // Animation de destroyer
    destination_destroyer.x -= speedestroyer;

    SDL_RenderClear(renderer);
    //   SDL_SetTextureAlphaMod(anakin_texture,  0);
    for (int i = 0; i < 3; i++) {
      SDL_RenderCopy(renderer, bg_texture, &source_bg, &destination_bg[i]);
    }
    SDL_RenderCopy(renderer, destroyer_texture, &source_destroyer,
                   &destination_destroyer);
    SDL_RenderCopy(renderer, sebulba_texture, &source_sebulba,
                   &destination_sebulba);
    SDL_RenderCopy(renderer, anakin_texture, &source_anakin,
                   &destination_anakin);
    SDL_RenderPresent(renderer);
    SDL_Delay(10); // Adjust delay as needed for desired animation speedbg
  }
}

int mainsprite(int argc, char **argv) {
  (void)argc;
  (void)argv;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *bg = NULL;
  SDL_Texture *anakin = NULL;
  SDL_Texture *destroyer = NULL;
  SDL_Texture *sebulba = NULL;

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

  bg = IMG_LoadTexture(renderer, "./image/desert_tatoine22.png");
  if (bg == NULL)
    end_sdl(0, "Echec du chargement de l'image dans la texture", window,
            renderer);

  anakin = IMG_LoadTexture(renderer, "./image/file.png");
  if (anakin == NULL)
    end_sdl(0, "Echec du chargement de l'image de premier plan dans la texture",
            window, renderer);
  destroyer = IMG_LoadTexture(renderer, "./image/destroyer.png");
  if (destroyer == NULL)
    end_sdl(0, "Echec du chargement de l'image de premier plan dans la texture",
            window, renderer);
  sebulba = IMG_LoadTexture(renderer, "./image/sebulba.png");
  if (sebulba == NULL)
    end_sdl(0, "Echec du chargement de l'image de premier plan dans la texture",
            window, renderer);

  animationparallax(bg, anakin, sebulba, destroyer, window, renderer);

  SDL_Delay(3000);

  IMG_Quit();
  SDL_RenderClear(renderer);

  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}
