#include "affichageterminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "situation.h"


void affichagemainjoueur(sitjoueur* joueur){
  for(int i=0; i<NB_RESSOURCE; i++){
    printf(" [%d] ",joueur->mainjoueur[i]);      
    }
  printf("\n"); 
}

void affichagepioche(sitjoueur* joueur){
  for(int i=0; i<NB_RESSOURCE; i++){
    printf(" [%d] ",joueur->pioche[i]);      
    }
  printf("\n"); 
}
void affichagemarchee(sitjoueur* joueur){
  for(int i=0; i<NB_RESSOURCE; i++){
    printf(" [%d] ",joueur->marchee[i]);      
    }
  printf("\n"); 
}
void affichagetab_constru_board(sitjoueur* joueur){
  for(int i=0; i<NB_CONSTRUCTION; i++){
    printf(" [%d] ",joueur->tab_constru_board[i]);      
    }
  printf("\n"); 
}
void affichagetab_constru_joueur(sitjoueur* joueur){
  for(int i=0; i<NB_CONSTRUCTION; i++){
    printf(" [%d] ",joueur->tab_constru_joueur[i]);      
    }
  printf("\n"); 
}

void affichage(sitjoueur* joueur1, sitjoueur* joueur2){
  printf("Joueur 1\n");
  printf("----------------\n");
  printf("Main joueur 1\n");
  affichagemainjoueur(joueur1);
  printf("Tab constru joueur 1\n");
  affichagetab_constru_joueur(joueur1);
  printf("Tab constru board\n");
  affichagetab_constru_board(joueur1);
  printf("Joueur 2\n");
  printf("----------------\n");
  printf("Main joueur 2\n");
  affichagemainjoueur(joueur2);
  printf("Pioche joueur 2\n");
  affichagepioche(joueur2);
  printf("Marchee joueur 2\n");
  affichagemarchee(joueur2);
  printf("Tab constru joueur 2\n");
  affichagetab_constru_joueur(joueur2);

}