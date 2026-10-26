#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "SDL.h"
#include "partie.h"

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));
  if (argc > 1 && strcmp(argv[1], "--console") == 0) {
    printf("Catane, le jeu de cartes : premier à 10 points.\n");
    printf("1 : contre l'IA, 2 : à deux joueurs ? ");
    int choix = 0;
    if (scanf("%d", &choix) != 1) return 1;
    partie(choix == 1);
    return 0;
  }
  return lancer_sdl();
}
