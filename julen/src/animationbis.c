#include "animationbis.h"
#include "sdl.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define speed 5

// void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer*
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

// void drawRect(SDL_Renderer* renderer, int x, int y) {
//     SDL_Rect rectangle;
//     SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() %
//     256, 255); // Couleur aléatoire rectangle.x = x; rectangle.y = y;
//     rectangle.w = 100;
//     rectangle.h = 100;
//     SDL_RenderFillRect(renderer, &rectangle);
// }

int mainanimationbis(int argc, char **argv) {
  (void)argc;
  (void)argv;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_DisplayMode screen;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    end_sdl(0, "ERROR SDL INIT", window, renderer);
  }

  SDL_GetCurrentDisplayMode(0, &screen);
  int Lwindow = screen.w * 0.66;
  int Hwindow = screen.h * 0.66;

  printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

  window = SDL_CreateWindow("Animation de rectangle", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, Lwindow, Hwindow,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) {
    end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
  }

  int posX = 500; // Position initiale du rectangle
  int posY = 500;
  SDL_bool monte = SDL_TRUE; // Déplacement initial vertical vers le haut
  SDL_bool descend =
      SDL_FALSE; // Pas de déplacement vertical initial vers le bas
  SDL_bool droite = SDL_TRUE; // Déplacement initial horizontal vers la droite
  SDL_bool gauche =
      SDL_FALSE; // Pas de déplacement horizontal initial vers la gauche

  SDL_bool running = SDL_TRUE;
  SDL_Event event;

  srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = SDL_FALSE;
      }
    }

    // Mettre à jour la position du rectangle
    if (monte) {
      posY -= speed;
      if (posY <= 0) {
        monte = SDL_FALSE;
        descend = SDL_TRUE;
      }
    }
    if (descend) {
      posY += speed;
      if (posY + 100 >= Hwindow) {
        descend = SDL_FALSE;
        monte = SDL_TRUE;
      }
    }
    if (droite) {
      posX += speed;
      if (posX + 100 >= Lwindow) {
        droite = SDL_FALSE;
        gauche = SDL_TRUE;
      }
    }
    if (gauche) {
      posX -= speed;
      if (posX <= 0) {
        gauche = SDL_FALSE;
        droite = SDL_TRUE;
      }
    }

    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dessiner le rectangle à la position actuelle
    drawRect(renderer, posX, posY);

    // Afficher le rendu
    SDL_RenderPresent(renderer);

    // Délai pour contrôler la vitesse de l'animation
    SDL_Delay(50); // Vous pouvez ajuster cette valeur pour changer la vitesse
  }

  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}
