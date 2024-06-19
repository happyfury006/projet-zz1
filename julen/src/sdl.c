#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include "sdl.h"

void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
          char const* msg,                                       // message à afficher
          SDL_Window* window,                                    // fenêtre à fermer
          SDL_Renderer* renderer) {                              // renderer à fermer
       char msg_formated[255];                                            
       int l;                                                     
                                            
       if (!ok) {                                                        // Affichage de ce qui ne va pas
     strncpy(msg_formated, msg, 250);                                         
     l = strlen(msg_formated);                                            
     strcpy(msg_formated + l, " : %s\n");                                     
                                            
     SDL_Log(msg_formated, SDL_GetError());                                   
       }                                                          
                                            
       if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
     SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
     renderer = NULL;
       }
       if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
     SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
     window= NULL;
       }
                                            
       SDL_Quit();                                                    
                                            
       if (!ok) {                                       // On quitte si cela ne va pas            
     exit(EXIT_FAILURE);                                                  
       }                                                          
     } 
void drawRect(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect rectangle;
    SDL_SetRenderDrawColor(renderer, 250, 0, 0, 255);
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = 100;
    rectangle.h = 100;
    SDL_RenderFillRect(renderer, &rectangle);
}

SDL_Window* creationwindow(const char* title, int x, int y, int w, int h) {
    SDL_Window* window = NULL;

    /* Création de la fenêtre */
    window = SDL_CreateWindow(
        title,
        x, y,
        w, h,
        SDL_WINDOW_RESIZABLE
    );

    if (window == NULL) {
        SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return window;
}