#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#define SIZE 400 

/************************************/
/*        Exercice X fenêtré        */
/************************************/

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SDL_Window 
    *window_1 = NULL,                     // Future fenêtre de gauche
    *window_2 = NULL,
    *window_3 = NULL,
    *window_4 = NULL;  

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    SDL_DisplayMode display_mode;
    if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) 
    {
        fprintf(stderr, "SDL_GetCurrentDisplayMode Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int width = display_mode.w;
    int height = display_mode.h;
    int x;int y;int taille;
    
    /* Création de la fenêtre du coin haut gauche */
    window_1 = SDL_CreateWindow(
    "Fenêtre coin haut gauche",                    // codage en utf8, donc accents possibles
    0, 0,                                  // coin haut gauche en haut gauche de l'écran
    SIZE, SIZE,                              // largeur = 400, hauteur = 300
    SDL_WINDOW_RESIZABLE);                 // redimensionnable

    if (window_1 == NULL) 
    {
        SDL_Log("Error : SDL window 1 creation - %s\n", 
        SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }


    /* Création de la fenêtre du coin bas gauche */
    window_2 = SDL_CreateWindow(
    "Fenêtre coin bas gauche",                    // codage en utf8, donc accents possibles
    0, height,                                  // coin haut gauche en haut gauche de l'écran
    SIZE, SIZE,                              // largeur = 400, hauteur = 300
    SDL_WINDOW_RESIZABLE);                 // redimensionnable

    if (window_2 == NULL) 
    {
        SDL_Log("Error : SDL window 2 creation - %s\n", 
        SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre du coin bas droit */
    window_3 = SDL_CreateWindow(
    "Fenêtre coin bas droit",                    // codage en utf8, donc accents possibles
    width, height,                                  // coin haut gauche en haut gauche de l'écran
    SIZE, SIZE,                              // largeur = 400, hauteur = 300
    SDL_WINDOW_RESIZABLE);                 // redimensionnable

    if (window_3 == NULL) 
    {
        SDL_Log("Error : SDL window 3 creation - %s\n", 
        SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre du coin haut droit */
    window_4 = SDL_CreateWindow(
    "Fenêtre coin haut droit",                    // codage en utf8, donc accents possibles
    width, 0,                                  // coin haut gauche en haut gauche de l'écran
    SIZE, SIZE,                              // largeur = 400, hauteur = 300
    SDL_WINDOW_RESIZABLE);                 // redimensionnable

    if (window_4 == NULL) 
    {
        SDL_Log("Error : SDL window 4 creation - %s\n", 
        SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }



    // Simulation d'un délai de 20 ms
    SDL_Delay(1000);

    // Faire "clignoter" les fenetres
    for(int i=0; i<3;i++)
    {
        SDL_HideWindow(window_1);
        SDL_HideWindow(window_2);
        SDL_HideWindow(window_3);
        SDL_HideWindow(window_4);
        SDL_Delay(50);
        SDL_ShowWindow(window_1);
        SDL_ShowWindow(window_2);
        SDL_ShowWindow(window_3);
        SDL_ShowWindow(window_4);
    }

    //deplacement des fenetres
    x=0;
    while(x<width-SIZE)
    {
        x+=30;
        SDL_SetWindowPosition(window_1,x,0);
        SDL_SetWindowPosition(window_2,x,height);
    }
    SDL_Delay(10);
    x=width;
    while(x+SIZE > 0)
    {
        x-=30;
        SDL_SetWindowPosition(window_3,x,height);
        SDL_SetWindowPosition(window_4,x,0);
    }
    SDL_Delay(10);
    y=0;
    while(y<height-SIZE)
    {
        y+=30;
        SDL_SetWindowPosition(window_1,0,y);
        SDL_SetWindowPosition(window_4,width,y);
    }
    SDL_Delay(100);
    y=height;
    while(y+SIZE > 0)
    {
        y-=30;
        SDL_SetWindowPosition(window_2,0,y);
        SDL_SetWindowPosition(window_3,width,y);
    }


    //agrandit une fenetre
    x=SIZE;y=SIZE;
    while(x<width)
    {
        x+=8;
        SDL_SetWindowSize(window_4,x,y);
        SDL_Delay(100);
    }
    while(y<height)
    {
        y+=8;
        SDL_SetWindowSize(window_4,x,y);
        SDL_Delay(100);
    }
    
    

    // Simulation d'un délai avant de quitter
    SDL_Delay(1000);

    // Destruction des fenêtres et nettoyage
    
    SDL_DestroyWindow(window_1);
    SDL_DestroyWindow(window_2);
    SDL_DestroyWindow(window_3);
    SDL_DestroyWindow(window_4);
    
    SDL_Quit();                                // quitte la SDL

    return 0;
}
