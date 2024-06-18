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

void play_with_texture_4(SDL_Texture* my_texture,
               SDL_Window* window,
               SDL_Renderer* renderer) {
    SDL_Rect 
        source = {0},                    // Rectangle définissant la zone totale de la planche
        window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};                     // Rectangle de la vignette en cours dans la planche 

    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
            &window_dimensions.w,
            &window_dimensions.h);
    SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
            NULL, NULL,
            &source.w, &source.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                        // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée
    

    state.x = 0 ;                          // La première vignette est en début de ligne
    state.y = 3 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;                    // Hauteur de la vignette

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

    destination.y =                        // La course se fait en milieu d'écran (en vertical)
    (window_dimensions.h - destination.h) /2;

    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
        destination.x = x;                   // Position en x pour l'affichage du sprite
        state.x += offset_x;                 // On passe à la vignette suivante dans l'image
        state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                        // celle de début de ligne

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                &state,
                &destination);  
        SDL_RenderPresent(renderer);         // Affichage
        SDL_Delay(80);                       // Pause en ms
    }
    //SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
}


int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* bg = NULL;
    SDL_Texture* chen0 = NULL;
    SDL_Texture* chen1 = NULL;
    SDL_Texture* chen2 = NULL;
    SDL_Texture* chen3 = NULL;
    

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
    chen0 = IMG_LoadTexture(renderer,"./images/prof-1.png");
    chen1 = IMG_LoadTexture(renderer,"./images/prof.png");
    chen2 = IMG_LoadTexture(renderer,"./images/prof1.png");
    chen3 = IMG_LoadTexture(renderer,"./images/prof2.png");
    if (bg == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (chen0 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (chen1 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (chen2 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (chen3 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w,
    &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    
    SDL_QueryTexture(bg, NULL, NULL,
                &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, bg,
            &source,
            &destination); 

    SDL_QueryTexture(chen0, NULL, NULL,
                &source.w, &source.h);       // Récupération des dimensions de l'image

    float zoom = 0.8;                        // Facteur de zoom à appliquer    
    destination.w = source.w * zoom;         // La destination est un zoom de la source
    destination.h = source.h * zoom;         // La destination est un zoom de la source
    destination.x =
     (window_dimensions.w - destination.w) /2;     // La destination est au milieu de la largeur de la fenêtre
    destination.y =
     (window_dimensions.h - 0.575*window_dimensions.h);

    SDL_RenderCopy(renderer, chen0,
            &source,
            &destination); 
    

                                 
    SDL_RenderPresent(renderer); 
    SDL_Delay(3000);                      // Pause exprimée en ms                                   
    
    
    IMG_Quit();
    SDL_RenderClear(renderer); 

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}