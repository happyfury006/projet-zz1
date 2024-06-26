#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "action.h"
#include "utils.h"


void defausser(sitjoueur* joueur1,sitjoueur* joueur2, int ressource1)
{
    if (ressource1<0 || ressource1>4)
    {
        printf("Ressource invalide\n");
    }
    else
    {
        if (joueur1->mainjoueur[ressource1] > 0) 
    {
        joueur1->mainjoueur[ressource1]--;
        joueur1->defausse[ressource1]++;
        joueur2->defausse[ressource1]++;
    }
    }
    
}


void piocher(sitjoueur* joueur1,sitjoueur* joueur2, int nombre_carte)
{
    // for (int i = 0; i < nombre_carte; i++) 
    // {
    //     int nbr_random=randomiser(5);
    //     joueur1->pioche[nbr_random]--;
    //     joueur2->pioche[nbr_random]--;
    //     joueur1->mainjoueur[nbr_random]++;
    // }
    while (nombre_carte>0)
    {
        int nbr_random=randomiser(5);
        if (joueur1->pioche[nbr_random]>0)
        {
            joueur1->pioche[nbr_random]--;
            joueur2->pioche[nbr_random]--;
            joueur1->mainjoueur[nbr_random]++;
            nombre_carte--;
        }
    }
    
}
void initialisation_marchee(sitjoueur* joueur1,sitjoueur* joueur2)
{
    for (int i = 0; i < TAILLE_MARCHER; i++)
    {
        int nbr_random=randomiser(5);
        joueur1->marchee[nbr_random]++;
        joueur2->marchee[nbr_random]++;
        joueur1->pioche[nbr_random]--;
        joueur2->pioche[nbr_random]--;
    }
    
}

int valide_nb_echange_marchee(sitjoueur* joueur1,int nombre_echange_voulu)
{
    if (nombre_echange_voulu<=joueur1->nb_echanges_marchee)
    {
        return 1;
    }
    return 0;
}
int valide_nb_echange_pioche(sitjoueur* joueur1,int nombre_echange_voulu)
{
    if (nombre_echange_voulu<=nbr_carte_liste(joueur1->pioche,5))
    {
        return 1;
    }
    return 0;
}

void echanger_marchee(sitjoueur* joueur1,sitjoueur* joueur2,int ressourcemain, int ressource)
{
    if (valide_nb_echange_marchee(joueur1,1)==1 && joueur1->mainjoueur[ressourcemain]>0 && joueur1->marchee[ressource]>0)
    {
        joueur1->mainjoueur[ressourcemain]--;
        joueur1->mainjoueur[ressource]++;
        joueur1->marchee[ressourcemain]++;
        joueur1->marchee[ressource]--;
        joueur2->marchee[ressourcemain]++;
        joueur2->marchee[ressource]--;
    }
    else
    {
        printf("Echange impossible\n");
    }
    
    
    // if (joueur1->mainjoueur[ressourcemain]>0 || joueur1->marchee[ressource]>0)
    // {
        
    // }
}

void echanger_pioche(sitjoueur* joueur1,sitjoueur* joueur2, int num_ressources)
{
    if(valide_nb_echange_pioche(joueur1,num_ressources)==1 )
    {
        defausser(joueur1,joueur2,num_ressources);
        piocher(joueur1,joueur2,1);
    }
    else
    {
        printf("Echange impossible\n");
    }
    
}

// void echanger_pioche(sitjoueur* joueur1,sitjoueur* joueur2, int num_ressources, ...)
// {
//     if(num_ressources<=joueur1->nb_echanges_marchee || num_ressources<= nbr_carte_liste(joueur1->pioche,5))
//     {
//         va_list args;
//         va_start(args, num_ressources);

//         for (int i = 0; i < num_ressources; i++) 
//         {
//             int ressource = va_arg(args, int);
//             defausser(joueur1,joueur2,ressource);
//         }

//         va_end(args);

//         piocher(joueur1,joueur2,num_ressources);
//     }
// }

