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
   // bool running = false;
   // while (running == false)
   // {
   //    // On demande au joueur de jouer
   //    printf("Joueur 1, c'est a vous de jouer\n");
   //    printf("Entrez la forme de la piece que vous voulez jouer\n");
   //    int forme;
   //    scanf("%d",&forme);
   //    piece pieceajoutee = creerPiece(forme,1);
   //    printf("Entrez la position x de la piece que vous voulez jouer\n");
   //    int x;
   //    scanf("%d",&x);
   //    printf("Entrez la position y de la piece que vous voulez jouer\n");
   //    int y;
   //    scanf("%d",&y);
   //    grille plateau = creationplateau();
   //    plateau = ajoutpiece(plateau,pieceajoutee,x,y);
   //    if (victoire == true)
   //    {
   //       printf("Bravo vous avez gagne!\n");
   //       running = true;
   //    }
      
   //    // On demande a l'IA de jouer
   //    printf("C'est au tour de l'IA de jouer\n");
   //    int formIA = IA(plateau);
   //    piece pieceIA = creerPiece(formIA,2);
   //    int xIA = rand() % 4;
   //    int yIA = rand() % 4;
   //    plateau = ajoutpiece(plateau,pieceIA,xIA,yIA);
   //    if (victoire == true)
   //    {
   //       printf("L'IA a gagne!\n");
   //       running = true;
   //    }
      
      
   // }
   
   grille plateau=creationplateau();
   affichageplateau(plateau);
   plateau=ajoutpiece(plateau,creerPiece(3,1),0,0);
   affichageplateau(plateau);
   
   return 0;
}