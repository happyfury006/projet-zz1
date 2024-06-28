#include <stdio.h>
#include <stdlib.h>
#include "situation.h"
#include "utils.h"
#include "partie.h"
#include "regles.h"
#include "construction.h"
#include "victoire.h"



void phase_echange(sitjoueur* joueur1,sitjoueur* joueur2){
  //joueur1
  printf("voulez vous echanger avec la pioche : 0 ou avec le marché : 1 ?\n");
  int choix=0;
  scanf("%d",&choix);
  int nb_echange=0;
  printf("Combien de carte de votre main voulez vous echanger ?\n");
  scanf("%d",&nb_echange);
  nb_echange=min(nb_echange,2);
    if (choix==0)
    {
        for (int i = 0; i < nb_echange; i++){ 
        printf("Quel carte voulez vous echanger avec la pioche ?\n");
        int choix_main=0;
        scanf("%d",&choix_main);
        if (joueur1->mainjoueur[choix_main]>0)
        {
          echanger_pioche(joueur1,joueur2,choix_main);
        }
        else
        {
          printf("Echange impossible\n");
        }
        }
    }
    else
    {
        for (int i = 0; i < nb_echange; i++){ 
          
        printf("Quel carte de votre main voulez vous echanger avec le marche ?\n");
        int choix_main=0;
        scanf("%d",&choix_main);
        if (joueur1->mainjoueur[choix_main]>0)
        {
        printf("Quel carte du marche voulez vous echanger  ?\n");
        int choix_marche=0;
        scanf("%d",&choix_marche);
        echanger_marchee(joueur1,joueur2,choix_main,choix_marche);
        }
        else
        {
          printf("Echange impossible\n");
        }
      }      
    }
  }
  
void phase_pioche(sitjoueur* joueur1,sitjoueur* joueur2){
  //joueur1
  piocher(joueur1,joueur2,joueur1->nb_cartes_mainjoueur- nbr_carte_liste(joueur1->mainjoueur,5));
  //joueur2
  //piocher(joueur2,joueur1,joueur2->nb_cartes_mainjoueur- nbr_carte_liste(joueur2->mainjoueur,5));
}
void phase_construction(sitjoueur* joueur1,sitjoueur* joueur2){
  //joueur1
  printf("Quelle carte voulez vous construire ?\n");
  int choix=0;
  scanf("%d",&choix);
  if (valide_construction(joueur1,choix)==1)
  {
    construction(joueur1,joueur2,choix);
  }
  else
  {
    printf("Construction impossible\n");
  }
} 

void partie(sitjoueur* joueur1,sitjoueur* joueur2 ){
  int tour=1;
  initilisation_depart(joueur1,joueur2);
  // affichage(joueur1,joueur2);
  while(1){
    //Debut du tour
    printf("=============\n ");
    printf("|||Tour %d|||\n",tour);
    printf("=============\n ");
    printf("\n");
    //joueur1
    affichage(joueur1,joueur2);
    printf("----------------\n");
    printf("Tour Joueur 1\n");
    phase_pioche(joueur1,joueur2);
    affichage_joueur(joueur1);
    affichage_board(joueur1);
    printf("Action joueur 1\n");
    phase_echange(joueur1,joueur2);
    affichage_joueur(joueur1);
    affichage_board(joueur1);
    phase_construction(joueur1,joueur2);
    affichage_joueur(joueur1);
    affichage_board(joueur1);

    if(victoire(joueur1,joueur2)==1){
      printf("Victoire joueur 1\n");
      break;
    }
    //Joueur 2
    printf("----------------\n");
    printf("Tour Joueur 2\n");
    phase_pioche(joueur2,joueur1);
    affichage_joueur(joueur2);
    affichage_board(joueur2);
    
    printf("Action joueur 2\n");
    phase_echange(joueur2,joueur1);
    affichage_joueur(joueur2);
    affichage_board(joueur2);
    phase_construction(joueur2,joueur1);
    affichage_joueur(joueur2);
    affichage_board(joueur2);

    tour++;

    
    if(victoire(joueur1,joueur2)==2){
      printf("Victoire joueur 2\n");
      break;
    }
  }
}