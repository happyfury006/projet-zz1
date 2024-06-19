#include "jeu.h"
#include<stdio.h>
#include <bool.h>


piece creerPiece(forme forme,int player){
    newpiece = malloc(sizeof(piece));
    newpiece->formes = forme;
    newpiece->joueur = player;
    newpiece->x = NULL;
    newpiece->y = NULL;
    return 
}


piece** creationplateau(){
   piece** plateau = malloc(4 * sizeof(piece*));
   for (int i = 0; i < 4; i++) {
      plateau[i] = malloc(4 * sizeof(piece));
   }
   return plateau;
}



void victoireligne(int x,piece **plateau){
   list * listdejaparcouru = NULL;
   bool victoire = true;
   int i=0;
    while (i < 4)
    {
      if (estdanslaliste(plateau[x][i],listdejaparcouru) == 0)
      {
         ajoutliste(plateau[x][i],listdejaparcouru);
      }
      else
      {
         victoire = false;
      }
      i++;
    }
    
}
void victoirecolonne(int y){
   list * listdejaparcouru = NULL;
   bool victoire = TRUE;
   int j=0;
    while (j < 4)
    {
      if (estdanslaliste(plateau[y][j],listdejaparcouru) == 0)
      {
         ajoutliste(plateau[y][j],listdejaparcouru);
      }
      else
      {
         victoire = FALSE;
      }
      j++;
    }
    
}
// void victoireregion(int x, int y){
    
//     if (x<2 )
//     {
//       if (y<2)
//       {
//          /* code */
//       }
//       else
//       {
//          /* code */
//       }
      
      
//     }
//    else{
//       if (y<2){
//          /* code */
//       }
//       else
//       {
//          /* code */
//       }         
//       }
    
// }


void victoire(piece** plateau, int x, int y){
   victoireligne(x);
   victoirecolonne(y);
   // victoireregion();
   printf("Bravo vous avez gagné !\n");
}


int main(){;
   piece** plateau = creationplateau();
   // coupjouer();
   // victoire(plateau);
   return 0;

}