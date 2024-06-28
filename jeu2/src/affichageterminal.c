#include "affichageterminal.h"
#include "situation.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void affichagemainjoueur(sitjoueur *joueur) {
  for (int i = 0; i < NB_RESSOURCE; i++) {
    printf(" [%d] ", joueur->mainjoueur[i]);
  }
  printf("\n");
}

void affichagepioche(sitjoueur *joueur) {
  for (int i = 0; i < NB_RESSOURCE; i++) {
    printf(" [%d] ", joueur->pioche[i]);
  }
  printf("\n");
}
void affichagedefausse(sitjoueur *joueur) {
  for (int i = 0; i < NB_RESSOURCE; i++) {
    printf(" [%d] ", joueur->defausse[i]);
  }
  printf("\n");
}
void affichagemarchee(sitjoueur *joueur) {
  for (int i = 0; i < NB_RESSOURCE; i++) {
    printf(" [%d] ", joueur->marchee[i]);
  }
  printf("\n");
}
void affichagetab_constru_board(sitjoueur *joueur) {
  for (int i = 0; i < NB_CONSTRUCTION; i++) {
    printf(" [%d] ", joueur->tab_constru_board[i]);
  }
  printf("\n");
}
void affichagetab_constru_joueur(sitjoueur *joueur) {
  for (int i = 0; i < NB_CONSTRUCTION; i++) {
    printf(" [%d] ", joueur->tab_constru_joueur[i]);
  }
  printf("\n");
}
void affichage_joueur(sitjoueur *joueur) {
  printf("Joueur %d, points: %d\n", joueur->joueur,
         joueur->compteur_points_joueur);
  printf("================\n");
  printf("Main joueur %d\n", joueur->joueur);
  affichagemainjoueur(joueur);
  printf("Tab constru joueur %d\n", joueur->joueur);
  affichagetab_constru_joueur(joueur);
  printf("\n");
}

void affichage_board(sitjoueur *joueur) {
  printf("Situation Board\n");
  printf("================\n");
  printf("Tab constru board\n");
  affichagetab_constru_board(joueur);
  printf("Pioche \n");
  affichagepioche(joueur);
  printf("Defausse \n");
  affichagedefausse(joueur);
  printf("Marchee \n");
  affichagemarchee(joueur);
  printf("\n");
}

void affichage(sitjoueur *joueur1, sitjoueur *joueur2) {
  // printf("----------------\n");
  // printf("\n");
  // printf("Joueur 1, points: %d\n",joueur1->compteur_points_joueur);
  // printf("================\n");
  // printf("Main joueur 1\n");
  // affichagemainjoueur(joueur1);
  // printf("Tab constru joueur 1\n");
  // affichagetab_constru_joueur(joueur1);
  // printf("\n");
  // printf("----------------\n");
  // printf("\n");
  // printf("Situation Board\n");
  // printf("================\n");
  // printf("Tab constru board\n");
  // affichagetab_constru_board(joueur1);
  // printf("Pioche \n");
  // affichagepioche(joueur2);
  // printf("Defausse \n");
  // affichagedefausse(joueur2);
  // printf("Marchee \n");
  // affichagemarchee(joueur2);
  // printf("\n");
  // printf("----------------\n");
  // printf("\n");
  // printf("Joueur 2,points : %d\n",joueur2->compteur_points_joueur);
  // printf("================\n");
  // printf("Main joueur 2\n");
  // affichagemainjoueur(joueur2);
  // printf("Tab constru joueur 2\n");
  // affichagetab_constru_joueur(joueur2);
  // printf("\n");
  affichage_joueur(joueur1);
  affichage_board(joueur1);
  affichage_joueur(joueur2);
}