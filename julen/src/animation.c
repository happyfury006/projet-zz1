#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "animation.h"

#define Time 1000
#define speed 5





     /*********************************************************************************************************************/
     /*                              Programme d'exemple de création de rendu + dessin                                    */
     /*********************************************************************************************************************/
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


void animation(SDL_Renderer* renderer)
{  
   SDL_bool running = SDL_TRUE;
   SDL_Event event;
   float angle =0;
   while (running)
   {
      if (SDL_PollEvent(&event))
      {
         if (event.type == SDL_Quit)
         {
            running = SDL_FALSE;
         }
         
      }
      SDL_SetRenderDrawColor(renderer,cos(angle),cos(angle),cos(angle),255);
      angle+=10;   
      
      
   }
   
}
int mainanimation(int argc, char** argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        end_sdl(0, "ERROR SDL INIT", window, renderer);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    int Lwindow = screen.w * 0.66;
    int Hwindow = screen.h * 0.66;

    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    window = SDL_CreateWindow("Animation de rectangle",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              Lwindow, Hwindow,
                              SDL_WINDOW_OPENGL);
    if (window == NULL) {
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
    }

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    }

    int posX = 500;  // Position initiale du rectangle
    int posY = 500;
    SDL_bool monte = SDL_TRUE;    // Déplacement initial vertical vers le haut
    SDL_bool descend = SDL_FALSE; // Pas de déplacement vertical initial vers le bas
    SDL_bool droite = SDL_TRUE;   // Déplacement initial horizontal vers la droite
    SDL_bool gauche = SDL_FALSE;  // Pas de déplacement horizontal initial vers la gauche

    SDL_bool running = SDL_TRUE;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = SDL_FALSE;
            }
            
                      // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, rand()%256, rand()%256, rand()%256, 255);
        SDL_RenderClear(renderer);

        // Dessiner le rectangle à la position actuelle
        drawRect(renderer, posX, posY);

        // Afficher le rendu
        SDL_RenderPresent(renderer);

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

        }


        // Délai pour contrôler la vitesse de l'animation
        SDL_Delay(50);  // Vous pouvez ajuster cette valeur pour changer la vitesse
    }

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}
