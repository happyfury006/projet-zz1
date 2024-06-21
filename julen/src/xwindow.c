#include <SDL2/SDL.h>
#include <stdio.h>
#include "xwindow.h"
#include "sdl.h"


#include <stdlib.h>

#define I 10
#define N 5

// void SDL_SetWindowPosition(SDL_Window * window, int x, int y);
// void SDL_GetWindowPosition(SDL_Window * window, int *x, int *y);
// int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode);

// SDL_Window* creationwindow(const char* title, int x, int y, int w, int h) {
//     SDL_Window * window = NULL;

//     /* Initialisation de la SDL  + gestion de l'échec possible */
//     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//         SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
//         exit(EXIT_FAILURE);
//     }

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
//     } else {
//         return window;
//     }
// }

int mainxwindow(int argc, char **argv) {
    (void)argc;
    (void)argv;

    char title[12];
    SDL_Window *window[I];

    for (int i = 0; i < I; i++) {
        sprintf(title, "Window %d", i);
        if (i < I / 2) {
            window[i] = creationwindow(title, i * 400, 0, 300, 300);
        } else {
            window[i] = creationwindow(title, (i - I / 2) * 400, 800, 300, 300);
        }
    }

    /* Deplacement des fenetres */
    SDL_DisplayMode screen;
    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Screen resolution: %dx%d\n", screen.w, screen.h);

    int step = screen.h / N;

    for (int i = 0; i < I; i++) {
        int xpos, ypos;

        SDL_GetWindowPosition(window[i], &xpos, &ypos);
        printf("Fenêtre %d: position avant déplacement: (%d, %d)\n", i, xpos, ypos);

        if (i < I / 2) {
            SDL_SetWindowPosition(window[i], xpos, ypos + step*i);
        } else {
            SDL_SetWindowPosition(window[i], xpos, ypos - step*( i-I/2));
        }

        SDL_GetWindowPosition(window[i], &xpos, &ypos);
        printf("Fenêtre %d: position après déplacement: (%d, %d)\n", i, xpos, ypos);
    }

    SDL_Delay(5000);

    /* Fermetures des fenetres */
    for (int i = 0; i < I; i++) {
        SDL_DestroyWindow(window[i]);
    }

    SDL_Quit();

    return 0;
}
