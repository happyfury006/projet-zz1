
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "construction.h"
#include "utils.h"


void actualiser_board(sitjoueur* joueur1,sitjoueur* joueur2, int construc)
{
    joueur1->tab_constru_board[construc]--;   //on enleve la carte de sa pile
    joueur2->tab_constru_board[construc]--;
    joueur1->tab_constru_joueur[construc]++;  //on ajoute la carte sur le board du joueur
}


void construction_route(sitjoueur* joueur1,sitjoueur* joueur2, int construc)
{
    joueur1->mainjoueur[0]--;  //on enleve 1 bois
    joueur1->mainjoueur[1]--;  //1 argile
    actualiser_board(joueur1,joueur2,construc);
    if(joueur1->tab_constru_joueur[construc]%2 == 1)
    {
        joueur1->nb_echanges_marchee+=1;
    }
    else
    {
        joueur1->compteur_points_joueur+=1;
    }
}


void construction_chevalier(sitjoueur* joueur1,sitjoueur* joueur2, int construc)
{
    joueur1->mainjoueur[2]--;  //on enleve 1 mouton
    joueur1->mainjoueur[3]--;  //1 minerai
    joueur1->mainjoueur[4]--;  //1 blé
    actualiser_board(joueur1,joueur2,construc);
    if(joueur1->tab_constru_joueur[construc]%2 == 1)
    {
        joueur1->nb_cartes_mainjoueur+=1;
    }
    else
    {
        joueur1->compteur_points_joueur+=1;
    }
}


void construction_colonie(sitjoueur* joueur1,sitjoueur* joueur2, int construc)
{
    joueur1->mainjoueur[0]--;  //1 bois
    joueur1->mainjoueur[1]--;  //1 argile
    joueur1->mainjoueur[2]--;  //on enleve 1 mouton
    joueur1->mainjoueur[4]--;  //1 blé
    actualiser_board(joueur1,joueur2,construc);
    joueur1->compteur_points_joueur+=1;
}


void construction_ville(sitjoueur* joueur1,sitjoueur* joueur2, int construc)
{
    joueur1->mainjoueur[3]-=3;  //on enleve 3 minerai
    joueur1->mainjoueur[4]-=2;  //2 blé
    actualiser_board(joueur1,joueur2,construc);
    joueur1->compteur_points_joueur+=2;
}


void construction_developpement(sitjoueur* joueur1,sitjoueur* joueur2, int construc)
{
    joueur1->mainjoueur[3]--;  //on enleve 1 minerai
    joueur1->mainjoueur[2]-=3;  //3 mouton
    actualiser_board(joueur1,joueur2,construc);
    joueur1->compteur_points_joueur+=3;
}


void construction(sitjoueur* joueur1,sitjoueur* joueur2, int construc)
{
    // int construc = carte_construction;
    switch (construc){
        case 0 :  //route
            construction_route(joueur1,joueur2,construc);
            break;

        case 1 :  //chevalier
            construction_chevalier(joueur1,joueur2,construc);
            break;

        case 2 :  //colonie
            construction_colonie(joueur1,joueur2,construc);
            break;

        case 3 :  //ville
            construction_ville(joueur1,joueur2,construc);
            break;

        case 4 :  //developpement
            construction_developpement(joueur1,joueur2,construc);
            break;
    }
}  
