#include "jeu.h"
#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"

// enum formes forme;

piece creerPiece(int forme,int player){
	 piece* newpiece = malloc(sizeof(piece));
	 if (newpiece != NULL)
	 {
		newpiece->formes = forme;
	 newpiece->joueur = player;

	 return *newpiece;
	 }
	 
	 
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

bool valideligne(int x, int joueur,int forme, grille plateau){
	bool possible = false;
	bool running = true;
	int i=0;
	piece pieceverif = creerPiece(forme,joueur);
	while (i<4 && running == true)
	{
		if (plateau.grid[x][i] == pieceverif)
		{
			running = false;
		}
		i++;
	}
	if (running == true)
	{
		possible = true;
	}
	return possible;
}

bool validecolonne(int y, int joueur,int forme, grille plateau){
	bool possible = false;
	bool running = true;
	int i=0;
	piece pieceverif = creerPiece(forme,joueur);
	while (i<4 && running == true)
	{
		if (plateau.grid[i][y] == pieceverif)
		{
			running = false;
		}
		i++;
	}
	if (running == true)
	{
		possible = true;
	}
	return possible;
}
bool valideregion(int x, int y, int joueur,int forme, grille plateau){
	bool possible = false;
	bool running = true;
	int sectionx = x/2;
	int sectiony = y/2;
	int subsectionx = x%2;
	int subsectiony = y%2;
	piece pieceverif = creerPiece(forme,joueur);
	for (int i = sectionx; i <subsectionx ; i++)
	{
		for (int j = sectiony; j < subsectiony; j++)
		{
			if (plateau.grid[i][j] == pieceverif)
			{
				running = false;
			}
		}
	}
	if (running == true)
	{
		possible = true;
	}
	return possible;
}

bool valide(int forme,int joueur,int x, int y, grille plateau){
	bool possible = false;
	if (valideligne(x,joueur,forme,plateau) == true || validecolonne(y,joueur,forme,plateau) == true || valideregion(x,y,joueur,forme,plateau) == true)
	{
		possible = true;
	}
	return possible;
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

bool victoireligne(int x,grille plateau){
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
	 return victoire;
	 
}
bool victoirecolonne(int y, grille plateau){
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
	 return victoire;
}

bool chercheregion(int x,int y,grille plateau, list * lparcouru){
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
	return victoire;
}

bool victoireregion(int x, int y, grille plateau){
	bool victoire = false;
	 int ix=x%2;
	 int iy=y%2;
	 list* lparcouru = plateau.grid[x][y];

	 victoire = chercheregion(ix,iy,plateau,lparcouru);
	 return victoire;
		
}


bool victoire(grille plateau, int x, int y){
	bool victoire = false;
	if (victoireligne(x,plateau) == true || victoirecolonne(y,plateau) == true || victoireregion(x,y,plateau) == true)
	{
		victoire = true;
	}
	// victoireligne(x,plateau);
	// victoirecolonne(y,plateau);
	// victoireregion(x,y,plateau);
	printf("Bravo vous avez gagné !\n");
	return victoire;
}

void jeuencours1VS1(){
   bool running = false;
   grille plateau = creationplateau();

      while (running == false)
   {
      // On demande au joueur de jouer
      printf("Joueur 1, c'est a vous de jouer\n");
      printf("Entrez la forme de la piece que vous voulez jouer\n");
      int forme;
      scanf("%d",&forme);
      piece pieceajoutee = creerPiece(forme,1);
      printf("Entrez la position x de la piece que vous voulez jouer\n");
      int x;
      scanf("%d",&x);
      printf("Entrez la position y de la piece que vous voulez jouer\n");
      int y;
      scanf("%d",&y);
      
      plateau = ajoutpiece(plateau,pieceajoutee,x,y);
      if (victoire == true)
      {
         printf("Bravo vous avez gagne!\n");
         running = true;
      }
      // On demande a l'IA de jouer
      printf("C'est au tour de l'IA de jouer\n");
      
      // plateau = ajoutpiece(plateau,pieceIA,xIA,yIA);
      if (victoire == true)
      {
         printf("L'IA a gagne!\n");
         running = true;
      }
   }

}
void jeuencours1VSIA(){
   bool running = false;
   grille plateau = creationplateau();
      while (running == false)
   {
   // On demande au joueur1 de jouer
      printf("Joueur 1, c'est a vous de jouer\n");
      printf("Entrez la forme de la piece que vous voulez jouer\n");
      int forme1;
      scanf("%d",&forme1);
      piece pieceajoutee = creerPiece(forme1,1);
      printf("Entrez la position x de la piece que vous voulez jouer\n");
      int x1;
      scanf("%d",&x1);
      printf("Entrez la position y de la piece que vous voulez jouer\n");
      int y1;
      scanf("%d",&y1);
      
      plateau = ajoutpiece(plateau,pieceajoutee,x1,y1);
      if (victoire == true)
      {
         printf("Bravo vous avez gagne!\n");
         running = true;
      }
   // On demande au joueur2 de jouer
      printf("Joueur 2, c'est a vous de jouer\n");
      printf("Entrez la forme de la piece que vous voulez jouer\n");
      int forme2;
      scanf("%d",&forme2);
      piece pieceajoutee = creerPiece(forme2,1);
      printf("Entrez la position x de la piece que vous voulez jouer\n");
      int x2;
      scanf("%d",&x2);
      printf("Entrez la position y de la piece que vous voulez jouer\n");
      int y2;
      scanf("%d",&y2);
      grille plateau = creationplateau();
      plateau = ajoutpiece(plateau,pieceajoutee,x2,y2);
      if (victoire(plateau,x2,y2) == true)
      {
         printf("Bravo vous avez gagne!\n");
         running = true;
      }
}
}

// grille mainjeu(int x, int y, piece){;
// 	grille plateau = creationplateau();
// 	// coupjouer();
// 	// victoire(plateau);
// 	return plateau;

// }