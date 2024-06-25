#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "utils.h"

int randomiser(int N) 
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
    return compteur;
}