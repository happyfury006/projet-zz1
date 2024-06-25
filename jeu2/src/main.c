#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include "action.h"
#include "utils.h"
#include "construction.h"
#include "regles.h"
#include "situation.h"
#include "victoire.h"
//#include "SDL.h"
//#include "mcts.h"
#include "affichageterminal.h"

int main()
{
    srand(time(NULL));
    sitjoueur* joueur1 =creation_situation(1);
    sitjoueur* joueur2 =creation_situation(2);   
    affichage(joueur1, joueur2);    
    initilisation_depart(joueur1, joueur2);
    affichage(joueur1, joueur2);
    free(joueur1);
    free(joueur2);
    return 0;
}