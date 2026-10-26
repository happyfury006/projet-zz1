#ifndef GARDIEN_UNIQUE_UTILS_H
#define GARDIEN_UNIQUE_UTILS_H

// Constantes communes au jeu, à l'IA et à l'interface

#define TAILLE 4          // le plateau fait 4 x 4 cases
#define NB_FORMES 4       // quatre formes différentes
#define NB_EXEMPLAIRES 2  // chaque joueur a deux pièces de chaque forme
#define NB_COUPS_MAX (TAILLE * TAILLE * NB_FORMES)

enum formes {  // faire le lien entre la forme et un entier
  vide = 0,
  cone = 1,
  cube = 2,
  cylindre = 3,
  sphere = 4
};

enum joueurs {  // le joueur 1 a les pièces blanches, le joueur 2 les noires
  personne = -1,
  joueur1 = 0,
  joueur2 = 1
};

#endif
