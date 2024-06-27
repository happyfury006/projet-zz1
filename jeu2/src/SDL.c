#include "SDL.h"


void init_grille(SDL_Rect grille[GRID_HEIGHT][GRID_WIDTH]) {
    SDL_Rect temp[GRID_HEIGHT][GRID_WIDTH] = {
        { {500, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 230, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {500, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 380, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {500, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 530, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {500, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 680, TAILLE_CARTE_W, TAILLE_CARTE_H} }
    };

    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grille[i][j] = temp[i][j];
        }
    }
}

void init_main_ia(SDL_Rect grille_ia[GRID1_HEIGHT][GRID1_WIDTH]) {
    SDL_Rect temp[GRID1_HEIGHT][GRID1_WIDTH] = {
        { {350, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {450, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {550, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {650, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {750, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {850, 10, TAILLE_CARTE_W, TAILLE_CARTE_H} }
    };

    for (int i = 0; i < GRID1_WIDTH; ++i) {
        grille_ia[0][i] = temp[0][i];
    }
}
void init_main_joueur(SDL_Rect grille_joueur[GRID1_HEIGHT][GRID1_WIDTH]) {
    SDL_Rect temp[GRID1_HEIGHT][GRID1_WIDTH] = {
        { {350, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {450, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {550, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {650, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {750, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {850, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H} }
    };

    for (int i = 0; i < GRID1_WIDTH; ++i) {
        grille_joueur[0][i] = temp[0][i];
    }
}

void cadrillage_carte(cadrillage cadri) {
    SDL_Rect temp[GRID_CARTE_HEIGHT][GRID_CARTE_WIDTH] = {
        { {150,10,TAILLE_CARTE_W,TAILLE_CARTE_H}, {250,10,TAILLE_CARTE_W,TAILLE_CARTE_H}, {350, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {450, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {550, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {650, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {750, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {850, 10, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {0,0,0,0}, {0,0,0,0}, {500, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 230, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {200,380,TAILLE_CARTE_W,TAILLE_CARTE_H}, {350,380,TAILLE_CARTE_W,TAILLE_CARTE_H}, {500, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 380, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {0,0,0,0}, {400,530,TAILLE_CARTE_W,TAILLE_CARTE_H}, {500, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 530, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {0,0,0,0}, {0,0,0,0}, {500, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 680, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {150,1090,TAILLE_CARTE_W,TAILLE_CARTE_H},{250,1090,TAILLE_CARTE_W,TAILLE_CARTE_H}, {350, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {450, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {550, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {650, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {750, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {850, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H} }
        
    };
    for (int i = 0; i < GRID_CARTE_HEIGHT; ++i) {
        for (int j = 0; j < GRID_CARTE_WIDTH; j++)
        {
            carte* newCarte= creation_carte(-1) ;
            newCarte->rect = temp[j][i];
            cadri.emplacement[j][i] = newCarte;
        }
    }
}

int init_cartes(tab_carte* cartes, SDL_Renderer* renderer, const char* image_paths[]) {
    SDL_Texture* texture_routeA = IMG_LoadTexture(renderer, image_paths[0]);
    if (!texture_routeA) {
        printf("Erreur IMG_LoadTexture pour routeA: %s\n", IMG_GetError());
        return 0;
    }

    SDL_Texture* texture_chevalierA = IMG_LoadTexture(renderer, image_paths[1]);
    if (!texture_chevalierA) {
        printf("Erreur IMG_LoadTexture pour chevalierA: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        return 0;
    }
SDL_Texture* texture_colonie = IMG_LoadTexture(renderer, image_paths[2]);
    if (!texture_colonie) {
        printf("Erreur IMG_LoadTexture pour colonie: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        return 0;
    }

    SDL_Texture* texture_ville = IMG_LoadTexture(renderer, image_paths[3]);
    if (!texture_ville) {
        printf("Erreur IMG_LoadTexture pour ville: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SDL_DestroyTexture(texture_colonie);
        return 0;
    }

    SDL_Texture* texture_developpement = IMG_LoadTexture(renderer, image_paths[4]);
    if (!texture_developpement) {
        printf("Erreur IMG_LoadTexture pour développement: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        return 0;
    }
    SDL_Texture* texture_routeB = IMG_LoadTexture(renderer, image_paths[5]);
    if (!texture_routeB) {
        printf("Erreur IMG_LoadTexture pour routeB: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);

        return 0;
    }
    SDL_Texture* texture_chevalierB = IMG_LoadTexture(renderer, image_paths[6]);
    if (!texture_chevalierB) {
        printf("Erreur IMG_LoadTexture pour chevalierB: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        return 0;
    }
    SDL_Texture* texture_ressource_bois = IMG_LoadTexture(renderer, image_paths[7]);
    if (!texture_ressource_bois) {
        printf("Erreur IMG_LoadTexture pour ressource_bois: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        SDL_DestroyTexture(texture_chevalierB);
        return 0;
    }
    SDL_Texture* texture_ressource_argile = IMG_LoadTexture(renderer, image_paths[8]);
    if (!texture_ressource_argile) {
        printf("Erreur IMG_LoadTexture pour ressource_argile: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        SDL_DestroyTexture(texture_chevalierB);
        SDL_DestroyTexture(texture_ressource_bois);
        return 0;
    }
    SDL_Texture* texture_ressource_mouton = IMG_LoadTexture(renderer, image_paths[9]);
    if (!texture_ressource_mouton) {
        printf("Erreur IMG_LoadTexture pour ressource_mouton: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        SDL_DestroyTexture(texture_chevalierB);
        SDL_DestroyTexture(texture_ressource_bois);
        SDL_DestroyTexture(texture_ressource_argile);
        return 0;
    }
    SDL_Texture* texture_ressource_minerai = IMG_LoadTexture(renderer, image_paths[10]);
    if (!texture_ressource_minerai) {
        printf("Erreur IMG_LoadTexture pour ressource_minerai: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        SDL_DestroyTexture(texture_chevalierB);
        SDL_DestroyTexture(texture_ressource_bois);
        SDL_DestroyTexture(texture_ressource_argile);
        SDL_DestroyTexture(texture_ressource_mouton);
        return 0;
    }

    SDL_Texture* texture_ressource_ble = IMG_LoadTexture(renderer, image_paths[11]);
    if (!texture_ressource_ble) {
        printf("Erreur IMG_LoadTexture pour ressource_ble: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        SDL_DestroyTexture(texture_chevalierB);
        SDL_DestroyTexture(texture_ressource_bois);
        SDL_DestroyTexture(texture_ressource_argile);
        SDL_DestroyTexture(texture_ressource_mouton);
        SDL_DestroyTexture(texture_ressource_minerai);
        return 0;
    }
    SDL_Texture* texture_dos_carte = IMG_LoadTexture(renderer, image_paths[12]);
    if (!texture_dos_carte) {
        printf("Erreur IMG_LoadTexture pour dos_carte: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SLD_DestroyTexture(texture_colonie);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        SDL_DestroyTexture(texture_chevalierB);
        SDL_DestroyTexture(texture_ressource_bois);
        SDL_DestroyTexture(texture_ressource_argile);
        SDL_DestroyTexture(texture_ressource_mouton);
        SDL_DestroyTexture(texture_ressource_minerai);
        SDL_DestroyTexture(texture_ressource_ble);

        return 0;
    }

    SDL_Texture* texture_emp_carte = IMG_LoadTexture(renderer, image_paths[13]);
    if (!texture_emp_carte) {
        printf("Erreur IMG_LoadTexture pour emp_carte: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_routeA);
        SDL_DestroyTexture(texture_chevalierA);
        SDL_DestroyTexture(texture_ville);
        SDL_DestroyTexture(texture_developpement);
        SDL_DestroyTexture(texture_routeB);
        SDL_DestroyTexture(texture_chevalierB);
        SDL_DestroyTexture(texture_ressource_bois);
        SDL_DestroyTexture(texture_ressource_argile);
        SDL_DestroyTexture(texture_ressource_mouton);
        SDL_DestroyTexture(texture_ressource_minerai);
        SDL_DestroyTexture(texture_ressource_ble);
        SDL_DestroyTexture(texture_dos_carte);

        return 0;
    }

    //assignation des textures aux cartes 

    //Carte routeA
    cartes->tab_carte[0]->texture = texture_routeA;

    //Carte chevalierA
    cartes->tab_carte[1]->texture = texture_chevalierA;

    //Carte colonie
    cartes->tab_carte[2]->texture = texture_colonie;

    //Carte ville
    cartes->tab_carte[3]->texture = texture_ville;

    //Carte développement
    cartes->tab_carte[4]->texture = texture_developpement;

    //Carte routeB
    cartes->tab_carte[5]->texture = texture_routeB;

    //Carte chevalierB
    cartes->tab_carte[6]->texture = texture_chevalierB;

    //asignation des textures des ressources

    //Ressource bois
    cartes->tab_carte[7]->texture = texture_ressource_bois;

    //Resosurce argile
    cartes->tab_carte[8]->texture = texture_ressource_argile;
    
    //Ressource mouton
    cartes->tab_carte[9]->texture = texture_ressource_mouton;
    
    //Ressource minerai
    cartes->tab_carte[10]->texture = texture_ressource_minerai;
    
    //Ressource ble
    cartes->tab_carte[11]->texture = texture_ressource_ble;
    
    //Dos carte
    cartes->tab_carte[12]->texture = texture_dos_carte;
    
    //Emp_carte
    cartes->tab_carte[13]->texture = texture_emp_carte;

    return 1;
}

void init_position_carte_initiale(cadrillage* cadri, tab_carte* cartes) {
    cadrillage* cadrillage_tmp_reel = cadri;
    for (int i = 2; i < GRID_CARTE_WIDTH; ++i) {
        //Carte construction position board
        if (i-2 != 3)
        {
            cadrillage_tmp_reel->emplacement[1][2]->type = cartes->tab_carte[i-2]->type;
            cadrillage_tmp_reel->emplacement[1][2]->texture = cartes->tab_carte[i-2]->texture;
        }   
    }
    //carte pioche de dos
    cadrillage_tmp_reel->emplacement[1][2]->type = cartes->tab_carte[12]->type;
    cadrillage_tmp_reel->emplacement[1][2]->texture = cartes->tab_carte[12]->texture;
}

void init_position_carte_marche_initiale(cadrillage* cadri, tab_carte* cartes,sitjoueur* joueur1,sitjoueur* joueur2){
    cadrillage* cadrillage_tmp_reel = cadri;
    for (int i = 1; i < GRID_CARTE_WIDTH; ++i) {
        //Carte ressource position marche premier initiale
        int random_pioche_marche=randomiser(5);
        cadrillage_tmp_reel->emplacement[i][3]->type = cartes->tab_carte[random_pioche_marche+7]->type;
        cadrillage_tmp_reel->emplacement[i][3]->texture = cartes->tab_carte[random_pioche_marche+7]->texture;
        joueur1->marchee[random_pioche_marche]++;
        joueur2->marchee[random_pioche_marche]++;
        joueur1->pioche[random_pioche_marche]--;
        joueur2->pioche[random_pioche_marche]--;
    }
}


void position_carte_joueur(cadrillage* cadri, tab_carte* cartes, sitjoueur* joueur1, sitjoueur* joueur2) {
    cadrillage* cadrillage_tmp_reel = cadri;
    for (int i = 0; i < GRID1_WIDTH; ++i) {
        //Carte ressource position joueur
        int random_pioche=randomiser(5);
        cadrillage_tmp_reel->emplacement[i][0]->type = cartes->tab_carte[random_pioche+7]->type;
        cadrillage_tmp_reel->emplacement[i][0]->texture = cartes->tab_carte[random_pioche+7]->texture;
        joueur1->mainjoueur[random_pioche]++;
        joueur2->mainjoueur[random_pioche]++;
        joueur1->pioche[random_pioche]--;
        joueur2->pioche[random_pioche]--;
    }
}



void display(SDL_Texture* bg_texture, tab_carte* cartes, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

    for (int i = 0; i < NB_CARTES; ++i) {
        if (cartes->tab_carte[i]) {
            SDL_RenderCopy(renderer, cartes->tab_carte[i]->texture, NULL, &cartes->tab_carte[i]->rect);
            printf("Carte %d : x = %d, y = %d, w = %d, h = %d\n", i, cartes->tab_carte[i]->rect.x, cartes->tab_carte[i]->rect.y, cartes->tab_carte[i]->rect.w, cartes->tab_carte[i]->rect.h);
        } else {
            printf("Carte %d est NULL\n", i);
        }
    }

    SDL_RenderPresent(renderer);
}

void destroy_cartes(tab_carte* cartes) {
    for (int i = 0; i < NB_CARTES; ++i) {
        if (cartes->tab_carte[i]) {
            if (cartes->tab_carte[i]->texture) {
                SDL_DestroyTexture(cartes->tab_carte[i]->texture);
            }
            free(cartes->tab_carte[i]);
        }
    }
}

int init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur IMG_Init: %s\n", IMG_GetError());
        SDL_Quit();
        return 0;
    }

    *window = SDL_CreateWindow("Cartes SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 1200, 0);
    if (!*window) {
        printf("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        IMG_Quit();
        SDL_Quit();
        return 0;
    }

    return 1;
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer, tab_carte* cartes) {
    destroy_cartes(cartes);
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

void phase_de_pioche(SDL_Renderer* renderer, tab_carte* cartes, SDL_Rect grille[GRID_HEIGHT][GRID_WIDTH], SDL_Rect grille1[GRID1_HEIGHT][GRID1_WIDTH],SDL_Texture* bg_texture, sitjoueur* joueur1, sitjoueur* joueur2) {

    
}

void tour_de_jeu(SDL_Renderer* renderer, tab_carte* cartes, SDL_Rect grille[GRID_HEIGHT][GRID_WIDTH], SDL_Rect grille1[GRID1_HEIGHT][GRID1_WIDTH],SDL_Rect grille2[GRID1_HEIGHT][GRID1_WIDTH], SDL_Texture* bg_texture) {
    //Tab_carte il faut que ca soit vu comme un dictionnaire qu'on vient copier dans le main et dans la grille

    
    
    // SDL_Texture* bg_texture = IMG_LoadTexture(renderer, "../Images/routeA.png");
    // if (!bg_texture) {
    //     printf("Erreur IMG_LoadTexture pour bg_texture: %s\n", IMG_GetError());
    //     return;
    // }

    // if (!init_cartes(cartes, renderer, image_paths, grille, grille1)) {
    //     SDL_DestroyTexture(bg_texture);
    //     return;
    // }

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            phase_de_pioche
        }
        display(bg_texture, cartes, renderer);
    }

    SDL_DestroyTexture(bg_texture);
}


void jeu() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!init(&window, &renderer)) {
        return 1;
    }

    const char *image_paths[NB_CARTES] = {
        "../Images/routeA.png",
        "../Images/chevalierA.png",
        "../Images/colonie.png",
        "../Images/ville.png",
        "../Images/developpement_eglise.png",
        "../Images/routeB.png",
        "../Images/chevalierB.png",
        
        "../Images/ressource_bois.png",
        "../Images/ressource_argile.png",
        "../Images/ressource_mouton.png",
        "../Images/ressource_minerai.png",
         "../Images/ressource_ble.png",
        
        "../Images/dos.png",
        "../Images/emp_carte.png",
        "../Images/fondblanc.png",
    };

    emplacement_carte grille[GRID_HEIGHT][GRID_WIDTH];
    init_grille(grille);

    emplacement_carte grille_ia[GRID1_HEIGHT][GRID1_WIDTH];
    init_main_ia(grille_ia);

    tab_carte cartes;
    cartes = creation_tab_carte();

    if (!init_cartes(&cartes, renderer, image_paths, grille, grille_ia)) {
        cleanup(window, renderer, &cartes);
        return 1;
    }

    SDL_Texture* bg_texture = IMG_LoadTexture(renderer, image_paths[14]);
    if (!bg_texture) {
        printf("Erreur IMG_LoadTexture pour bg_texture: %s\n", IMG_GetError());
        cleanup(window, renderer, &cartes);
        return 1;
    }

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        jeu();
        display(bg_texture, &cartes, renderer);
    }

    SDL_DestroyTexture(bg_texture);
    cleanup(window, renderer, &cartes);

    
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    jeu();
    return 1;
}
