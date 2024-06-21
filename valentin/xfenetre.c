#include <SDL2/SDL.h>
#include <stdio.h>

// Fonction principale
int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    // Dimensions des fenêtres
    SDL_Delay(3000);
    const int windowWidth = 100;
    const int windowHeight = 100;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Obtenir les dimensions de l'écran
    SDL_DisplayMode DM;
    if (SDL_GetCurrentDisplayMode(0, &DM) != 0) {
        printf("Erreur lors de l'obtention des dimensions de l'écran: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    int screenWidth = DM.w;
    int screenHeight = DM.h;

    // Calcul du nombre de fenêtres nécessaires pour couvrir la diagonale
    int numWindows = (screenWidth / windowWidth + screenHeight / windowHeight) / 2;
    SDL_Window* windows[numWindows * 2]; // Deux diagonales

    // Création des fenêtres sur la première diagonale (du haut gauche au bas droit)
    for (int i = 0; i < numWindows; ++i) {
        int x = (screenWidth / 2) - (numWindows * windowWidth / 2) + i * windowWidth;
        int y = (screenHeight / 2) - (numWindows * windowHeight / 2) + i * windowHeight;
        windows[i] = SDL_CreateWindow("X Window",
                                      x,
                                      y,
                                      windowWidth,
                                      windowHeight,
                                      SDL_WINDOW_SHOWN);
        if (!windows[i]) {
            printf("Erreur de création de la fenêtre %d: %s\n", i + 1, SDL_GetError());
            SDL_Quit();
            return 1;
        }
    }

    // Création des fenêtres sur la deuxième diagonale (du haut droit au bas gauche)
    for (int i = 0; i < numWindows; ++i) {
        int x = (screenWidth / 2) + (numWindows * windowWidth / 2) - (i + 1) * windowWidth;
        int y = (screenHeight / 2) - (numWindows * windowHeight / 2) + i * windowHeight;
        windows[numWindows + i] = SDL_CreateWindow("X Window",
                                                   x,
                                                   y,
                                                   windowWidth,
                                                   windowHeight,
                                                   SDL_WINDOW_SHOWN);
        if (!windows[numWindows + i]) {
            printf("Erreur de création de la fenêtre %d: %s\n", numWindows + i + 1, SDL_GetError());
            SDL_Quit();
            return 1;
        }
    }

    // Boucle d'événements
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Attendre un moment avant de redessiner (optionnel)
        SDL_Delay(100);
    }

    // Nettoyage et sortie
    for (int i = 0; i < numWindows * 2; ++i) {
        SDL_DestroyWindow(windows[i]);
    }
    SDL_Quit();

    return 0;
}

