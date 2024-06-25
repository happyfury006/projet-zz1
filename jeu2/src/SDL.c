

#include "SDL.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>  
#include <math.h>
#include "utils.h"
const int WINDOW_LARGEUR = 1300;
const int WINDOW_HAUTEUR = 900;


void end_sdl(int ok, const char* msg, SDL_Window* window, SDL_Renderer* renderer) 
{
    char msg_formated[255];
    int l;
    if (!ok) {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");
        SDL_Log(msg_formated, SDL_GetError());
    }
    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

void initialisation()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Milles bornes avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *bg_texture;
    SDL_Texture *chevalier_recto_texture;
    SDL_Texture *chevalier_verso_texture;
    SDL_Texture *route_recto_texture;
    SDL_Texture *route_verso_texture;
    SDL_Texture *colonie_texture;
    SDL_Texture *ville_texture;
    SDL_Texture *developpement_texture;
    SDL_Texture *bois_texture;
    SDL_Texture *argile_texture;
    SDL_Texture *pierre_texture;
    SDL_Texture *mouton_texture;
    SDL_Texture *paille_texture;
    SDL_Texture *dos_carte_texture;
    bg_texture = IMG_LoadTexture(renderer, "../Images/fondblanc.png");
    chevalier_recto_texture = IMG_LoadTexture(renderer, "../Images/chevalier_recto.png");
    chevalier_verso_texture = IMG_LoadTexture(renderer, "../Images/chevalier_verso.png");
    route_recto_texture = IMG_LoadTexture(renderer, "../Images/route_recto.png");
    route_verso_texture = IMG_LoadTexture(renderer, "../Images/route_verso.png");
    colonie_texture = IMG_LoadTexture(renderer, "../Images/colonie.png");
    ville_texture = IMG_LoadTexture(renderer, "../Images/ville.png");
    developpement_texture = IMG_LoadTexture(renderer, "../Images/developpement.png");
    bois_texture = IMG_LoadTexture(renderer, "../Images/bois.png");
    argile_texture = IMG_LoadTexture(renderer, "../Images/argile.png");
    pierre_texture = IMG_LoadTexture(renderer, "../Images/pierre.png");
    mouton_texture = IMG_LoadTexture(renderer, "../Images/mouton.png");
    paille_texture = IMG_LoadTexture(renderer, "../Images/paille.png");
    dos_carte_texture = IMG_LoadTexture(renderer, "../Images/dos_carte.png");
}

void destruction(SDL_Texture* texture,SDL_Window* window,SDL_Renderer* renderer)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
}


int main(int argc, char* argv[]) {

    (void)argc;
    (void)argv;
    for (int i = 0; i < 16; i++) {
        SDL_QueryTexture(pieces[i].texture, NULL, NULL, &pieces[i].rect.w, &pieces[i].rect.h);
        pieces[i].selected = 0;
    }

    if (bg_texture == NULL || bgv2_texture == NULL || j1_texture == NULL || j2_texture == NULL) {
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }

    grille(tableau);
    
    int mode = display_menu(renderer, bgv2_texture, one_player_texture, two_player_texture);
    printf("Mode sélectionné: %d joueur(s)\n", mode);

    place_pieces_initial(pieces);
    int selected_piece = -1;

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handle_events(&event, pieces, 16, &selected_piece, tableau);
        }
        if(mode == 1)
        {
            display(bgv2_texture, bg_texture, ia_texture, j1_texture, pieces, 16, renderer);
            SDL_Delay(16); // Pour avoir environs 60 FPS
        }
        else
        {
            display(bgv2_texture,bg_texture,j2_texture,j1_texture,pieces,16,renderer);
        }
    }
    for (int i = 0; i < 16; i++) {
        if (pieces[i].texture) SDL_DestroyTexture(pieces[i].texture);
    }

    SDL_DestroyTexture(two_player_texture);
    SDL_DestroyTexture(one_player_texture);
    SDL_DestroyTexture(j2_win);
    SDL_DestroyTexture(j1_win);
    SDL_DestroyTexture(ia_texture);
    SDL_DestroyTexture(j1_texture);
    SDL_DestroyTexture(j2_texture);
    SDL_DestroyTexture(bgv2_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}