// Tests des règles et de l'IA : make test
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/IA.h"
#include "../src/jeu.h"

static double maintenant(void) { return (double)clock() / CLOCKS_PER_SEC; }

static void test_regles(void) {
  grille g;
  creationplateau(&g);
  jouercoup(&g, (coups){0, 0, cone});  // joueur 1 : cône en haut à gauche
  // joueur 2 ne peut pas poser de cône dans la même ligne, colonne ou carré
  assert(!valide(&g, joueur2, cone, 0, 3));
  assert(!valide(&g, joueur2, cone, 3, 0));
  assert(!valide(&g, joueur2, cone, 1, 1));
  assert(valide(&g, joueur2, cone, 2, 2));
  // mais joueur 1 peut reposer un cône à côté du sien
  assert(valide(&g, joueur1, cone, 0, 3));
  assert(!valide(&g, joueur2, cube, 0, 0));  // case occupée

  // victoire : quatre formes différentes dans une ligne, couleurs mélangées
  creationplateau(&g);
  jouercoup(&g, (coups){0, 0, cone});
  jouercoup(&g, (coups){3, 3, cube});
  jouercoup(&g, (coups){0, 1, cylindre});
  jouercoup(&g, (coups){0, 2, cube});
  assert(!victoire(&g, 0, 2));
  assert(coupgagnant(&g, (coups){0, 3, sphere}));
  assert(!coupgagnant(&g, (coups){1, 3, sphere}));
  // un carré
  creationplateau(&g);
  jouercoup(&g, (coups){2, 2, cone});
  jouercoup(&g, (coups){2, 3, cube});
  jouercoup(&g, (coups){3, 2, cylindre});
  assert(coupgagnant(&g, (coups){3, 3, sphere}));
  // les pièces s'épuisent
  creationplateau(&g);
  g.restantes[joueur1][cone] = 0;
  assert(!valide(&g, joueur1, cone, 1, 1));
  printf("règles : ok\n");
}

// Joue une partie, renvoie le gagnant ; un joueur « ia » vaut 1, aléatoire 0
static int partie(int ia1, int ia2, double *pire) {
  grille g;
  creationplateau(&g);
  while (1) {
    coups liste[NB_COUPS_MAX];
    int n = coupspossibles(&g, liste);
    if (n == 0) return 1 - g.trait;  // bloqué : l'autre gagne
    coups c;
    if ((g.trait == joueur1 ? ia1 : ia2)) {
      double t = maintenant();
      c = trouver_meilleur_coup(&g, profondeurconseillee(&g), NULL);
      t = maintenant() - t;
      if (t > *pire) *pire = t;
    } else {
      c = liste[rand() % n];
    }
    assert(valide(&g, g.trait, c.forme, c.x, c.y));
    int joueur = g.trait;
    jouercoup(&g, c);
    if (victoire(&g, c.x, c.y)) return joueur;
  }
}

int main(void) {
  srand(42);
  test_regles();
  double pire = 0;
  int n = 100, gagnees1 = 0, gagnees2 = 0;
  for (int i = 0; i < n; i++) gagnees1 += partie(1, 0, &pire) == joueur1;
  for (int i = 0; i < n; i++) gagnees2 += partie(0, 1, &pire) == joueur2;
  printf("IA contre aléatoire : %d/%d en commençant, %d/%d en second\n", gagnees1, n, gagnees2, n);
  int ia_contre_ia[2] = {0, 0};
  for (int i = 0; i < 20; i++) ia_contre_ia[partie(1, 1, &pire)]++;
  printf("IA contre IA : joueur 1 %d, joueur 2 %d sur 20\n", ia_contre_ia[0], ia_contre_ia[1]);
  printf("coup le plus long de l'IA : %.2f s\n", pire);
  return 0;
}
