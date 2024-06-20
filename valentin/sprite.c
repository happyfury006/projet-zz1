#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
const int WINDOW_LARGEUR = 800;
const int WINDOW_HAUTEUR = 600;
const int vit = 5;

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
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
    SDL_RenderPresent(renderer);                  // Affichage
    SDL_Delay(5000);                              // Pause en ms

    // Effacer la fenêtre
}

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
  SDL_Texture *my_texture2; 
  bg_texture = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/fond.png");
  my_texture2 = IMG_LoadTexture(renderer,"/home/local.isima.fr/vatardy/shared/Projet/projet-zz1/valentin/marioyoshi.png");
  if (bg_texture == NULL) 
  {
    // end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
  }
  // int x = WINDOW_LARGEUR / 2; Pos initiale de mario en x
  // int y = WINDOW_HAUTEUR / 2; Pos initiale de mario en y
  /*play_with_texture_1(bg_texture,window,renderer);
  SDL_Delay(200);
  play_with_texture_2(my_texture2,window,renderer);
  SDL_Delay(200);  */
  play_with_texture_4(bg_texture,my_texture2,window,renderer);
  /*play_with_texture_3(my_texture2,window,renderer);
  SDL_Delay(200)
  play_with_texture_4(my_texture2,window,renderer);
  SDL_Delay(200);
  play_with_texture_5(my_texture1,my_texture2,window,renderer);*/
  SDL_Delay(1000);
  SDL_DestroyTexture(my_texture2);
  SDL_DestroyTexture(bg_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  IMG_Quit();
  return 0;
}