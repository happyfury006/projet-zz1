#ifndef GARDIEN_UNIQUE_IA_H
#define GARDIEN_UNIQUE_IA_H

#include "jeu.h"
#include <stdio.h>

#define N 4 * 16
#define PROFONDEUR 6

// fichier d'entete classique ou l'on declare les types necessaires,
// les fonctions implementees dans le fichier .c
// les declaration de variables globales externes

typedef struct coups {
  int x;
  int y;
  int joueur;
  int forme;
}coups;

typedef struct arbre {    // structure de l'arbre
  struct grille *plateau; // noeud : plateau actualisé
  struct arbre *fils[N];  // enfants : un tableau de sous arbres
  struct coups* derniercoup;
}arbre;

bool victoiretouteligne(grille *plat);
bool victoiretoutecolonne(grille *plat);
bool victoiretouteregion(grille *plat);
int aligneligne(int x, grille *plateau, int n);
int alignecolonne(int y, grille *plateau, int n);
int cherchealingeregion(int x, int y, grille *plateau, list *lparcouru, int n);
int aligneregion(int x, int y, grille *plateau, int n);
int aligne(grille *plateau, int n);
int evaluation(grille *plat, int profondeur);
grille *grillecopie(grille *acopier);
arbre *generecoup(joueur *jo1, joueur *jo2, grille *plat, int profondeur,int profondeurmax);
int minimax(arbre *noeud, int profondeur, int maximizingPlayer);
coups* trouver_meilleur_coup(arbre *racine, int profondeur);

#endif