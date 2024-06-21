#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

const int WINDOW_LARGEUR = 800;
const int WINDOW_HAUTEUR = 600;
const int vit = 5;

void render_background(SDL_Texture *bg_texture, SDL_Window *window,
                       SDL_Renderer *renderer, int offset) {
  SDL_Rect source =
               {0}, // Rectangle définissant la zone de la texture à récupérer
      window_dimensions = {0}, // Rectangle définissant la fenêtre, on
                               // n'utilisera que largeur et hauteur
      destination = {0}; // Rectangle définissant où la zone_source doit être
                         // déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h); // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(bg_texture, NULL, NULL, &source.w,
                   &source.h); // Récupération des dimensions de l'image

  destination = window_dimensions; // On fixe les dimensions de l'affichage à
                                   // celles de la fenêtre

  destination.x =
      -offset; // Appliquer l'offset pour créer l'effet de défilement

  SDL_RenderCopy(renderer, bg_texture, &source,
                 &destination); // Création de l'élément à afficher

  // Si l'arrière-plan sort de l'écran, dessiner une deuxième copie pour boucler
  if (destination.x + destination.w < window_dimensions.w) {
    destination.x += destination.w;
    SDL_RenderCopy(renderer, bg_texture, &source, &destination);
  }
}

void play_with_texture_4(SDL_Texture *bg_texture, SDL_Texture *my_texture,
                         SDL_Window *window, SDL_Renderer *renderer) {
  SDL_Rect source = {0}, // Rectangle définissant la zone totale de la planche
      window_dimensions = {0}, // Rectangle définissant la fenêtre, on
                               // n'utilisera que largeur et hauteur
      destination = {0}; // Rectangle définissant où la zone_source doit être
                         // déposée dans le renderer

  SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                    &window_dimensions.w, &window_dimensions.h);
  SDL_QueryTexture(my_texture, // Récupération des dimensions de l'image
                   NULL, NULL, &source.w, &source.h);

  int nb_images =
      8; // Il y a 8 vignettes dans la ligne de l'image qui nous intéresse
  float zoom = 1.0; // zoom, car ces images sont un peu petites
  int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image,
                                       // marche car la planche est bien réglée
      offset_y = source.h / 4; // La hauteur d'une vignette de l'image, marche
                               // car la planche est bien réglée

  destination.w = offset_x * zoom; // Largeur du sprite à l'écran
  destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

  destination.y = // La course se fait en milieu d'écran (en vertical)
      (window_dimensions.h - destination.h) / 2;

  int speed = 9;
  int bg_offset = 0;       // Pour l'animation de l'arrière-plan
  int frame_duration = 80; // Durée de chaque frame en ms

  for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
    destination.x = x; // Position en x pour l'affichage du sprite
    SDL_RenderClear(
        renderer); // Effacer l'image précédente avant de dessiner la nouvelle
    render_background(bg_texture, window, renderer, bg_offset);
    SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                   NULL, &destination);
    SDL_RenderPresent(renderer); // Affichage
    SDL_Delay(frame_duration);   // Pause en ms

    // Mettre à jour l'offset de l'arrière-plan pour créer l'effet de défilement
    bg_offset = (bg_offset + vit) % window_dimensions.w;
  }
  SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Window *window = SDL_CreateWindow(
      "Sprite avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Texture *bg_texture;
  SDL_Texture *my_texture2;
  bg_texture = IMG_LoadTexture(renderer, "../valentin/fondv2.jpg");
  my_texture2 = IMG_LoadTexture(renderer, "../valentin/marioyoshi.png");
  if (bg_texture == NULL) {
    printf("Echec du chargement de l'image dans la texture: %s\n",
           SDL_GetError());
    SDL_Quit();
    return 1;
  }

  play_with_texture_4(bg_texture, my_texture2, window, renderer);

  SDL_Delay(1000);
  SDL_DestroyTexture(my_texture2);
  SDL_DestroyTexture(bg_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  IMG_Quit();
  return 0;
}
