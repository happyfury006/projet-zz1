// Tests des règles et de l'IA : make test
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/action.h"
#include "../src/construction.h"
#include "../src/mcts.h"
#include "../src/regles.h"

#define NB_CARTES_RESSOURCE 62

static int total_cartes(const situation *s) {
  return nbr_carte_liste(s->pioche, NB_RESSOURCE) + nbr_carte_liste(s->defausse, NB_RESSOURCE) +
         nbr_carte_liste(s->marchee, NB_RESSOURCE) + nbr_carte_liste(s->joueurs[0].mainjoueur, NB_RESSOURCE) +
         nbr_carte_liste(s->joueurs[1].mainjoueur, NB_RESSOURCE);
}

static void donner(situation *s, int b, int a, int m, int mi, int bl) {
  int *main = s->joueurs[s->trait].mainjoueur;
  int voulu[NB_RESSOURCE] = {b, a, m, mi, bl};
  for (int r = 0; r < NB_RESSOURCE; r++) {  // on reprend les cartes à la pioche pour garder le compte
    s->pioche[r] += main[r] - voulu[r];
    main[r] = voulu[r];
  }
}

static void test_regles(void) {
  situation s;
  creation_situation(&s);
  assert(total_cartes(&s) == NB_CARTES_RESSOURCE);
  assert(nbr_carte_liste(s.marchee, NB_RESSOURCE) == TAILLE_MARCHE);
  assert(nbr_carte_liste(s.joueurs[0].mainjoueur, NB_RESSOURCE) == 4);  // 3 + chevalier de départ
  assert(nbr_carte_liste(s.joueurs[1].mainjoueur, NB_RESSOURCE) == 4);

  // route : la 2e route (face B) rapporte 1 point, la 3e (face A) un échange
  donner(&s, 1, 1, 0, 0, 0);
  assert(construction(&s, ROUTE));
  assert(s.joueurs[0].compteur_points_joueur == 1 && s.joueurs[0].nb_echanges_marchee == 1);
  assert(!construction(&s, ROUTE));  // une seule construction par tour
  fin_tour(&s);
  fin_tour(&s);
  donner(&s, 1, 1, 0, 0, 0);
  assert(construction(&s, ROUTE));
  assert(s.joueurs[0].nb_echanges_marchee == 2 && s.echanges_marchee_restants == 2);

  // ville : impossible sans colonie, puis jour du marché
  fin_tour(&s);
  fin_tour(&s);
  donner(&s, 0, 0, 0, 3, 2);
  assert(!valide_construction(&s, VILLE));
  donner(&s, 1, 1, 1, 0, 1);
  assert(construction(&s, COLONIE));
  fin_tour(&s);
  fin_tour(&s);
  donner(&s, 0, 0, 0, 3, 2);
  int defausse_avant = nbr_carte_liste(s.defausse, NB_RESSOURCE);
  assert(construction(&s, VILLE));
  assert(nbr_carte_liste(s.defausse, NB_RESSOURCE) == defausse_avant + 5 + 5);  // coût + ancien marché
  assert(nbr_carte_liste(s.marchee, NB_RESSOURCE) == TAILLE_MARCHE);
  assert(total_cartes(&s) == NB_CARTES_RESSOURCE);

  // échanges
  fin_tour(&s);
  fin_tour(&s);
  donner(&s, 2, 0, 0, 0, 0);
  int marche_bois = s.marchee[BOIS];
  int autre = -1;
  for (int r = 1; r < NB_RESSOURCE; r++) if (s.marchee[r] > 0) autre = r;
  assert(echanger_marchee(&s, BOIS, autre));
  assert(s.marchee[BOIS] == marche_bois + 1 && s.joueurs[0].mainjoueur[autre] == 1);
  assert(echanger_pioche(&s, BOIS) && echanger_pioche(&s, s.joueurs[0].mainjoueur[BOIS] ? BOIS : autre));
  assert(!valide_echange_pioche(&s, autre));  // 2 échanges avec la pioche au maximum
  assert(total_cartes(&s) == NB_CARTES_RESSOURCE);
  printf("règles : ok\n");
}

typedef enum { ALEATOIRE, GLOUTON, IA } strategie;

static int partie_auto(strategie j1, strategie j2, double *pire, int *tours) {
  situation s;
  creation_situation(&s);
  while (!s.finie && s.tour < 300) {
    strategie st = s.trait == 0 ? j1 : j2;
    action a;
    if (st == IA) {
      double t = (double)clock() / CLOCKS_PER_SEC;
      a = choisir_action_mcts(&s, ITERATIONS_IA);
      t = (double)clock() / CLOCKS_PER_SEC - t;
      if (t > *pire) *pire = t;
    } else if (st == GLOUTON) {
      a = choisir_action_glouton(&s);
    } else {
      action liste[NB_ACTIONS_MAX];
      a = liste[rand() % lister_actions(&s, liste)];
    }
    action liste[NB_ACTIONS_MAX];
    int n = lister_actions(&s, liste), legal = 0;
    for (int i = 0; i < n; i++) legal |= liste[i].type == a.type && liste[i].a == a.a && liste[i].b == a.b;
    assert(legal);
    appliquer_action(&s, a);
    assert(total_cartes(&s) == NB_CARTES_RESSOURCE);
  }
  *tours += s.tour;
  return s.finie ? s.gagnant : -1;
}

static void duel(const char *nom, strategie a, strategie b, int n, double *pire) {
  int gagnees = 0, egalites = 0, tours = 0;
  for (int i = 0; i < n; i++) {
    // chacun commence une partie sur deux
    int g = i % 2 == 0 ? partie_auto(a, b, pire, &tours) : partie_auto(b, a, pire, &tours);
    if (g < 0) egalites++;
    else if ((i % 2 == 0) == (g == 0)) gagnees++;
  }
  printf("%-28s %3d victoires, %d égalités sur %d (%.0f tours en moyenne)\n", nom, gagnees, egalites, n, (double)tours / n);
}

int main(void) {
  srand(7);
  test_regles();
  double pire = 0;
  duel("glouton contre aléatoire :", GLOUTON, ALEATOIRE, 100, &pire);
  duel("IA contre aléatoire :", IA, ALEATOIRE, 10, &pire);
  duel("IA contre glouton :", IA, GLOUTON, 30, &pire);
  printf("coup le plus long de l'IA : %.2f s\n", pire);
  return 0;
}
