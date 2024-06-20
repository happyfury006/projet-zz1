#include "jeu.h"
#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"


piece creerPiece(int forme,int player){
	 piece* newpiece = malloc(sizeof(piece));
	 newpiece->formes = forme;
	 newpiece->joueur = player;

	 return *newpiece;
}


grille creationplateau(){
	grille plateau ;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			plateau.grid[i][j] = NULL;
		}
	}
	return plateau;
}



grille ajoutpiece(grille plateau, piece pieceajoutee, int x, int y){
	plateau.grid[x][y] = &pieceajoutee;
	return plateau;
}

void affichageplateau(grille plateau){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			if (plateau.grid[i][j] == NULL)
			{
				printf("0");
			}
			else
			{
				printf("%d",plateau.grid[i][j]->formes);
			}
		}
		printf("\n");
	}
}

void victoireligne(int x,grille plateau){
	list * lparcouru = NULL;
	bool victoire = true;
	int i=0;
	 while (i < 4 && victoire == true)
	 {
		if (estdanslaliste(plateau.grid[x][i],lparcouru) == 0)
		{
			ajoutliste(plateau.grid[x][i],lparcouru);
		}
		else
		{
			victoire = false;
		}
		i++;
	 }
	 if (victoire == true)
	 {
		printf("Bravo vous avez fait une ligne!\n");
	 }
	 
	 
}
void victoirecolonne(int y, grille plateau){
	list * lparcouru = NULL;
	bool victoire = true;
	int j=0;
	 while (j < 4 && victoire == true)
	 {
		if (estdanslaliste(plateau.grid[y][j],lparcouru) == 0)
		{
			ajoutliste(plateau.grid[y][j],lparcouru);
		}
		else
		{
			victoire = false;
		}
		j++;
	 }
	 if (victoire == true)
	 {
		printf("Bravo vous avez fait une colonne!\n");
	 }
	 
}

void chercheregion(int x,int y,grille plateau, list * lparcouru){
	bool victoire = true;
	int sectionx = x/2;
	int sectiony = y/2;
	int subsectionx = x%2;
	int subsectiony = y%2;
	for (int i = sectionx; i <subsectionx ; i++)
	{
		for (int j = sectiony; j < subsectiony; j++)
		{
			if (estdanslaliste(plateau.grid[i][j],lparcouru) == 0)
			{
				ajoutliste(plateau.grid[i][j],lparcouru);
			}
			else
			{
				victoire = false;
			}  
		}  
	}
	if (victoire == true)
	{
		printf("Bravo vous avez fait une region!\n");
	}
	
}

void victoireregion(int x, int y, grille plateau){
	 int ix=x%2;
	 int iy=y%2;
	 list* lparcouru = plateau.grid[x][y];
	 chercheregion(ix,iy,plateau,lparcouru);
		
}


void victoire(grille plateau, int x, int y){
	victoireligne(x,plateau);
	victoirecolonne(y,plateau);
	// victoireregion();
	printf("Bravo vous avez gagné !\n");
}


grille mainjeu(int x, int y, piece){;
	grille plateau = creationplateau();
	// coupjouer();
	// victoire(plateau);
	return plateau;

}