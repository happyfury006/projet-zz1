#include "SDL_automate.h"




cadrillage cadrillage_carte(cadrillage cadri) {
    SDL_Rect temp[GRID_CARTE_HEIGHT][GRID_CARTE_WIDTH] = {
        { {350, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {450, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {550, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {650, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {750, 10, TAILLE_CARTE_W, TAILLE_CARTE_H}, {850, 10, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {0,0,0,0}, {0,0,0,0}, {500, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 230, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 230, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {200,380,TAILLE_CARTE_W,TAILLE_CARTE_H}, {350,380,TAILLE_CARTE_W,TAILLE_CARTE_H}, {500, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 380, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 380, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {0,0,0,0}, {400,530,TAILLE_CARTE_W,TAILLE_CARTE_H}, {500, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 530, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 530, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {0,0,0,0}, {0,0,0,0}, {500, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {600, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {700, 680, TAILLE_CARTE_W, TAILLE_CARTE_H}, {800, 680, TAILLE_CARTE_W, TAILLE_CARTE_H} },
        { {350, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {450, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {550, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {650, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {750, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H}, {850, 1090, TAILLE_CARTE_W, TAILLE_CARTE_H} }
        
    };
    for (int i = 0; i < GRID_CARTE_HEIGHT; ++i) {
        for (int j = 0; j < GRID_CARTE_WIDTH; j++)
        {
            carte* newCarte= creation_carte(-1) ;
            newCarte->texture= IMG_LoadTexture(renderer, "../Images/emp_carte.png");
            newCarte->rect = temp[j][i];
            cadri.emplacement[j][i] = newCarte;
        }
    }
    return cadri;
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
    int position = 0;
    for (int i = 2; i < GRID_CARTE_WIDTH; ++i) {
        //Carte construction position board
        if (i-2 != 3)
        {
            cadrillage_tmp_reel->emplacement[position+2][2]->type = cartes->tab_carte[i-2]->type;
            cadrillage_tmp_reel->emplacement[position+2][2]->texture = cartes->tab_carte[i-2]->texture;
            position++;
        }   
    }
    //carte pioche de dos
    cadrillage_tmp_reel->emplacement[1][2]->type = cartes->tab_carte[12]->type;
    cadrillage_tmp_reel->emplacement[1][2]->texture = cartes->tab_carte[12]->texture;
}

void init_positioner_carte_marche_initiale(cadrillage* cadri, tab_carte* cartes,sitjoueur* joueur1,sitjoueur* joueur2){
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


trouple* get_carte_from_position(cadrillage* cadri, int x, int y) {
    for (int i = 0; i < GRID_CARTE_HEIGHT; ++i) {
        for (int j = 0; j < GRID_CARTE_WIDTH; ++j) {
            if (cadri->emplacement[i][j]) {
                if (x >= cadri->emplacement[i][j]->rect.x && x <= cadri->emplacement[i][j]->rect.x + cadri->emplacement[i][j]->rect.w &&
                    y >= cadri->emplacement[i][j]->rect.y && y <= cadri->emplacement[i][j]->rect.y + cadri->emplacement[i][j]->rect.h) {
                    return creer_trouple(cadri->emplacement[i][j]->rect.x,cadri->emplacement[i][j]->rect.y, cadri->emplacement[i][j]->type);
                }
            }
        }
    }
    return -1;
}

void positioner_carte_joueur(cadrillage* cadri, tab_carte* cartes, sitjoueur* joueur1, sitjoueur* joueur2) {
    cadrillage* cadrillage_tmp_reel = cadri;
    
    int compteur_possition = 0;
    int indice_ressource = 0;
     // Assign the value to 'copie_main_joueur'
    while (indice_ressource != 4 && compteur_possition <= joueur1->nb_cartes_mainjoueur)
    {
        int copie_main_joueur = joueur1->mainjoueur[indice_ressource];
        while (copie_main_joueur != 0)
        {
            copie_main_joueur--;
            cadrillage_tmp_reel->emplacement[compteur_possition][5]->type = cartes->tab_carte[indice_ressource]->type;
            cadrillage_tmp_reel->emplacement[compteur_possition][5]->texture = cartes->tab_carte[indice_ressource]->texture;
        }
        indice_ressource++;
    }
    
}

void postionner_carte_constru_joueur(cadrillage* cadri, tab_carte* cartes, sitjoueur* joueur1, sitjoueur* joueur2,int choix_construction) {
    cadrillage* cadrillage_tmp_reel = cadri;

        if (choix_construction == 0 || choix_construction == 1)
        {
            if (joueur1->tab_constru_joueur[choix_construction]%2 == 0)
            {
                cadrillage_tmp_reel->emplacement[choix_construction+2][4]->type = cartes->tab_carte[choix_construction]->type;
                cadrillage_tmp_reel->emplacement[choix_construction+2][4]->texture = cartes->tab_carte[choix_construction]->texture;               
            }
            else
            {
                cadrillage_tmp_reel->emplacement[choix_construction+2][4]->type = cartes->tab_carte[choix_construction+5]->type;
                cadrillage_tmp_reel->emplacement[choix_construction+2][4]->texture = cartes->tab_carte[choix_construction+5]->texture;
            }
        }
        else
        {
            cadrillage_tmp_reel->emplacement[choix_construction+2][4]->type = cartes->tab_carte[choix_construction]->type;
            cadrillage_tmp_reel->emplacement[choix_construction+2][4]->texture = cartes->tab_carte[choix_construction]->texture;
        }   

}
  

void positioner_carte_ia(cadrillage* cadri, tab_carte* cartes, sitjoueur* joueur1, sitjoueur* joueur2) {
    cadrillage* cadrillage_tmp_reel = cadri;
    // Declare the variable 'copie_main_joueur'
    // for (int i = 0; i < joueur1->nb_cartes_mainjoueur; ++i) {
    //Carte ressource position joueur
    int compteur_possition = 0;
    int indice_ressource = 0;
    // Assign the value to 'copie_main_joueur'
    while (indice_ressource != 4 && compteur_possition <= joueur2->nb_cartes_mainjoueur)
    {
        int copie_main_joueur = joueur2->mainjoueur[indice_ressource];
        while (copie_main_joueur != 0)
        {
            copie_main_joueur--;
            cadrillage_tmp_reel->emplacement[compteur_possition][0]->type = cartes->tab_carte[indice_ressource]->type;
            cadrillage_tmp_reel->emplacement[compteur_possition][0]->texture = cartes->tab_carte[12]->texture;
        }
        indice_ressource++;
    }
}

int appartientRect(SDL_Rect* rect, int x, int y)
{
    return (x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h);
}

void deplacer_texture(SDL_Renderer* renderer, SDL_Texture* background_texture, SDL_Texture* texture, SDL_Rect rect_init, SDL_Rect rect_final, int speed) {
    int dx = rect_final.x - rect_init.x;
    int dy = rect_final.y - rect_init.y;
    int distance = sqrt(dx * dx + dy * dy);
    int steps = distance / speed;
    float increment_x = (float)dx / steps;
    float increment_y = (float)dy / steps;

    float x = rect_init.x;
    float y = rect_init.y;

    for (int i = 0; i < steps; ++i) {
        x += increment_x;
        y += increment_y;

        SDL_Rect rect_current = { (int)x, (int)y, rect_init.w, rect_init.h };

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, NULL); // Afficher le background
        SDL_RenderCopy(renderer, texture, NULL, &rect_current);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Pour créer un effet de mouvement fluide (~60 FPS)
    }

    // S'assurer que la texture est rendue à la position finale
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL); // Afficher le background
    SDL_RenderCopy(renderer, texture, NULL, &rect_final);
    SDL_RenderPresent(renderer);
}

void echanger_positions(SDL_Renderer* renderer, SDL_Texture* background_texture, SDL_Texture** textures, SDL_Rect rectangles, int nb_textures) {
    SDL_Event event;
    bool clicked = false;
    int index_texture1 = -1;

    while (!clicked) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            return;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            for (int i = 0; i < nb_textures; ++i) {
                SDL_Rect rect = rectangles[i];
                if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
                    index_texture1 = i;
                    clicked = true;
                    break;
                }
            }
        }
    }

    int index_texture2 = -1;
    clicked = false;

    while (!clicked) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            return;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            for (int i = 0; i < nb_textures; ++i) {
                SDL_Rect rect = rectangles[i];
                if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h && i != index_texture1) {
                    index_texture2 = i;
                    clicked = true;
                    break;
                }
            }
        }
    }

    // Échanger les positions des textures
    SDL_Rect rect1 = rectangles[index_texture1];
    SDL_Rect rect2 = rectangles[index_texture2];

    deplacer_texture(renderer, background_texture, textures[index_texture1], rect1, rect2, 5);
    deplacer_texture(renderer, background_texture, textures[index_texture2], rect2, rect1, 5);

    // Mettre à jour les rectangles avec les nouvelles positions
    rectangles[index_texture1] = rect2;
    rectangles[index_texture2] = rect1;
}

void echanger_pioche(SDL_Renderer* renderer, SDL_Texture* background_texture, SDL_Texture* textures_carte_main, SDL_Texture* textures_carte_pioche, SDL_Rect rect_main, SDL_Rect rect_pioche, SDL_Rect rect_defausse, int nb_textures) {

    SDL_Rect rect1 = rect_main;
    SDL_Rect rect2 = rect_pioche;
    SDL_Rect rect3 = rect_defausse;

    deplacer_texture(renderer, background_texture, textures_carte_main, rect1, rect3, 5);
    deplacer_texture(renderer, background_texture,  textures_carte_pioche, rect2 ,rect1, 5);

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

void tour_de_jeu(SDL_Renderer* renderer,tab_carte* cartes, cadrillage* cadri, SDL_Rect rect_main_joueur,SDL_Rect rect_pioche,SDL_Rect rect_main_marche,SDL_Rect rect_defausse ,SDL_Texture* bg_texture, sitjoueur* joueur1, sitjoueur* joueur2, int x, int y,int case, bool* tour) {
  //Un systeme automate avec un switch case pour representer les différentes phase d'un tour de jeu, d'abord le joueur1 pioche puis il choisi d'échanger des cartes(max 2) de sa main avec la pioche ou le marche ou garder ses cartes puis après la phase de construction choisis de contruire une cartes a partir des ressources s'il en a assez puis le joueur 2 fait la meme chose que le joueur1
  if (tour!=0)
  {
    switch (case)
    {
    case 1:
      //Pioche
      int position_libre = 0;
      for (int i = 0; i < GRID_CARTE_WIDTH; i++)
      {
        if (cadri->emplacement[i][5]->type == -1)
        {
          position_libre = i;
          break;
        }
      }
      
      deplacer_texture(renderer, bg_texture, cartes->tab_carte[12]->texture, rect_pi, cadri->emplacement[position_libre][5]->rect, 5);
      piocher(joueur1, joueur2, 1);
      // echanger_pioche(renderer, bg_texture, cartes->tab_carte, cadri->emplacement, 3);
      positioner_carte_joueur(cadri, cartes, joueur1, joueur2);
      case=2;
      break;
    case 2:
      //Echange
      if (appartientRect(rect_pioche, x, y) && joueur1->nb_cartes_mainjoueur > 0)
      {
        echanger_pioche(renderer, bg_texture, cartes->tab_carte[12]->texture, cartes->tab_carte[7]->texture, cadri->emplacement[x][y]->rect, cadri->emplacement[1][2]->rect, cadri->emplacement[1][2]->rect, 3);
        piocher(joueur1, joueur2, 1);
        positioner_carte_joueur(cadri, cartes, joueur1, joueur2);
      }
      else if (appartientRect(cadri->emplacement[x][y]->rect, 0, 0) && joueur1->nb_cartes_mainjoueur > 0)
      {
        echanger_pioche(renderer, bg_texture, cartes->tab_carte[12]->texture, cartes->tab_carte[8]->texture, cadri->emplacement[x][y]->rect, cadri->emplacement[1][2]->rect, cadri->emplacement[1][2]->rect, 3);
        piocher(joueur1, joueur2, 1);
        positioner_carte_joueur(cadri, cartes, joueur1, joueur2);
      }
      
      
      echanger_pioche(renderer, bg_texture, cartes->tab_carte, cadri->emplacement, 3);
      positioner_carte_joueur(cadri, cartes, joueur1, joueur2);
      case=3;
      break;
    case 3:
      //Construction
      postionner_carte_constru_joueur(cadri, cartes, joueur1, joueur2, 1);
      tour=0;
      break;
    default:
      break;
    }
  }
  
    
    
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
        // "../Images/emp_carte.png",
        // "../Images/fondblanc.png",
    };

    cadrillage cadri;
    cadri = cadrillage_carte(cadri);

    tab_carte cartes;
    cartes = creation_tab_carte();
    
    SDL_Rect rect_main_ordi = {350, 10, TAILLE_CARTE_W*6, TAILLE_CARTE_H };
    SDL_Rect rect_main_joueur = {350, 1090, TAILLE_CARTE_W*6, TAILLE_CARTE_H };
    SDL_Rect rect_pioche = {350, 380, TAILLE_CARTE_W, TAILLE_CARTE_H };
    SDL_Rect rect_defausse = {200, 380, TAILLE_CARTE_W, TAILLE_CARTE_H };
    SDL_Rect rect_marche = {400, 530, TAILLE_CARTE_W*5, TAILLE_CARTE_H };

    if (!init_cartes(&cartes, renderer, image_paths)) {
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
    sitjoueur* joueur1 = creation_sitjoueur(1);
    sitjoueur* joueur2 = creation_sitjoueur(2);
    int clique_x, clique_y;
    int anim = 0;

    init_position_carte_initiale(&cadri, &cartes);
    while (running) {

        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT:
                    switch (event.window.event)  {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            width = event.window.data1;
                            height = event.window.data2;
                        default:
                            dessinerFenetre(renderer, tapis, cartes, boutons, &j1, tabj1, -1, &j2, tabj2, -1, sommetDefausse(&defausse), &defausse_rect, &pioche_rect, &rectEnMvt1, &rectEnMvt2, &bouton1, &bouton2, etat);
                    }   
                break;
                case SDL_MOUSEBUTTONDOWN:
                    clique_x = event.button.x;
                    clique_y = event.button.y;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        annimation = 1;
                        debanim = time(NULL);
                        break;
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    default:
                        break;
                    }
                break;
                case SDL_QUIT :  
                    running = 0;      
            }
        }
        trouple* carte_info =get_carte_from_position(&cadri, clique_x, clique_y);
        if (carte_info != -1)
        {
            tour_de_jeu(renderer, &cartes, &cadri, bg_texture, rect_main_joueur,rect_pioche,rect_marche,rect_defausse, joueur1, joueur2, carte_info->premier, carte_info->deuxieme, carte_info->troisieme, &anim);
        }
        

    SDL_DestroyTexture(bg_texture);
    cleanup(window, renderer, cartes);

    
}
}