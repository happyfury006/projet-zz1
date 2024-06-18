#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer) {
    char msg_formated[255];
    int l;

    if (!ok) {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strncpy(msg_formated + l, " : %s\n", 250 - l);
        SDL_Log(msg_formated, SDL_GetError());
    } else {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strncpy(msg_formated + l, "\n", 250 - l);
        SDL_Log(msg_formated);
    }

    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bg = NULL;
    SDL_Texture *chen[4] = {NULL};

    SDL_DisplayMode screen;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w,
                              screen.h,
                              SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    bg = IMG_LoadTexture(renderer, "./images/kanto_route_1.jpg");
    chen[0] = IMG_LoadTexture(renderer, "./images/prof-1.png");
    chen[1] = IMG_LoadTexture(renderer, "./images/prof.png");
    chen[2] = IMG_LoadTexture(renderer, "./images/prof1.png");
    chen[3] = IMG_LoadTexture(renderer, "./images/prof2.png");
    if (bg == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    for (int i = 0; i < 4; ++i) {
        if (chen[i] == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }

    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;

    bool running = true;

    SDL_Event event;
    int frame = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)) {
                running = false;
            }
        }


        SDL_RenderCopy(renderer, bg, &source, &destination);

        SDL_QueryTexture(chen[frame], NULL, NULL, &source.w, &source.h);
        float zoom = 0.8;
        destination.w = source.w * zoom;
        destination.h = source.h * zoom;
        destination.x = (window_dimensions.w - destination.w) / 2;
        destination.y = (window_dimensions.h - 1.735 * destination.h);

        SDL_RenderCopy(renderer, chen[frame], &source, &destination);
        SDL_RenderPresent(renderer);

        frame = (frame + 1) % 4;            // change entre 0, 1, 2, 3
        SDL_Delay(100); 
    }

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}
