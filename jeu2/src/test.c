#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>



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




void echanger_positions(SDL_Renderer* renderer, SDL_Texture* background_texture, SDL_Texture* textures[], SDL_Rect rectangles[], int nb_textures) {
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

/*void echanger_pioche(SDL_Renderer* renderer, SDL_Texture* background_texture, SDL_Texture* textures[], SDL_Rect rectangles[], int nb_textures) {
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
    SDL_Rect rect3 = rectangles[index_texture3];

    deplacer_texture(renderer, background_texture, textures[index_texture1], rect1, rect3, 5);
    deplacer_texture(renderer, background_texture, textures[index_texture2], rect2, rect1, 5);

    // Mettre à jour les rectangles avec les nouvelles positions
    rectangles[index_texture1] = rect3;
    rectangles[index_texture2] = rect1;
}*/


int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    SDL_Window* window = SDL_CreateWindow("Échanger Positions", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* background_texture = IMG_LoadTexture(renderer, "../Images/fondblanc.png");
    SDL_Texture* textures[3];
    SDL_Rect rectangles[3];
    textures[0] = IMG_LoadTexture(renderer, "../Images/ressource_bois.png");
    textures[1] = IMG_LoadTexture(renderer, "../Images/ressource_minerai.png");
    textures[2] = IMG_LoadTexture(renderer,"../Images/ressources_ble.png");
    SDL_Rect rect1 = {100, 100, 100, 150};
    SDL_Rect rect2 = {300, 300, 100, 150};
    SDL_Rect rect3 = {300,300, 100,150};
    rectangles[0] = rect1;
    rectangles[1] = rect2;
    rectangles[2] = rect3;
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                echanger_positions(renderer, background_texture, textures, rectangles, 2);
                // echanger_pioche(renderer,background_texture,textures,rectangles,3);
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, NULL); // Afficher le background
        for (int i = 0; i < 3; ++i) {
            SDL_RenderCopy(renderer, textures[i], NULL, &rectangles[i]);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(textures[0]);
    SDL_DestroyTexture(textures[1]);
    SDL_DestroyTexture(textures[2]);
    SDL_DestroyTexture(background_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
