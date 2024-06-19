#include "jeu.h"
#include<stdio.h>
#include <stdbool.h>


piece creerPiece(int forme,int player){
    piece* newpiece = malloc(sizeof(piece));
    newpiece->formes = forme;
    newpiece->joueur = player;

    return *newpiece;
}


grille creationplateau(){
   grille plateau ;
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++)
      {
         plateau.grid[i][j] = NULL;
      }
      
      
   }
   return plateau;
}



void victoireligne(int x,grille plateau){
   list * lparcouru = NULL;
   bool victoire = true;
   int i=0;
    while (i < 4 && victoire == true)
    {
      if (estdanslaliste(plateau.grid[x][i],lparcouru) == 0)
      {
         ajoutliste(plateau.grid[x][i],lparcouru);
      }
      else
      {
         victoire = false;
      }
      i++;
    }
    if (victoire == true)
    {
      printf("Bravo vous avez fait une ligne!\n");
    }
    
    
}
void victoirecolonne(int y, grille plateau){
   list * lparcouru = NULL;
   bool victoire = true;
   int j=0;
    while (j < 4 && victoire == true)
    {
      if (estdanslaliste(plateau.grid[y][j],lparcouru) == 0)
      {
         ajoutliste(plateau.grid[y][j],lparcouru);
      }
      else
      {
         victoire = true;
      }
      j++;
    }
    if (victoire == true)
    {
      printf("Bravo vous avez fait une colonne!\n");
    }
    
    
}
void chercheregion(int dx,int dy, int fx,int fy){
   if 

}

void victoireregion(int x, int y, grille plateau){
    int ix=x%2;
    int iy=y%2;
    list* lparcouru = plateau.grid[x][y];
    if (x<2 )
    {
      if (y<2){
         switch (position)
         {
         case 0:
            
            break;
         
         default:
            break;
         }
         }
         
      else
      {
         /* code */
      }   
      }
      
      
      
    
   else{
      if (y<2){
         /* code */
      }
      else
      {
         /* code */
      }         
      }
    
}


void victoire(grille plateau, int x, int y){
   victoireligne(x,plateau);
   victoirecolonne(y,plateau);
   // victoireregion();
   printf("Bravo vous avez gagné !\n");
}


int main(){;
   grille plateau = creationplateau();
   // coupjouer();
   // victoire(plateau);
   return 0;

}