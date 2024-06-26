#ifndef GARDIEN_UNIQUE_COUPS_H
#define GARDIEN_UNIQUE_COUPS_H

#include "situation.h"
typedef struct coups{
    int echange_pioche[5];
    int construction;
    int carte_donnee_marche[5];
    int carte_recu_marche[5];
    struct coup* coup_suivant;
}coups;



void suppprimer_1coup_possible(coups* coup);
void phase_echange_pioche_ordi(sitjoueur* joueur1,coups** tete);
void phase_echange_marche_ordi(sitjoueur* joueur1,coups** tete);
void phase_echange_ordi(sitjoueur* joueur1,coups** tete);
void phase_construction_ordi(sitjoueur* joueur1,coups** tete);
coups* liste_coup_possible(sitjoueur* joueur1);
void afficher_listes_coup_possible(coups* tete);
#endif // GARDIEN_UNIQUE_COUPS_H