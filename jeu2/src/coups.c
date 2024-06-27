#include <stdio.h>
#include <stdlib.h>
#include "coups.h"
#include "situation.h"


coups init_coups(){
  coups* coup = malloc(sizeof(coups));
  coup->coup_suivant = NULL;
  return *coup;
}


void suppprimer_1coup_possible(coups* coup){
  coups* copie_coups = coup;
    if(coup->coup_suivant != NULL){
        coup = coup->coup_suivant;
        free(copie_coups);
        
    }
    else{
        free(coup);
    }
}



void phase_echange_pioche_ordi(sitjoueur* joueur1,coups* coup){
  //Test tous les nombres d'echanges possibles et toutes les cartes possibles echanger avec la pioche
    
    for (int nb_echange = 0; nb_echange < 5; nb_echange++)
    {
      for (int choix_main = 0; choix_main < 5; choix_main++)
      {
        if (joueur1->mainjoueur[choix_main]>0)
        {
          coup->echange_pioche[choix_main]++;
        }
      }
    }
  
  
}
void phase_echange_marche_ordi(sitjoueur* joueur1,coups* coup){
  //Test tous les nombres d'echanges possibles et toutes les cartes possibles echanger avec le marche
    
  
    for (int nb_echange = 0; nb_echange < 5; nb_echange++)
    {
      for (int choix_main = 0; choix_main < 5; choix_main++)
      {
        if (joueur1->mainjoueur[choix_main]>0)
        {
            for (int choix_marche = 0; choix_marche < 5; choix_marche++)
            {
              if (joueur1->marchee[choix_marche]>0)
              {
                coup->carte_donnee_marche[choix_main]++;
                coup->carte_recu_marche[choix_marche]++;
              }
            }
        }
      }
    }
  
  
}


void phase_echange_ordi(sitjoueur* joueur,coups* coup){
  for (int choix = 0; choix < 2; choix++)
  {
    if (choix==0)
    {
      phase_echange_pioche_ordi(joueur,&coup);
    }
    if (choix==1)
    {
      phase_echange_marche_ordi(joueur,&coup);
    }
    
  }
  
}

void phase_construction_ordi(sitjoueur* joueur,coups* coup){
  for (int choix = 0; choix < 4; choix++)
  {
    if (valide_construction(joueur,choix)==1)
    {
      coup->construction = choix;
    }
  }
  
}
coups liste_coup_possible(sitjoueur* joueur){
  coups coup = init_coups();
  phase_echange_ordi(joueur, &coup);
  phase_construction_ordi(joueur, &coup);
  return coup;


}
