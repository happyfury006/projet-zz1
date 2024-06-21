#include "IA.h"
#include "jeu.h"
#include "utils.h"
// #include "SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main() {
  printf("Hello, les gamers!\n");
  printf("Bienvenue dans notre jeu du quantik\n");
  printf("Le but est d'aligner 4 formes différentes soit en ligne, soit en "
         "colonne, soit en carré\n");
  printf("Voulez vous jouez seul en 1VSIA ou a 2 en 1VS1\n");
  printf("(1,1VSIA), (2,1VS1):");
  int choix;
  scanf("%d", &choix);
  grille *plateau = creationplateau();

  if (choix == 1) {
    jeuencours1VSIA();
  } else if (choix == 2) {
    jeuencours1VS1();
  }
  // affichageplateau(plateau);
  // plateau=ajoutpiece(plateau,creerPiece(3,1),0,0);

  return 0;
}