#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "IA.h"
#include "SDL.h"
#include "jeu.h"

// Lit un coup au clavier : forme, ligne et colonne
static coups demandecoup(const grille *plateau) {
  coups c;
  while (1) {
    printf("Joueur %d, forme (1 cône, 2 cube, 3 cylindre, 4 sphère), ligne et colonne : ", plateau->trait + 1);
    if (scanf("%d %d %d", &c.forme, &c.x, &c.y) != 3) exit(0);
    bool dansplateau = c.x >= 0 && c.x < TAILLE && c.y >= 0 && c.y < TAILLE && c.forme >= cone && c.forme <= sphere;
    if (dansplateau && valide(plateau, plateau->trait, c.forme, c.x, c.y)) return c;
    printf("Coup interdit.\n");
  }
}

// Version terminal du jeu, utile pour tester sans interface graphique
static void jeuconsole(int contreia) {
  grille plateau;
  creationplateau(&plateau);
  affichageplateau(&plateau);
  while (1) {
    coups liste[NB_COUPS_MAX];
    if (coupspossibles(&plateau, liste) == 0) {
      printf("Le joueur %d ne peut plus jouer : le joueur %d gagne !\n", plateau.trait + 1, 2 - plateau.trait);
      return;
    }
    coups c;
    if (contreia && plateau.trait == joueur2) {
      c = trouver_meilleur_coup(&plateau, profondeurconseillee(&plateau), NULL);
      printf("L'IA joue la forme %d en (%d, %d)\n", c.forme, c.x, c.y);
    } else {
      c = demandecoup(&plateau);
    }
    int joueur = plateau.trait;
    jouercoup(&plateau, c);
    affichageplateau(&plateau);
    if (victoire(&plateau, c.x, c.y)) {
      printf("Le joueur %d gagne !\n", joueur + 1);
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));
  if (argc > 1 && strcmp(argv[1], "--console") == 0) {
    printf("Quantik : alignez 4 formes différentes en ligne, en colonne ou dans un carré.\n");
    printf("1 : contre l'IA, 2 : à deux joueurs ? ");
    int choix = 0;
    if (scanf("%d", &choix) != 1) return 1;
    jeuconsole(choix == 1);
    return 0;
  }
  return lancer_sdl();
}
