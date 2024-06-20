#include "SDL.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

const int WINDOW_LARGEUR = 1300;
const int WINDOW_HAUTEUR = 900;

const int GRID_ROWS = 4;
const int GRID_COLS = 4;
const int CELL_WIDTH = 100; // Largeur de chaque cellule du plateau
const int CELL_HEIGHT = 100; // Hauteur de chaque cellule du plateau


void end_sdl(int ok, const char* msg, SDL_Window* window, SDL_Renderer* renderer) {
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

void render_texture_fullscreen(SDL_Texture *texture, SDL_Renderer *renderer) {
    SDL_Rect destination = {0, 0, WINDOW_LARGEUR, WINDOW_HAUTEUR};
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void render_texture_centered(SDL_Texture *texture, SDL_Renderer *renderer) {
    SDL_Rect source = {0};
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

    SDL_Rect destination = {0};
    destination.w = source.w;
    destination.h = source.h;
    destination.x = (WINDOW_LARGEUR - source.w) / 2;
    destination.y = (WINDOW_HAUTEUR - source.h) / 2;

    SDL_RenderCopy(renderer, texture, &source, &destination);
}

void render_pieces(Piece pieces[], int piece_count, SDL_Renderer *renderer) {
    for (int i = 0; i < piece_count; i++) {
        SDL_RenderCopy(renderer, pieces[i].texture, NULL, &pieces[i].rect);
    }
}

void render_extra_textures(SDL_Texture* texture1, SDL_Texture* texture2, SDL_Renderer *renderer) {
    SDL_Rect source1 = {0}, source2 = {0};
    SDL_QueryTexture(texture1, NULL, NULL, &source1.w, &source1.h);
    SDL_QueryTexture(texture2, NULL, NULL, &source2.w, &source2.h);

    SDL_Rect destination1 = {0};
    destination1.w = source1.w;
    destination1.h = source1.h;
    destination1.x = 0;
    destination1.y = 110;

    SDL_Rect destination2 = {0};
    destination2.w = source2.w;
    destination2.h = source2.h;
    destination2.x = WINDOW_LARGEUR - destination2.w;
    destination2.y = WINDOW_HAUTEUR - destination2.h - 110;

    SDL_RenderCopy(renderer, texture1, &source1, &destination1);
    SDL_RenderCopy(renderer, texture2, &source2, &destination2);
}

void place_pieces_initial(Piece pieces[]) {
    int piece_width = WINDOW_LARGEUR / 8;

    for (int i = 0; i < 8; i++) {
        pieces[i].rect.x = i * piece_width + (piece_width - pieces[i].rect.w) / 2;
        pieces[i].rect.y = WINDOW_HAUTEUR - pieces[i].rect.h - 10; // Bottom row
    }

    for (int i = 8; i < 16; i++) {
        pieces[i].rect.x = (i - 8) * piece_width + (piece_width - pieces[i].rect.w) / 2;
        pieces[i].rect.y = 10; // Top row
    }
}

int is_valid_position(int x, int y, Piece pieces[], int piece_count) {
    // Check if the position is within the board's grid
    if (x < 0 || x >= WINDOW_LARGEUR || y < 0 || y >= WINDOW_HAUTEUR) {
        return 0;
    }
    // Check if the position is within the grid cells
    int cell_x = x / CELL_WIDTH;
    int cell_y = y / CELL_HEIGHT;
    if (cell_x >= GRID_COLS || cell_y >= GRID_ROWS) {
        return 0;
    }
    // Check if the cell is already occupied
    for (int i = 0; i < piece_count; i++) {
        int piece_cell_x = pieces[i].rect.x / CELL_WIDTH;
        int piece_cell_y = pieces[i].rect.y / CELL_HEIGHT;
        if (piece_cell_x == cell_x && piece_cell_y == cell_y) {
            return 0;
        }
    }
    return 1;
}

void snap_to_grid(Piece *piece) {
    int cell_x = piece->rect.x / CELL_WIDTH;
    int cell_y = piece->rect.y / CELL_HEIGHT;
    piece->rect.x = cell_x * CELL_WIDTH + (CELL_WIDTH - piece->rect.w) / 2;
    piece->rect.y = cell_y * CELL_HEIGHT + (CELL_HEIGHT - piece->rect.h) / 2;
}

void handle_events(SDL_Event *event, Piece pieces[], int piece_count, int *selected_piece) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                int x = event->button.x;
                int y = event->button.y;
                if (*selected_piece == -1) {
                    // Check if we clicked on any piece
                    for (int i = 0; i < piece_count; i++) {
                        if (SDL_PointInRect(&(SDL_Point){x, y}, &pieces[i].rect)) {
                            *selected_piece = i;
                            pieces[i].selected = 1;
                            break;
                        }
                    }
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (*selected_piece != -1) {
                    int x = event->button.x;
                    int y = event->button.y;
                    // Check if the new position is valid
                    if (is_valid_position(x, y, pieces, piece_count)) {
                        // Snap the piece to the grid
                        snap_to_grid(&pieces[*selected_piece]);
                    } else {
                        // If not valid, reset the piece to its original position
                        pieces[*selected_piece].rect.x = pieces[*selected_piece].rect.x - pieces[*selected_piece].rect.w / 2;
                        pieces[*selected_piece].rect.y = pieces[*selected_piece].rect.y - pieces[*selected_piece].rect.h / 2;
                    }
                    // Release the selected piece
                    pieces[*selected_piece].selected = 0;
                    *selected_piece = -1;
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (*selected_piece != -1) {
                int x = event->motion.x;
                int y = event->motion.y;
                // Update the position of the selected piece
                pieces[*selected_piece].rect.x = x - pieces[*selected_piece].rect.w / 2;
                pieces[*selected_piece].rect.y = y - pieces[*selected_piece].rect.h / 2;
            }
            break;
        case SDL_QUIT:
            exit(0);
            break;
    }
}

void display(SDL_Texture* bgv2_texture, SDL_Texture* bg_texture,SDL_Texture* extra_texture1,SDL_Texture* extra_texture2, Piece pieces[], int piece_count, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    render_texture_fullscreen(bgv2_texture, renderer);
    render_texture_centered(bg_texture, renderer);
    render_pieces(pieces, piece_count, renderer);
    render_extra_textures(extra_texture1, extra_texture2, renderer);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Quantik avec SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *bg_texture;
    SDL_Texture *bgv2_texture;
    SDL_Texture *j1_texture;
    SDL_Texture *j2_texture;
    SDL_Texture *ia_texture;
    Piece pieces[16] = {0};
    
    bg_texture = IMG_LoadTexture(renderer, "../images/nouveaufond.png");
    bgv2_texture = IMG_LoadTexture(renderer, "../images/fondblanc.png");
    j1_texture = IMG_LoadTexture(renderer, "../images/joueur1.png");
    j2_texture = IMG_LoadTexture(renderer, "../images/joueur2.png");
    pieces[0].texture = IMG_LoadTexture(renderer, "../images/coneblanc.png");
    pieces[2].texture = IMG_LoadTexture(renderer, "../images/cubeblanc.png");
    pieces[4].texture = IMG_LoadTexture(renderer, "../images/cylindreblanc.png");
    pieces[6].texture = IMG_LoadTexture(renderer, "../images/sphereblanche.png");
    pieces[8].texture = IMG_LoadTexture(renderer, "../images/conenoir.png");
    pieces[10].texture = IMG_LoadTexture(renderer, "../images/cubenoir.png");
    pieces[12].texture = IMG_LoadTexture(renderer, "../images/cylindrenoir.png");
    pieces[14].texture = IMG_LoadTexture(renderer, "../images/spherenoir.png");
    pieces[1] = pieces[0];
    pieces[3] = pieces[2];
    pieces[5] = pieces[4];
    pieces[7] = pieces[6];
    pieces[9] = pieces[8];
    pieces[11] = pieces[10];
    pieces[13] = pieces[12];
    pieces[15] = pieces[14];
    for (int i = 0; i < 16; i++) {
        SDL_QueryTexture(pieces[i].texture, NULL, NULL, &pieces[i].rect.w, &pieces[i].rect.h);
        pieces[i].selected = 0;
    }

    if (bg_texture == NULL || bgv2_texture == NULL) {
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }

    place_pieces_initial(pieces);
    int selected_piece = -1;

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handle_events(&event, pieces, 16, &selected_piece);
        }
        display(bgv2_texture, bg_texture,j2_texture,j1_texture, pieces, 16, window, renderer);
        SDL_Delay(16); // Approximately 60 FPS
    }
    for (int i = 0; i < 16; i++) {
        if (pieces[i].texture) SDL_DestroyTexture(pieces[i].texture);
    }
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
