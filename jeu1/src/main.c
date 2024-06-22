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
  printf("(Tapez 1 pour 1VSIA), (Tapez 2 pour 1VS1):");
  int choix;
  scanf("%d", &choix);
  

  if (choix == 1) {
    return jeuencours1VSIA();
  } else if (choix == 2) {
    return jeuencours1VS1();
  }
  // affichageplateau(plateau);
  // plateau=ajoutpiece(plateau,creerPiece(3,1),0,0);

  
}