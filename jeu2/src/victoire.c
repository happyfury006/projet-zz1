#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "situation.h"
#include "victoire.h"
#include "utils.h"


bool victoire_point_obj(sitjoueur* joueur)
{
  if (joueur->compteur_points_joueur >= 10)
  {
    return true;
  }
  return false;
}

bool victoire_point_pioche(sitjoueur* joueur)
{
  if (nbr_carte_liste(joueur->pioche,5 )== 0)
  {
    return true;
  }
  return false;
}

int victoire(sitjoueur* joueur1,sitjoueur* joueur2)
{
  if (victoire_point_obj(joueur1) == true)
  {
    printf("Victoire du joueur %d\n", joueur1->joueur);
    return joueur1->joueur;
  }


  else if (victoire_point_pioche(joueur1) == true)
  {
    if (joueur1->compteur_points_joueur > joueur2->compteur_points_joueur)
    {
      printf("Victoire du joueur %d\n", joueur1->joueur);
      return joueur1->joueur;
    }
    else if (joueur1->compteur_points_joueur < joueur2->compteur_points_joueur)
    {
      printf("Victoire du joueur %d\n", joueur2->joueur);
      return joueur2->joueur;
    }
    else
    {
      printf("Egalité\n");
      return 0;
    }
  }
}
