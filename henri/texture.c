#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <math.h>


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


void displaySprite(SDL_Texture * texture, SDL_Window * window, SDL_Renderer * renderer, int frame)
{
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},
        state={0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture, NULL, NULL,&source.w, &source.h);

    int nb_images= 8;
    float zoom = 3; 
    int offset_x = source.w / nb_images;
    int offset_y = source.h;

    state.x = 0;
    state.y = offset_y*0;
    state.w = offset_x;
    state.h = offset_y;

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;

    destination.x = window_dimensions.w/2;
    destination.y = window_dimensions.h*0.85;

    state.x += frame*offset_x;
    state.x%=source.w;
    SDL_RenderCopy(renderer, texture, &state, &destination);
}


void displaybackground(SDL_Texture* my_texture,
            SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};

    SDL_GetWindowSize(
    window, &window_dimensions.w,
    &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    
    SDL_QueryTexture(my_texture, NULL, NULL,
                &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
            &source,
            &destination); 
}


void play_with_texture_3(SDL_Texture* my_texture,
            SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Rect 
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer
                            
    SDL_GetWindowSize(                      
    window, &window_dimensions.w,               
    &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,         
                        &source.w,                 
                &source.h);                    // Récupération des dimensions de l'image
                                
    /* On décide de déplacer dans la fenêtre         cette image */
    float zoom = 0.25;                              // Facteur de zoom entre l'image source et l'image affichée
                                
    int nb_it = 200;                                // Nombre d'images de l'animation
    destination.w = source.w * zoom;                // On applique le zoom sur la largeur
    destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
    destination.x =                     
    (window_dimensions.w - destination.w) / 2;  // On centre en largeur
    float h = window_dimensions.h - destination.h;  // hauteur du déplacement à effectuer

    for (int i = 0; i < nb_it; ++i) {
        destination.y =
        h * (1 - exp(-5.0 * i / nb_it) / 2 *
                (1 + cos(10.0 * i / nb_it * 2 *
                M_PI)));            // hauteur en fonction du numéro d'image

        SDL_RenderClear(renderer);                    // Effacer l'image précédente

        SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
        SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
        SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
        SDL_Delay(30);                                // Pause en ms
    }                               
    //SDL_RenderClear(renderer);                      // Effacer la fenêtre une fois le travail terminé
}



int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* bg = NULL;
    SDL_Texture* perso = NULL;

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
    bg = IMG_LoadTexture(renderer,"./images/ciel.jpg");
    perso = IMG_LoadTexture(renderer,"./images/run.png");
    if (bg == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (perso == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    for (int frame = 0; frame<400; frame++) 
    {
        displaybackground(bg, window, renderer);                     
        displaySprite(perso, window, renderer, frame);

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        SDL_RenderClear(renderer);
    }

    
                               
    
    
    IMG_Quit();
    SDL_RenderClear(renderer); 

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}