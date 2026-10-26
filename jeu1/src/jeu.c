#include "jeu.h"

#include <stdio.h>

void creationplateau(grille *plateau) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      plateau->forme[i][j] = vide;
      plateau->joueur[i][j] = personne;
    }
  }
  for (int j = 0; j < 2; j++) {
    plateau->restantes[j][vide] = 0;
    for (int f = cone; f <= sphere; f++) {
      plateau->restantes[j][f] = NB_EXEMPLAIRES;
    }
  }
  plateau->trait = joueur1;
  plateau->nbcoups = 0;
}

// Numéro du carré 2 x 2 qui contient la case (x, y), de 0 à 3
int region(int x, int y) { return (x / 2) * 2 + y / 2; }

// La forme est interdite si l'adversaire l'a déjà posée dans la même ligne,
// la même colonne ou le même carré
bool valide(const grille *plateau, int numJoueur, int forme, int x, int y) {
  if (plateau->forme[x][y] != vide || plateau->restantes[numJoueur][forme] == 0) {
    return false;
  }
  int adversaire = 1 - numJoueur;
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      bool memezone = i == x || j == y || region(i, j) == region(x, y);
      if (memezone && plateau->forme[i][j] == forme && plateau->joueur[i][j] == adversaire) {
        return false;
      }
    }
  }
  return true;
}

// Remplit la liste des coups autorisés pour le joueur qui a le trait
int coupspossibles(const grille *plateau, coups liste[NB_COUPS_MAX]) {
  int n = 0;
  for (int forme = cone; forme <= sphere; forme++) {
    for (int x = 0; x < TAILLE; x++) {
      for (int y = 0; y < TAILLE; y++) {
        if (valide(plateau, plateau->trait, forme, x, y)) {
          liste[n++] = (coups){x, y, forme};
        }
      }
    }
  }
  return n;
}

void jouercoup(grille *plateau, coups coup) {
  plateau->forme[coup.x][coup.y] = coup.forme;
  plateau->joueur[coup.x][coup.y] = plateau->trait;
  plateau->restantes[plateau->trait][coup.forme]--;
  plateau->trait = 1 - plateau->trait;
  plateau->nbcoups++;
}

void annulercoup(grille *plateau, coups coup) {
  plateau->trait = 1 - plateau->trait;
  plateau->restantes[plateau->trait][coup.forme]++;
  plateau->forme[coup.x][coup.y] = vide;
  plateau->joueur[coup.x][coup.y] = personne;
  plateau->nbcoups--;
}

// Vrai si la ligne, la colonne ou le carré de (x, y) contient les quatre formes
static bool zonecomplete(const grille *plateau, int x, int y, int typezone) {
  bool vu[NB_FORMES + 1] = {false};
  int differentes = 0;
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      bool dedans = (typezone == 0 && i == x) || (typezone == 1 && j == y) ||
                    (typezone == 2 && region(i, j) == region(x, y));
      int f = plateau->forme[i][j];
      if (dedans && f != vide && !vu[f]) {
        vu[f] = true;
        differentes++;
      }
    }
  }
  return differentes == NB_FORMES;
}

// Vrai si la pièce posée en (x, y) a complété une ligne, une colonne ou un carré
bool victoire(const grille *plateau, int x, int y) {
  return zonecomplete(plateau, x, y, 0) || zonecomplete(plateau, x, y, 1) ||
         zonecomplete(plateau, x, y, 2);
}

bool coupgagnant(grille *plateau, coups coup) {
  jouercoup(plateau, coup);
  bool gagne = victoire(plateau, coup.x, coup.y);
  annulercoup(plateau, coup);
  return gagne;
}

void affichageplateau(const grille *plateau) {
  const char lettres[] = ".ABCD";  // A cône, B cube, C cylindre, D sphère
  printf("    0 1   2 3\n");
  for (int i = 0; i < TAILLE; i++) {
    if (i == 2) printf("   ----+----\n");
    printf("%d  ", i);
    for (int j = 0; j < TAILLE; j++) {
      if (j == 2) printf("| ");
      char c = lettres[plateau->forme[i][j]];
      // minuscules pour le joueur 2
      if (plateau->joueur[i][j] == joueur2) c = (char)(c - 'A' + 'a');
      printf("%c ", c);
    }
    printf("\n");
  }
}
