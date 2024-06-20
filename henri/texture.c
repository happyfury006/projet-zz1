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
    float zoom = 2; 
    int offset_x = source.w / nb_images;
    int offset_y = source.h;

    state.x = 0;
    state.y = offset_y*0;
    state.w = offset_x;
    state.h = offset_y;

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;

    destination.x = window_dimensions.w*0.4;
    destination.y = window_dimensions.h*0.675;

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

void displaymoving(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer,int vitesse) {
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);
    

    destination.w = window_dimensions.w;
    destination.h = window_dimensions.h;
    destination.x = 0;
    destination.y= 0;
   
    float speed= vitesse;

    destination.x += speed;
    if (destination.x > destination.w)
    {
        destination.x =0;
    }
    
    SDL_RenderCopy(renderer, my_texture, &source, &destination);
    
    
    
    SDL_Delay(30);
    
}


int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* bg = NULL;
    SDL_Texture* perso = NULL;
    SDL_Texture* eau = NULL;
    SDL_Texture* eau2 = NULL;
    SDL_Texture* route = NULL;
    SDL_Texture* route2 = NULL;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

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
                SDL_WINDOWPOS_CENTERED, screen.w*0.7,
                screen.h*0.7,
                SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);


    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    

    /* Création du renderer */
    bg = IMG_LoadTexture(renderer,"./images/ciel.jpg");
    route = IMG_LoadTexture(renderer,"./images/kanto_route_1_route.png");
    route2 = IMG_LoadTexture(renderer,"./images/kanto_route_1_route.png");
    eau = IMG_LoadTexture(renderer,"./images/kanto_route_1_eau.png");
    eau2 = IMG_LoadTexture(renderer,"./images/kanto_route_1_eau.png");
    perso = IMG_LoadTexture(renderer,"./images/run.png");
    if (bg == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (perso == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (eau == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (eau2 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    if (route == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(route, NULL, NULL, &source.w, &source.h);
    
    destination.w = window_dimensions.w;
    destination.h = window_dimensions.h;
    destination.x = 0;
    destination.y= 0;

    SDL_Rect source2 = {0}, destination2 = {0};

   
    SDL_QueryTexture(eau, NULL, NULL, &source2.w, &source2.h);
    
    destination2.w = window_dimensions.w;
    destination2.h = window_dimensions.h;
    destination2.x = 0;
    destination2.y= 0;

    SDL_Rect source3 = {0}, destination3 = {0};

   
    SDL_QueryTexture(route2, NULL, NULL, &source3.w, &source3.h);
    
    destination3.w = window_dimensions.w;
    destination3.h = window_dimensions.h;
    destination3.x = window_dimensions.w;
    destination3.y= 0;

    SDL_Rect source4 = {0}, destination4 = {0};

   
    SDL_QueryTexture(eau2, NULL, NULL, &source4.w, &source4.h);
    
    destination4.w = window_dimensions.w;
    destination4.h = window_dimensions.h;
    destination4.x = window_dimensions.w;
    destination4.y= 0;
    
    flip=SDL_FLIP_HORIZONTAL;
    

    for (int frame = 0; frame<200; frame++) 
    {
        displaybackground(bg, window, renderer);  

        destination.x -=  5;
        if (destination.x  < -window_dimensions.w)
        {
            destination.x =window_dimensions.w-5;
        }
        SDL_RenderCopy(renderer, route, &source, &destination);

        destination3.x -=  5;
        if (destination3.x < -window_dimensions.w)
        {
            destination3.x =window_dimensions.w-5;
        }
        SDL_RenderCopyEx(renderer, route2, &source3, &destination3,0,NULL,flip);

        destination2.x -=  10;
        if (destination2.x < -window_dimensions.w)
        {
            destination2.x =window_dimensions.w-10;
        }
        SDL_RenderCopy(renderer, eau, &source2, &destination2); 
 

        destination4.x -=  10;
        if (destination4.x < -window_dimensions.w)
        {
            destination4.x =window_dimensions.w-10;
        }
        SDL_RenderCopyEx(renderer, eau2, &source4, &destination4,0,NULL,flip);        

        displaySprite(perso, window, renderer, frame);

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        SDL_RenderClear(renderer);
    }

    
    IMG_Quit();

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}