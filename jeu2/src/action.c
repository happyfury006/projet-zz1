#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "action.c"


int random(int N) 
{
    srand(time(NULL));
    return rand() % N;
}


int nbr_carte_liste(int liste[], int N)
{
    int compteur=0;
    for (int i=0; i<N; i++)
    {
        compteur+=liste[i];
    }
}


void defausse(sitjoueur* joueur1,sitjoueur* joueur2, int ressource1)
{
    if (joueur1->mainjoueur[ressource] > 0) 
    {
        joueur1->mainjoueur[ressource]--;
        joueur1->defausse[ressource]++;
        joueur2->defausse[ressource]++;
    }
}


void pioche(sitjoueur* joueur1,sitjoueur* joueur2, int nombre_carte);
{
    for (int i = 0; i < nombre_carte; i++) 
    {
        int nbr_random=random(5);
        joueur1->pioche[nbr_random]--;
        joueur2->pioche[nbr_random]--;
        joueur1->mainjoueur[nbr_random]++;
    }
}



void echange_marche(sitjoueur* joueur1,sitjoueur* joueur2,int ressourcemain, int ressource)
{
    if (joueur1->mainjoueur[ressourcemain]>0 || joueur1->marche[ressource]>0)
    {
        joueur1->mainjoueur[ressourcemain]--;
        joueur1->mainjoueur[ressource]++;
        joueur1->marche[ressourcemain]++;
        joueur1->marche[ressource]--;
        joueur2->marche[ressourcemain]++;
        joueur2->marche[ressource]--;
    }
}



void echange_pioche(sitjoueur* joueur1,sitjoueur* joueur2, int num_ressources, ...)
{
    if(num_ressources<=joueur1->nb_echanges || num_ressources<= nbr_carte_liste(joueur1->pioche))
    {
        va_list args;
        va_start(args, num_ressources);

        for (int i = 0; i < num_ressources; i++) 
        {
            int ressource = va_arg(args, int);
            defausse(joueur1,joueur2,ressource);
        }

        va_end(args);

        pioche(joueur1,joueur2,num_ressources);
    }
}


void construction(sitjoueur* joueur1, int construction)
{
    
}  
