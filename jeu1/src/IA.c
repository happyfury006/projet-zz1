#include "IA.h"
#include "jeu.h"
#include "utils.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


bool victoiretouteligne(grille* plat)
{
    for(int x=0; x<4; x++)
    {
        if(victoireligne(x,plat))
            return true;
    }
    return false;
}

bool victoiretoutecolonne(grille*plat)
{
    for(int y=0; y<4; y++)
    {
        if(victoirecolonne(y,plat))
            return true;
    }
    return false;
}


bool victoiretouteregion(grille*plat)
{
    if(victoireregion(0,0,plat)||victoireregion(3,0,plat)||victoireregion(0,3,plat)||victoireregion(3,3,plat))
        return true;
    
    return false;
}



int aligneligne(int x,grille* plateau,int n){
	list * lparcouru = malloc(sizeof(list));
	if (lparcouru == NULL)
	{
		return false;
	}
	lparcouru->piece = NULL;
	lparcouru->next = NULL;
	
	int scoreligne = 0;
	int i=0;
	int compteur = 0;
	while (i < 4 && victoire == false)
	{
		if (plateau->grid[x][i] != NULL && estdanslaliste(plateau->grid[x][i],lparcouru) == 0)
		{
			ajoutliste(plateau->grid[x][i],lparcouru);
			compteur++;
		}
		
		i++;
		
	}
    
	if (compteur == n)
    switch (n)
    {
    case 1:
        scoreligne = 1;
        break;
    case 2:
        scoreligne = 40;
        break;
    case 3:
        scoreligne = 1000;
        break;    
    default:
        break;
    }
	return scoreligne;
}

int alignecolonne(int y, grille* plateau,int n){
	list * lparcouru = malloc(sizeof(list));
	if (lparcouru == NULL)
	{
		return false;
	}
	lparcouru->piece = NULL;
	lparcouru->next = NULL;
	int scorecolonne = 0;
	int j=0;
	int compteur = 0;
	 while (j < 4 && victoire == false)
	 {
		if (plateau->grid[j][y] !=NULL &&estdanslaliste(plateau->grid[j][y],lparcouru) == 0)
		{
			ajoutliste(plateau->grid[j][y],lparcouru);
			compteur++;
		}
		j++;
	 }
	 if (compteur == n)
    switch (n)
    {
    case 1:
        scorecolonne = 1;
        break;
    case 2:
        scorecolonne = 40;
        break;
    case 3:
        scorecolonne = 1000;
        break;    
    default:
        break;
    }
	return scorecolonne;
}

int cherchealingeregion(int x,int y,grille* plateau, list * lparcouru,int n){
	int scoreregion = 0;
	int sectionx = x/2;
	int sectiony = y/2;
	int subsectionx = x%2;
	int subsectiony = y%2;
	int compteur = 0;
	for (int i = 2*sectionx; i <subsectionx+(sectionx*2) ; i++)
	{
		for (int j = 2*sectiony; j < subsectiony+(sectiony*2); j++)
		{
			if (plateau->grid[i][j] !=NULL && estdanslaliste(plateau->grid[i][j],lparcouru) == 0)
			{
				ajoutliste(plateau->grid[i][j],lparcouru);
				compteur++;
			} 
		}  
	}
	if (compteur == n)
    switch (n)
    {
    case 1:
        scoreregion = 1;
        break;
    case 2:
        scoreregion = 40;
        break;
    case 3:
        scoreregion = 1000;
        break;    
    default:
        break;
    }
	return scoreregion;
}

int aligneregion(int x, int y, grille* plateau,int n){
	int scoreregion = 0;
	
	list * lparcouru = malloc(sizeof(list));
	if (lparcouru == NULL)
	{
		return false;
	}
	lparcouru->piece = NULL;
	lparcouru->next = NULL;
	ajoutliste(plateau->grid[x][y],lparcouru);

	scoreregion = cherchealingeregion(x,y,plateau,lparcouru,n);
	return scoreregion;
		
}

int aligne(grille* plateau, int n){
	int score = 0;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            score+=aligneregion(x,y,plateau,n)+aligneligne(x,plateau,n)+alignecolonne(y,plateau,n);
        }
    }
	return score;
}


int evaluation(grille*plat, int profondeur)
{
    int score = 0;
    int paire = profondeur % 2;
    if(victoiretouteligne(plat) || victoiretoutecolonne(plat) || victoiretouteregion(plat))
    {
        if (paire)
            return 100000;
        else
            return -100000;
    }

    int score3=aligne(plat,3);
    int score2=aligne(plat,2);
    int score1=aligne(plat,1);

    if(paire)
    {
        score-=score3;
        score+=score2;
        score+=score1;
    }
    else
    {
        score+=score3;
        score-=score2;
        score-=score1;
    }
}


grille* grillecopie(grille* acopier) {
    grille* copie = (grille*)malloc(sizeof(grille));          //allocation de la copie
    for (int i = 0; i < 4; i++)                               //parcours de la grille
    {                                
        for (int j = 0; j < 4; j++)                             
        {
            if (acopier->grid[i][j] != NULL)                  //si la case n'est pas vide
            {
                copie->grid[i][j] = (piece*)malloc(sizeof(piece));      //on alloue la piece
                *(copie->grid[i][j]) = *(acopier->grid[i][j]);           //on copie la piece dans la copie
            } 
            else 
            {
                copie->grid[i][j] = NULL;
            }
        }
    }
    return copie;
}


arbre* generecoup(joueur jo1,joueur jo2,grille* plat,int profondeur,int profondeurmax){
    arbre* arb= (arbre*)malloc(sizeof(arbre));
    arb->plateau=plat;
    for(int i=0; i<4; i++)
    {
        if (jo1.piecerestante[i][1]>0)
        {
            for(int j=0; j<4; j++)
            {
                for(int k=0; k<4; k++)
                {
                    if(valide(i, jo1.numJoueur, j, k, plat))
                    {
                        grille* platcopie=grillecopie(plat);
                        platcopie=ajoutpiece(platcopie,jo1.piecerestante[i][0],jo1,j,k);
                        if (profondeur<profondeurmax)
                        {
                            profondeur-=1;
                            arbre* sousarb = arb->fils[0];
                            sousarb->derniercoup.x = j;
                            sousarb->derniercoup.y = k;
                            sousarb->derniercoup.joueur = jo1.numJoueur;
                            sousarb->derniercoup.forme = jo1.piecerestante[i][0];
                            sousarb=generecoup(jo2,jo1,platcopie,profondeur,profondeurmax);
                        }
                        profondeur+=1;
                    }
                }
            }
        }
    }
    return arb;
}


int minmax(arbre* noeud, int profondeur, int maximizingPlayer) {
    if (profondeur == 0)             //si c'est une feuille (de notre profondeur)
    {
        return evaluation(noeud->plateau,maximizingPlayer);
    }

    if (maximizingPlayer)             //on maximise pour le joueur
    {
        int maxEval = INT_MIN;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) 
        {
            int eval = minmax(noeud->fils[i], profondeur - 1, 0);
            if (eval > maxEval) 
            {
                maxEval = eval;
            }
        }
        return maxEval;
    } 
    else                                //on minimise pour l'adversaire
    {
        int minEval = INT_MAX;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) 
        {
            int eval = minmax(noeud->fils[i], profondeur - 1, 1);
            if (eval < minEval) 
            {
                minEval = eval;
            }
        }
        return minEval;
    }
}


int minmaxalphabeta(arbre* noeud, int profondeur, int maximizingPlayer, int alpha, int beta) {
    if (profondeur == 0) {
        return evaluer_plateau(noeud->plateau);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) {
            int eval = minmaxalphabeta(noeud->fils[i], profondeur - 1, 0, alpha, beta);
            if (eval > maxEval) {
                maxEval = eval;
            }
            if (eval > alpha) {
                alpha = eval;
            }
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < N && noeud->fils[i] != NULL; i++) {
            int eval = minmaxalphabeta(noeud->fils[i], profondeur - 1, 1, alpha, beta);
            if (eval < minEval) {
                minEval = eval;
            }
            if (eval < beta) {
                beta = eval;
            }
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}


coups trouver_meilleur_coup(arbre* racine, int profondeur) {
    int meilleur_valeur = INT_MIN;
    coups meilleur_coup;
    for (int i = 0; i < N && racine->fils[i] != NULL; i++) 
    {
        int valeur = minmax(racine->fils[i], profondeur - 1, 0);
        if (valeur > meilleur_valeur) 
        {
            meilleur_valeur = valeur;
            meilleur_coup = racine->fils[i]->derniercoup;
        }
    }
    return meilleur_coup;
}


