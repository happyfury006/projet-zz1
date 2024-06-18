#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>


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


void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
            SDL_Renderer *renderer) {
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w,
    &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
            &source,
            &destination);                 // Création de l'élément à afficher
    SDL_RenderPresent(renderer);                  // Affichage
    SDL_Delay(2000);                              // Pause en ms
}




int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* bg = NULL;
    

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/  
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    /*********************************************************************************************************************/
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
        screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, screen.w,
                screen.h,
                SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);


    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    

    /* Création du renderer */
    bg = IMG_LoadTexture(renderer,"./images/kanto_route_1.jpg");
    if (bg == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    play_with_texture_1(bg, window, renderer);


    SDL_Delay(3000);                             // Pause exprimée en ms                                   
    
    IMG_Quit();
    SDL_RenderClear(renderer); 

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}