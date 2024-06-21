#include "jeu.h"
#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"

//Varaibles globales
int forme;
int x;
int y;

joueur* creerjoueur(int numJoueur, int ia){
	joueur* newjoueur = (joueur*)malloc(sizeof(joueur));
	if (newjoueur != NULL)
	{
		newjoueur->numJoueur = numJoueur;
		newjoueur->ia = ia;
		for (int i = 0; i < 4; i++)
		{
			newjoueur->piecerestante[i][0] = i+1;
			newjoueur->piecerestante[i][1] = 2;
		}
	}
	return newjoueur;
}

piece* creerPiece(int forme,joueur* player){
	 piece* newpiece = (piece*)malloc(sizeof(piece));
	 if (newpiece != NULL)
	 {
		newpiece->formes = forme;
	  newpiece->joueur = player;
	 }
	 return newpiece;
}

grille* creationplateau() {
    grille* plateau = (grille*)malloc(sizeof(grille));  // Alloue de la mémoire pour la structure grille
    if (plateau == NULL) {
        // Gérer l'erreur d'allocation mémoire
        return NULL;
    }
		

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            plateau->grid[i][j] = NULL;
        }
    }
    return plateau;
}



bool valideligne(int x, int numJoueur,int forme, grille* plateau){
	bool possible = true;
	
	int i=0;
	
	while (i<4 && possible == true)
	{
		if ( plateau->grid[x][i] != NULL && plateau->grid[x][i]->formes == forme && plateau->grid[x][i]->joueur->numJoueur == numJoueur)
		{
			possible = false;
		}
		i++;
	}
	
	return possible;
}

bool validecolonne(int y, int numJoueur,int forme, grille *plateau){
	bool possible = true;
	int i=0;

	while (i<4 && possible == true)
	{
		if (plateau->grid[i][y] !=NULL && plateau->grid[i][y]->formes == forme && plateau->grid[i][y]->joueur->numJoueur == numJoueur)
		{
			possible = false;
		}
		i++;
	}
	return possible;
}

bool valideregion(int x, int y, int numJoueur,int forme, grille* plateau){
	bool possible = true;
	int sectionx = x/2;
	int sectiony = y/2;
	int subsectionx = x%2;
	int subsectiony = y%2;

	for (int i = 2*sectionx; i <subsectionx+(sectionx*2) ; i++)
	{
		for (int j = 2*sectiony; j < subsectiony+(sectiony*2); j++)
		{
			if (plateau->grid[i][j] !=NULL && plateau->grid[i][j]->formes == forme && plateau->grid[i][j]->joueur->numJoueur == numJoueur)
			{
				possible = false;
			}
		}
	}
	return possible;
}

bool valide(int forme, int numJoueur, int x, int y, grille* plateau) {
	if (plateau->grid[x][y] != NULL)
	{
<<<<<<< HEAD
		possible = true;
	}
	return possible;
}

grille ajoutpiece(grille plateau, int forme,int joueur, int x, int y){
	if (valide(forme,joueur,x,y,plateau) == true)
	{
		plateau.grid[x][y] = &pieceajoutee;
		return plateau;
=======
		return false;
>>>>>>> jeu1julen
	}
	else{
		return valideligne(x, numJoueur, forme, plateau) && validecolonne(y, numJoueur, forme, plateau) && valideregion(x, y, numJoueur, forme, plateau);
	}
}

grille* ajoutpiece(grille* plateau, piece* pieceajoutee,joueur* joueur, int x, int y) {
    if (valide(pieceajoutee->formes, joueur->numJoueur, x, y, plateau)) {
        plateau->grid[x][y] = pieceajoutee;
				joueur->piecerestante[pieceajoutee->formes-1][1]--;
    } else {
        printf("Impossible de placer la piece a cet endroit\n");
    }
    return plateau;
}
	
void affichageplateau(grille* plateau){
	printf("x   0    1    2    3\n");
	printf("y_____________________\n");
	for (int i = 0; i < 4; i++) {
		printf("%d|",i);
		for (int j = 0; j < 4; j++)
		{
			if (plateau->grid[i][j] == NULL)
			{
				printf("(0 0)");
			}
			else
			{
	    printf ("\033[34m(%d %d)\033[00m",plateau->grid[i][j]->joueur->numJoueur,plateau->grid[i][j]->formes);
			}
		}
		printf("|\n");
		
	}
	printf(" ---------------------\n");
}

bool victoireligne(int x,grille* plateau){
	list * lparcouru = malloc(sizeof(list));
	if (lparcouru == NULL)
	{
		return false;
	}
	lparcouru->piece = NULL;
	lparcouru->next = NULL;
	
	bool victoire = false;
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
	if (compteur == 4)
	{
		victoire = true;
		printf("Bravo vous avez fait une ligne!\n");
	}
	return victoire;
	 
}

bool victoirecolonne(int y, grille* plateau){
	list * lparcouru = malloc(sizeof(list));
	if (lparcouru == NULL)
	{
		return false;
	}
	lparcouru->piece = NULL;
	lparcouru->next = NULL;
	bool victoire = false;
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
	 if (compteur == 4)
	 {
		 victoire = true;
		printf("Bravo vous avez fait une colonne!\n");
	 }
	 return victoire;
}

bool chercheregion(int x,int y,grille* plateau, list * lparcouru){
	bool victoire = false;
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
	if (compteur == 4)
	{
		victoire = true;
		printf("Bravo vous avez fait une region!\n");
	}
	return victoire;
}

bool victoireregion(int x, int y, grille* plateau){
	bool victoire = false;
	
	list * lparcouru = malloc(sizeof(list));
	if (lparcouru == NULL)
	{
		return false;
	}
	lparcouru->piece = NULL;
	lparcouru->next = NULL;
	ajoutliste(plateau->grid[x][y],lparcouru);

	victoire = chercheregion(x,y,plateau,lparcouru);
	return victoire;
		
}

bool victoire(grille* plateau, int x, int y){
	bool victoire = false;
	if (victoireligne(x,plateau) == true || victoirecolonne(y,plateau) == true || victoireregion(x,y,plateau) == true)
	{
		victoire = true;
		
	}
	
	return victoire;
}

grille* demandepiece(grille* plateau,joueur* joueur){
	// On demande au joueur ce qu'il veut jouer
	
	printf("Entrez la forme de la piece que vous voulez jouer\n");
	scanf("%d",&forme);
	piece* pieceajoutee = creerPiece(forme,joueur);

	printf("Entrez la position x de la piece que vous voulez jouer\n");
	scanf("%d",&x);

	printf("Entrez la position y de la piece que vous voulez jouer\n");
	scanf("%d",&y);

	plateau = ajoutpiece(plateau,pieceajoutee,joueur,x,y);

	return plateau;

}


void jeuencours1VSIA(){
//    bool running = false;
//  grille* plateau = creationplateau();
// 	grille* newplateau=plateau;
// 	joueur* joueur1 = creerjoueur(1,0);
// 	joueur* joueurIA = creerjoueur(2,6);	
// 	affichageplateau(plateau);
	
//   while (running == false)
//    {
//       //Joueur1 joue
// 			newplateau = demandepiece(plateau,joueur1);
// 			affichageplateau(newplateau);

// 			bool victoryJ1 = victoire(newplateau,x,y);
      
// 			if (victoryJ1 == true)
//       {
//          printf("Bravo Joueur1 vous avez gagne!\n");
//          return true;
// 				 break;
//       }

//     //Joueur2 joue
// 			plateau=newplateau;
//       newplateau = demandepiece(plateau,joueurIA->numJoueur);
// 			affichageplateau(newplateau);
// 			bool victoryIA = victoire(newplateau,x,y);

//       if (victoryJ2 == true)
//       {
//          printf("L'IA gagne!\n");
//          return true;
//       }

// 			if (plateau==newplateau)
// 			{
				
// 			}
			
// 			plateau=newplateau;
}

bool jeuencours1VS1(){
  bool running = false;
  grille* plateau = creationplateau();
	grille* newplateau=plateau;
	joueur* joueur1 = creerjoueur(1,0);
	joueur* joueur2 = creerjoueur(2,0);	
	affichageplateau(plateau);
	
  while (running == false)
   {
      //Joueur1 joue
			printf("Joueur1 c'est a vous de jouez\n");
			newplateau = demandepiece(plateau,joueur1);
			affichageplateau(newplateau);

			bool victoryJ1 = victoire(newplateau,x,y);
      
			if (victoryJ1 == true)
      {
         printf("Bravo Joueur1 vous avez gagne!\n");
         return true;
				 break;
      }

    //Joueur2 joue
			plateau=newplateau;
			printf("Joueur2 c'est a vous de jouez\n");
      newplateau = demandepiece(plateau,joueur2);
			affichageplateau(newplateau);
			bool victoryJ2 = victoire(newplateau,x,y);

      if (victoryJ2 == true)
      {
         printf("Bravo Joueur2 vous avez gagne!\n");
         return true;
      }

			if (plateau==newplateau)
			{
				
			}
			
			plateau=newplateau;

}
}

// grille mainjeu(int x, int y, piece){;
// 	grille plateau = creationplateau();
// 	// coupjouer();
// 	// victoire(plateau);
// 	return plateau;

// }