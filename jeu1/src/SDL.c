#include "SDL.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

const int WINDOW_LARGEUR = 1000;
const int WINDOW_HAUTEUR = 800;
const int GRID_ROWS = 4;
const int GRID_COLS = 4;
const int CELL_SIZE = 100; // Taille d'une cellule du plateau



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

int is_valid_position(int x, int y, SDL_Rect grid[][GRID_COLS], int grid_status[][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            if (SDL_PointInRect(&(SDL_Point){x, y}, &grid[i][j]) && grid_status[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void handle_events(SDL_Event *event, Piece pieces[], int piece_count, int *selected_piece, SDL_Rect grid[][GRID_COLS], int grid_status[][GRID_COLS]) {
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
                } else {
                    // Check if the selected position is valid
                    if (is_valid_position(x, y, grid, grid_status)) {
                        // Place the selected piece
                        pieces[*selected_piece].rect.x = x - pieces[*selected_piece].rect.w / 2;
                        pieces[*selected_piece].rect.y = y - pieces[*selected_piece].rect.h / 2;
                        pieces[*selected_piece].selected = 0;

                        // Mark the grid cell as occupied
                        for (int i = 0; i < GRID_ROWS; i++) {
                            for (int j = 0; j < GRID_COLS; j++) {
                                if (SDL_PointInRect(&(SDL_Point){x, y}, &grid[i][j])) {
                                    grid_status[i][j] = 1;
                                }
                            }
                        }

                        *selected_piece = -1;
                    }
                }
            }
            break;
        case SDL_QUIT:
            exit(0);
            break;
    }
}


void display(SDL_Texture* bgv2_texture, SDL_Texture* bg_texture, Piece pieces[], int piece_count, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    render_texture_fullscreen(bgv2_texture, renderer);
    render_texture_centered(bg_texture, renderer);
    render_pieces(pieces, piece_count, renderer);

    SDL_RenderPresent(renderer);
}

int mainsdl(int argc, char* argv[]) {
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
    
    bg_texture = IMG_LoadTexture(renderer, "../images/plateau.png");
    bgv2_texture = IMG_LoadTexture(renderer, "../images/fondblanc.png");
    j1_texture = IMG_LoadTexture(renderer, "../images/joueur1.png");
    j2_texture = IMG_LoadTexture(renderer, "../images/joueur2.png");
    ia_texture = IMG_LoadTexture(renderer, "../images/ia.png");
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
    pieces[13] = pieces[14];

    for (int i = 0; i < 16; i++) 
    {
        SDL_QueryTexture(pieces[i].texture, NULL, NULL, &pieces[i].rect.w, &pieces[i].rect.h);
        pieces[i].selected = 0;
    }

    if (bg_texture == NULL || bgv2_texture == NULL) {
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }

    place_pieces_initial(pieces);

    SDL_Rect grid[GRID_ROWS][GRID_COLS];
    int grid_status[GRID_ROWS][GRID_COLS];

    // Initialize the grid cells and grid status
    int grid_start_x = (WINDOW_LARGEUR - (GRID_COLS * CELL_SIZE)) / 2;
    int grid_start_y = (WINDOW_HAUTEUR - (GRID_ROWS * CELL_SIZE)) / 2;
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            grid[i][j].x = grid_start_x + j * CELL_SIZE;
            grid[i][j].y = grid_start_y + i * CELL_SIZE;
            grid[i][j].w = CELL_SIZE;
            grid[i][j].h = CELL_SIZE;
            grid_status[i][j] = 0; // Initialize all cells as empty
        }
    }

    int selected_piece = -1;

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handle_events(&event, pieces, 16, &selected_piece, grid, grid_status);
        }
        display(bgv2_texture, bg_texture, pieces, 16, window, renderer);
        SDL_Delay(16); // Approximately 60 FPS
    }
    for (int i = 0; i < 16; i++) 
    {
        if (pieces[i].texture) SDL_DestroyTexture(pieces[i].texture);
    }
    SDL_DestroyTexture(ia_texture);
    SDL_DestroyTexture(j2_texture);
    SDL_DestroyTexture(j1_texture);
    SDL_DestroyTexture(bgv2_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}