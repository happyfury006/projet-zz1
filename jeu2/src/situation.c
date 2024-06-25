#include "situation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
#include "utils.h"





sitjoueur* creation_situation(int joueur)
{
  sitjoueur* s = malloc(sizeof(sitjoueur));
  s->joueur = joueur;
  //Initialisation des cartes ressources du joueur, de la defausse, du marcher, des constructions du joueur et de l'adversaire
  for (int i = 0; i < NB_RESSOURCE; i++)
  {
    s->mainjoueur[i] = 0;
    s->defausse[i] = 0;
    s->marchee[i] = 0;
    s->tab_constru_joueur[i] = 0;
    s->tab_constru_advers[i] = 0;
    
  }
  //Initialisation des cartes ressources de la pioche
  s->pioche[BOIS] = 11;
  s->pioche[ARGILE] = 11;
  s->pioche[MOUTON] = 15;
  s->pioche[BLE] = 14;
  s->pioche[MINERAI] = 11;

  //Initialisation des cartes du board construction
  s->tab_constru_board[ROUTE] = 9;
  s->tab_constru_board[CHEVALIER] = 14;
  s->tab_constru_board[COLONIE] = 15;
  s->tab_constru_board[VILLE] = 15;
  s->tab_constru_board[CARTE_DEVELOPPEMENT] = 9;


  s->compteur_points_joueur = 0;
  s->nb_echanges_marchee = 0;
  s->nb_cartes_mainjoueur = 3;
 
  
  
  return s;
}

sitjoueur* initilisation_depart(sitjoueur* joueur){
  
}

void destruction_situation(sitjoueur* s)
{
  free(s);
}
