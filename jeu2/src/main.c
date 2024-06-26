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
#include "partie.h"
int main()
{
    srand(time(NULL));
    sitjoueur* joueur1 =creation_situation(1);
    sitjoueur* joueur2 =creation_situation(2);   
    // affichage(joueur1, joueur2);    
    partie(joueur1, joueur2);
    destruction_situation(joueur1);
    destruction_situation(joueur2);
    return 0;
}