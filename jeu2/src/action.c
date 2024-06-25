#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "action.h"
#include "utils.h"





void defausser(sitjoueur* joueur1,sitjoueur* joueur2, int ressource1)
{
    if (joueur1->mainjoueur[ressource1] > 0) 
    {
        joueur1->mainjoueur[ressource1]--;
        joueur1->defausse[ressource1]++;
        joueur2->defausse[ressource1]++;
    }
}


void piocher(sitjoueur* joueur1,sitjoueur* joueur2, int nombre_carte)
{
    for (int i = 0; i < nombre_carte; i++) 
    {
        int nbr_random=randomiser(5);
        joueur1->pioche[nbr_random]--;
        joueur2->pioche[nbr_random]--;
        joueur1->mainjoueur[nbr_random]++;
    }
}
void initialisation_marchee(sitjoueur* joueur1,sitjoueur* joueur2)
{
    for (int i = 0; i < TAILLE_MARCHER; i++)
    {
        int nbr_random=randomiser(5);
        joueur1->marchee[nbr_random]++;
        joueur2->marchee[nbr_random]++;
    }
    
}


void echanger_marchee(sitjoueur* joueur1,sitjoueur* joueur2,int ressourcemain, int ressource)
{
    if (joueur1->mainjoueur[ressourcemain]>0 || joueur1->marchee[ressource]>0)
    {
        joueur1->mainjoueur[ressourcemain]--;
        joueur1->mainjoueur[ressource]++;
        joueur1->marchee[ressourcemain]++;
        joueur1->marchee[ressource]--;
        joueur2->marchee[ressourcemain]++;
        joueur2->marchee[ressource]--;
    }
}



void echanger_pioche(sitjoueur* joueur1,sitjoueur* joueur2, int num_ressources, ...)
{
    if(num_ressources<=joueur1->nb_echanges_marchee || num_ressources<= nbr_carte_liste(joueur1->pioche,5))
    {
        va_list args;
        va_start(args, num_ressources);

        for (int i = 0; i < num_ressources; i++) 
        {
            int ressource = va_arg(args, int);
            defausser(joueur1,joueur2,ressource);
        }

        va_end(args);

        piocher(joueur1,joueur2,num_ressources);
    }
}


void construction(sitjoueur* joueur1, int construction)
{
    // if()
    // {
        
    // }
}  
