#include "IA.h"
#include "utils.h"
#include "jeu.h"
#include "SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>




int main(){
   printf("Hello, les gamers!\n");
   printf("Bienvenue dans notre jeu du quantik\n");
   printf("Le but est d'aligner 4 formes différentes soit en ligne, soit en colonne, soit en carré\n");
   printf("Voulez vous jouez seul en 1VSIA ou a 2 en 1VS1\n");
   printf("(1,1VSIA), (2,1VSIA):");
   int choix;
   
   scanf("%d",&choix);
   if (choix == 1)
   {
      jeuencours1VSIA();
   }
   else if (choix == 2)
   {
      jeuencours1VS1();
   }
   

   
   grille plateau=creationplateau();
   affichageplateau(plateau);
   plateau=ajoutpiece(plateau,creerPiece(3,1),0,0);
   affichageplateau(plateau);
   
   return 0;
}