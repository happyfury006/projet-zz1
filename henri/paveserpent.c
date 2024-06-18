#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

                                    
void draw(SDL_Renderer* renderer,float w,float h, int color1, int color2) {  // Je pense que vous allez faire moins laid :)
    
    SDL_Rect rectangle;
    SDL_Rect rectangle2; 
    SDL_Rect carre; 

                                      
    SDL_SetRenderDrawColor(renderer,                                       
                color1, 0, 0,                             // mode Red, Green, Blue (tous dans 0..255)
                200);                                 // 0 = transparent ; 255 = opaque
    rectangle.x = w/2 -40;                                             // x haut gauche du rectangle
    rectangle.y = h/2 -100;                                                  // y haut gauche du rectangle
    rectangle.w = 80;                                                // sa largeur (w = width)
    rectangle.h = 200;

    rectangle2.w = 12;                                                // sa largeur (w = width)
    rectangle2.h = 20;
    rectangle2.x = (rectangle.x+(rectangle.w/2))-rectangle2.w/2;                                             // x haut gauche du rectangle
    rectangle2.y = rectangle.y-rectangle2.h;                                                  // y haut gauche du rectangle
     
    carre.h= 60;
    carre.w=carre.h;
    carre.x = (rectangle2.x+(rectangle2.w/2))-carre.w/2;
    carre.y = rectangle2.y-carre.h;                                              // sa hauteur (h = height)
                                        
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderFillRect(renderer, &carre);
    SDL_SetRenderDrawColor(renderer, color2, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rectangle2);                        
    /*SDL_RenderDrawLine(renderer,                             
            0, 0,                                          // x,y du point de la première extrémité
            400, 400);     */                                // x,y seconde extrémité

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
                                  
                                        

    /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... 
    for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000) {      
        SDL_SetRenderDrawColor(renderer,
                (cos(angle * 2) + 1) * 255 / 2,          // quantité de Rouge      
                (cos(angle * 5) + 1) * 255 / 2,          //          de vert 
                (cos(angle) + 1) * 255 / 2,              //          de bleu
                255);                                    // opacité = opaque
        SDL_RenderDrawPoint(renderer,                  
                    200 + 100 * cos(angle),                     // coordonnée en x
                    200 + 150 * sin(angle));                    //            en y  
    }*/ 
}


int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    

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
    
    SDL_Rect rectangle;
    SDL_Rect rectangle2; 
    SDL_Rect carre; 

    rectangle.x = screen.w/2 -40;                                             // x haut gauche du rectangle
    rectangle.y = screen.h/2 -100;                                                  // y haut gauche du rectangle
    rectangle.w = 80;                                                // sa largeur (w = width)
    rectangle.h = 200;

    rectangle2.w = 12;                                                // sa largeur (w = width)
    rectangle2.h = 20;
    rectangle2.x = (rectangle.x+(rectangle.w/2))-rectangle2.w/2;                                             // x haut gauche du rectangle
    rectangle2.y = rectangle.y-rectangle2.h;                                                  // y haut gauche du rectangle
     
    carre.h= 60;
    carre.w=carre.h;
    carre.x = (rectangle2.x+(rectangle2.w/2))-carre.w/2;
    carre.y = rectangle2.y-carre.h;

    bool bouge = true;
    bool avant = true;
    int vitesse = 2;
    int color1 = 255;
    int color2 = 120;


    while (bouge) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) 
            {
                bouge = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Change la couleur à chaque clique gauche
                    int temp=color1;
                    color1=color2;
                    color2=temp;
                }
            }
        }

        if (avant) {
            rectangle.x += vitesse;
            rectangle2.x += vitesse;
            carre.x += vitesse;
            if (rectangle.x + rectangle.w >= screen.w) {
                avant = false;
            }
        } else {
            rectangle.x -= vitesse;
            rectangle2.x -= vitesse;
            carre.x -= vitesse;
            if (rectangle.x <= 0) {
                avant = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, color1, 0, 0, 0);
        SDL_RenderFillRect(renderer, &rectangle);
        SDL_RenderFillRect(renderer, &carre);
        SDL_SetRenderDrawColor(renderer, color2, 0, 0, 0);
        SDL_RenderFillRect(renderer, &rectangle2);

        SDL_RenderPresent(renderer);

        SDL_Delay(20); 
    }

    SDL_Delay(3000);                                     // Pause exprimée en ms
                                                    

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}