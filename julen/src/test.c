#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "sdl.h"

#define I 10
#define N 10

// SDL_Window* creationwindow(const char* title, int x, int y, int w, int h) {
//     SDL_Window* window = NULL;

//     /* Création de la fenêtre */
//     window = SDL_CreateWindow(
//         title,
//         x, y,
//         w, h,
//         SDL_WINDOW_RESIZABLE
//     );

//     if (window == NULL) {
//         SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());
//         SDL_Quit();
//         exit(EXIT_FAILURE);
//     }

//     return window;
// }

int maintest(int argc, char **argv) {
    (void)argc;
    (void)argv;
    int i = 0;
    char title[12];
    SDL_Window* window[I];

    /* Initialisation de la SDL + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_DisplayMode screen;
    if (SDL_GetCurrentDisplayMode(0, &screen) != 0) {
        SDL_Log("Error : SDL getting display mode - %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    printf("Screen resolution: %dx%d\n", screen.w, screen.h);

    int step_x = screen.w / (I / 2);
    int step_y = screen.h / (I / 2);

    for (i = 0; i < I; i++) {
        sprintf(title, "Window %d", i);
        if (i < I / 2) {
            window[i] = creationwindow(title, i * step_x, 0, 300, 300);
        } else {
            window[i] = creationwindow(title, (i - I / 2) * step_x, screen.h - 300, 300, 300);
        }
    }

    for (i = 0; i < I; i++) {
        int xpos, ypos;
        SDL_GetWindowPosition(window[i], &xpos, &ypos);

        if (i < I / 2) {
            
            ypos += i * step_y;
        } else {
            
            ypos -= (i - I / 2) * step_y;
        }

        SDL_SetWindowPosition(window[i], xpos, ypos);
        SDL_GetWindowPosition(window[i], &xpos, &ypos);
        printf("Fenêtre %d: position après déplacement: (%d, %d)\n", i, xpos, ypos);
    }
   
   int wwindow,hwindow;
   for ( i = 0; i < I; i++)
   {
      SDL_GetWindowSize(window[i],&wwindow,&hwindow);
      SDL_SetWindowSize(window[i],wwindow*1.2,hwindow*1.2);
   }
   
   
    SDL_Delay(5000);

    for (i = 0; i < I; i++) {
        SDL_DestroyWindow(window[i]);
    }

    SDL_Quit();

    return 0;
}
