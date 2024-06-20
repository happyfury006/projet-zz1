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



void jeuencours1VS1(){
   bool running = false;
      while (running == false)
   {
      // On demande au joueur de jouer
      printf("Joueur 1, c'est a vous de jouer\n");
      printf("Entrez la forme de la piece que vous voulez jouer\n");
      int forme;
      scanf("%d",&forme);
      piece pieceajoutee = creerPiece(forme,1);
      printf("Entrez la position x de la piece que vous voulez jouer\n");
      int x;
      scanf("%d",&x);
      printf("Entrez la position y de la piece que vous voulez jouer\n");
      int y;
      scanf("%d",&y);
      grille plateau = creationplateau();
      plateau = ajoutpiece(plateau,pieceajoutee,x,y);
      if (victoire == true)
      {
         printf("Bravo vous avez gagne!\n");
         running = true;
      }
      
      // On demande a l'IA de jouer
      printf("C'est au tour de l'IA de jouer\n");
      

      // plateau = ajoutpiece(plateau,pieceIA,xIA,yIA);
      if (victoire == true)
      {
         printf("L'IA a gagne!\n");
         running = true;
      }
      
      
   }

}
void jeuencours1VSIA(){
   bool running = false;
      while (running == false)
   {
   // On demande au joueur1 de jouer
      printf("Joueur 1, c'est a vous de jouer\n");
      printf("Entrez la forme de la piece que vous voulez jouer\n");
      int forme1;
      scanf("%d",&forme1);
      piece pieceajoutee = creerPiece(forme1,1);
      printf("Entrez la position x de la piece que vous voulez jouer\n");
      int x1;
      scanf("%d",&x1);
      printf("Entrez la position y de la piece que vous voulez jouer\n");
      int y1;
      scanf("%d",&y1);
      grille plateau = creationplateau();
      plateau = ajoutpiece(plateau,pieceajoutee,x1,y1);
      if (victoire == true)
      {
         printf("Bravo vous avez gagne!\n");
         running = true;
      }
   // On demande au joueur2 de jouer
      printf("Joueur 2, c'est a vous de jouer\n");
      printf("Entrez la forme de la piece que vous voulez jouer\n");
      int forme2;
      scanf("%d",&forme2);
      piece pieceajoutee = creerPiece(forme2,1);
      printf("Entrez la position x de la piece que vous voulez jouer\n");
      int x2;
      scanf("%d",&x2);
      printf("Entrez la position y de la piece que vous voulez jouer\n");
      int y2;
      scanf("%d",&y2);
      grille plateau = creationplateau();
      plateau = ajoutpiece(plateau,pieceajoutee,x2,y2);
      if (victoire(plateau,x2,y2) == true)
      {
         printf("Bravo vous avez gagne!\n");
         running = true;
      }
}
}
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