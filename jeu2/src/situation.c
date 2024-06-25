#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
#include "situation.h"



situation* creation_situation(int joueur, int mainjoueur[5], int compteur_points_joueur, int nb_echanges, int nb_cartes_mainjoueur, int pioche[5], int nb_cartes_pioche, int defausse[5], int tab_constru_joueur[4], int tab_constru_advers[4], int tab_constru_board[4], int marcher[5])
{
  situation* s = malloc(sizeof(situation));
  s->joueur = joueur;
  for (int i = 0; i < 5; i++)
  {
    s->mainjoueur[i] = mainjoueur[i];
    s->pioche[i] = pioche[i];
    s->defausse[i] = defausse[i];
    s->marcher[i] = marcher[i];
  }
  s->compteur_points_joueur = compteur_points_joueur;
  s->nb_echanges = nb_echanges;
  s->nb_cartes_mainjoueur = nb_cartes_mainjoueur;
  s->nb_cartes_pioche = nb_cartes_pioche;
  for (int i = 0; i < 4; i++)
  {
    s->tab_constru_joueur[i] = tab_constru_joueur[i];
    s->tab_constru_advers[i] = tab_constru_advers[i];
    s->tab_constru_board[i] = tab_constru_board[i];
  }
  return s;
}