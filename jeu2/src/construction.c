
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "construction.h"
#include "utils.h"


void construction(sitjoueur* joueur1,sitjoueur* joueur2, carte* carte_construction)
{
    int construc = carte_construction
    switch (construc){
        case 0 :  //route
            joueur1->mainjoueur[0]--;  //on enleve 1 bois
            joueur1->mainjoueur[1]--;  //1 argile
            joueur1->tab_constru_board[construct]--;   //on enleve la carte de sa pile
            joueur2->tab_constru_board[construct]--;
            joueur1->tab_constru_joueur[construct]++;  //on ajoute la carte sur le board du joueur
            if(joueur1->tab_constru_joueur[construct]%2=1)
            {
                joueur1->nb_echanges_marchee+=1;
            }
            else
            {
                joueur1->compteur_points_joueur+=1;
            }
            break;

        case 1 :  //chevalier
            joueur1->mainjoueur[2]--;  //on enleve 1 mouton
            joueur1->mainjoueur[3]--;  //1 minerai
            joueur1->mainjoueur[4]--;  //1 blé
            joueur1->tab_constru_board[construct]--;   //on enleve la carte de sa pile
            joueur2->tab_constru_board[construct]--;
            joueur1->tab_constru_joueur[construct]++;  //on ajoute la carte sur le board du joueur
            if(joueur1->tab_constru_joueur[construct]%2=1)
            {
                joueur1->nb_cartes_mainjoueur+=1;
            }
            else
            {
                joueur1->compteur_points_joueur+=1;
            }
            break;

        case 2 :  //colonie
            joueur1->mainjoueur[0]--;  //1 bois
            joueur1->mainjoueur[1]--;  //1 argile
            joueur1->mainjoueur[2]--;  //on enleve 1 mouton
            joueur1->mainjoueur[4]--;  //1 blé
            joueur1->tab_constru_board[construct]--;   //on enleve la carte de sa pile
            joueur2->tab_constru_board[construct]--;
            joueur1->tab_constru_joueur[construct]++;  //on ajoute la carte sur le board du joueur
            joueur1->compteur_points_joueur+=1;
            break;

        case 3 :  //ville
            joueur1->mainjoueur[3]-=3;  //on enleve 3 minerai
            joueur1->mainjoueur[4]-=2;  //2 blé
            joueur1->tab_constru_board[construct]--;   //on enleve la carte de sa pile
            joueur2->tab_constru_board[construct]--;
            joueur1->tab_constru_joueur[construct]++;  //on ajoute la carte sur le board du joueur
            joueur1->compteur_points_joueur+=2;
            break;

        case 4 :  //developpement
            joueur1->mainjoueur[3]--;  //on enleve 1 minerai
            joueur1->mainjoueur[2]-=3;  //3 mouton
            joueur1->tab_constru_board[construct]--;   //on enleve la carte de sa pile
            joueur2->tab_constru_board[construct]--;
            joueur1->tab_constru_joueur[construct]++;  //on ajoute la carte sur le board du joueur
            joueur1->compteur_points_joueur+=3;
            break;
    }
}  
