#include "SDL.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
const int WINDOW_LARGEUR = 800;
const int WINDOW_HAUTEUR = 600;

void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
               SDL_Renderer *renderer) 
  {
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
                            // Pause en ms
    SDL_RenderPresent(renderer);                    // Effacer la fenêtre
}

void play_with_texture_4(SDL_Texture* bg_texture, SDL_Texture* my_texture,
      SDL_Window* window,
      SDL_Renderer* renderer) {
  SDL_Rect 
  source = {0},                    // Rectangle définissant la zone totale de la planche
  window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
  destination = {0};               // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
      &window_dimensions.w,
      &window_dimensions.h);
  SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
      NULL, NULL,
      &source.w, &source.h);

     /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

  int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
  float zoom = 1.0;                        // zoom, car ces images sont un peu petites
  int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
  offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


  destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
  destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

  destination.y =                        // La course se fait en milieu d'écran (en vertical)
  (window_dimensions.h - destination.h) /2;

  int speed = 9;
  for (int x = 0; x < window_dimensions.w - destination.w; x += speed) 
  {
    destination.x = x;                   // Position en x pour l'affichage du sprite
    SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
    play_with_texture_1_1(bg_texture,window,renderer);
    SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
      NULL,
      &destination);  
    SDL_RenderPresent(renderer);         // Affichage
    SDL_Delay(80);                       // Pause en ms
  }
  SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Sprite avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *bg_texture;
    SDL_Texture *piece1b; 
    SDL_Texture *piece2b; 
    SDL_Texture *piece3b; 
    SDL_Texture *piece4b; 
    SDL_Texture *piece1n; 
    SDL_Texture *piece2n; 
    SDL_Texture *piece3n; 
    SDL_Texture *piece4n; 
    SDL_Texture *piece5b; 
    SDL_Texture *piece6b; 
    SDL_Texture *piece7b; 
    SDL_Texture *piece8b;
    SDL_Texture *piece5n;  
    SDL_Texture *piece6n; 
    SDL_Texture *piece7n; 
    SDL_Texture *piece8n; 
    bg_texture = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/fond.png");
    piece1b = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece1b.png");
    piece2b = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece2b.png");
    piece3b = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece3bpng");
    piece4b = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece4b.png");
    piece1n = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece1n.png");
    piece2n = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece2n.png");
    piece3n = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece3n.png");
    piece4n = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/piece4n.png");
    piece5b = piece1b;
    piece6b = piece2b;
    piece7b = piece3b;
    piece8b = piece4b;
    piece5n = piece1n;
    piece6n = piece2n;
    piece7n = piece3n;
    piece8n = piece4n;
    if (bg_texture == NULL) 
    {
        // end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }
    play_with_texture_4(bg_texture,NULL,window,renderer);
    SDL_Delay(1000);
    SDL_DestroyTexture(piece8n);
    SDL_DestroyTexture(piece7n);
    SDL_DestroyTexture(piece6n);
    SDL_DestroyTexture(piece5n);
    SDL_DestroyTexture(piece8b);
    SDL_DestroyTexture(piece7b);
    SDL_DestroyTexture(piece6b);
    SDL_DestroyTexture(piece5b);
    SDL_DestroyTexture(piece4n);
    SDL_DestroyTexture(piece3n);
    SDL_DestroyTexture(piece2n);
    SDL_DestroyTexture(piece1n);
    SDL_DestroyTexture(piece4b);
    SDL_DestroyTexture(piece3b);
    SDL_DestroyTexture(piece2b);
    SDL_DestroyTexture(piece1b);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}
