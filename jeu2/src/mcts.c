#include "mcts.h"

#include <math.h>
#include <stdlib.h>

#include "action.h"
#include "construction.h"
#include "regles.h"

// ---------- actions ----------

int lister_actions(const situation *s, action liste[NB_ACTIONS_MAX]) {
  int n = 0;
  if (s->finie) return 0;
  for (int c = 0; c < NB_CONSTRUCTION; c++) {
    if (valide_construction(s, c)) liste[n++] = (action){CONSTRUIRE, c, 0};
  }
  for (int r = 0; r < NB_RESSOURCE; r++) {
    for (int m = 0; m < NB_RESSOURCE; m++) {
      if (valide_echange_marchee(s, r, m)) liste[n++] = (action){ECHANGE_MARCHEE, r, m};
    }
  }
  for (int r = 0; r < NB_RESSOURCE; r++) {
    if (valide_echange_pioche(s, r)) liste[n++] = (action){ECHANGE_PIOCHE, r, 0};
  }
  liste[n++] = (action){FIN_TOUR, 0, 0};
  return n;
}

void appliquer_action(situation *s, action a) {
  switch (a.type) {
    case ECHANGE_MARCHEE: echanger_marchee(s, a.a, a.b); break;
    case ECHANGE_PIOCHE: echanger_pioche(s, a.a); break;
    case CONSTRUIRE: construction(s, a.a); break;
    case FIN_TOUR: fin_tour(s); break;
  }
}

static bool memes_actions(action x, action y) { return x.type == y.type && x.a == y.a && x.b == y.b; }

// ---------- stratégie gloutonne (simulations et tests) ----------

// Intérêt d'une construction : ses points, et un petit bonus pour les faces A
// (un échange ou une carte de plus à chaque tour)
static double interet(const sitjoueur *j, int c) {
  bool face_a = j->tab_constru_joueur[c] % 2 == 0;  // la prochaine carte sera la face A
  switch (c) {
    case ROUTE: return face_a ? 0.8 : 1.0;
    case CHEVALIER: return face_a ? 0.9 : 1.0;
    case COLONIE: return 1.1;
    case VILLE: return 2.2;
    default: return 3.0;
  }
}

static int cartes_manquantes(const situation *s, int c) {
  const sitjoueur *j = &s->joueurs[s->trait];
  int manque = 0;
  for (int r = 0; r < NB_RESSOURCE; r++) {
    int d = GUIDE_CONSTRUCTION[c][r] - j->mainjoueur[r];
    if (d > 0) manque += d;
  }
  return manque;
}

// Construit la meilleure carte possible ; sinon échange une carte inutile
// contre une carte qui manque pour la construction la plus proche
action choisir_action_glouton(const situation *s) {
  const sitjoueur *j = &s->joueurs[s->trait];
  int meilleure = -1;
  for (int c = 0; c < NB_CONSTRUCTION; c++) {
    if (valide_construction(s, c) && (meilleure < 0 || interet(j, c) > interet(j, meilleure))) meilleure = c;
  }
  if (meilleure >= 0) return (action){CONSTRUIRE, meilleure, 0};
  if (s->a_construit) return (action){FIN_TOUR, 0, 0};

  // la construction la plus proche, à intérêt égal la plus rentable
  int cible = -1;
  double score_cible = -1e9;
  for (int c = 0; c < NB_CONSTRUCTION; c++) {
    if (s->tab_constru_board[c] == 0) continue;
    if (c == VILLE && j->tab_constru_joueur[COLONIE] <= j->tab_constru_joueur[VILLE]) continue;
    double score = interet(j, c) - 1.2 * cartes_manquantes(s, c);
    if (score > score_cible) score_cible = score, cible = c;
  }
  if (cible < 0) return (action){FIN_TOUR, 0, 0};

  int inutile = -1;
  for (int r = 0; r < NB_RESSOURCE; r++) {
    if (j->mainjoueur[r] > GUIDE_CONSTRUCTION[cible][r]) inutile = r;
  }
  if (inutile < 0) return (action){FIN_TOUR, 0, 0};
  for (int r = 0; r < NB_RESSOURCE; r++) {
    if (j->mainjoueur[r] < GUIDE_CONSTRUCTION[cible][r] && valide_echange_marchee(s, inutile, r)) {
      return (action){ECHANGE_MARCHEE, inutile, r};
    }
  }
  if (valide_echange_pioche(s, inutile)) return (action){ECHANGE_PIOCHE, inutile, 0};
  return (action){FIN_TOUR, 0, 0};
}

// ---------- MCTS ----------
// L'arbre ne couvre que le tour de l'IA : chaque nœud est une suite d'actions
// depuis le début de la recherche. Comme la pioche est aléatoire, l'état n'est
// pas stocké dans les nœuds : il est rejoué à chaque itération (« open loop »).
// À la fin du tour, la partie est simulée jusqu'au bout avec la stratégie
// gloutonne pour les deux joueurs.

typedef struct noeud {
  action coup;
  int visites;
  double gains;
  int nb_enfants;
  struct noeud *enfants[NB_ACTIONS_MAX];
} noeud;

// L'IA ne voit pas la main de l'adversaire : on la retire au hasard parmi les
// cartes qu'elle ne connaît pas (pioche + main adverse)
static void determiniser(situation *s) {
  sitjoueur *adv = &s->joueurs[1 - s->trait];
  int taille = nbr_carte_liste(adv->mainjoueur, NB_RESSOURCE);
  for (int r = 0; r < NB_RESSOURCE; r++) {
    s->pioche[r] += adv->mainjoueur[r];
    adv->mainjoueur[r] = 0;
  }
  for (int k = 0; k < taille; k++) adv->mainjoueur[tirer_carte(s->pioche)]++;
}

static double simuler(situation *s, int joueur) {
  for (int coups = 0; !s->finie && coups < 2000; coups++) appliquer_action(s, choisir_action_glouton(s));
  if (!s->finie) return 0.5;
  return s->gagnant == joueur ? 1.0 : s->gagnant < 0 ? 0.5 : 0.0;
}

action choisir_action_mcts(const situation *depart, int iterations) {
  action liste[NB_ACTIONS_MAX];
  int n = lister_actions(depart, liste);
  if (n == 1) return liste[0];

  noeud *reserve = calloc((size_t)iterations + 1, sizeof(noeud));
  int utilises = 1;
  noeud *racine = &reserve[0];
  int joueur = depart->trait;

  for (int it = 0; it < iterations; it++) {
    situation s = *depart;
    determiniser(&s);
    noeud *chemin[64];
    int profondeur = 0;
    noeud *courant = racine;
    chemin[profondeur++] = courant;

    // sélection et expansion, tant qu'on est dans le tour de l'IA
    while (!s.finie && s.trait == joueur) {
      int nb = lister_actions(&s, liste);
      // une action légale pas encore essayée depuis ce nœud ?
      action nouvelle;
      bool trouvee = false;
      for (int i = 0; i < nb && !trouvee; i++) {
        bool deja = false;
        for (int e = 0; e < courant->nb_enfants && !deja; e++) deja = memes_actions(courant->enfants[e]->coup, liste[i]);
        if (!deja) nouvelle = liste[i], trouvee = true;
      }
      noeud *suivant = NULL;
      if (trouvee && utilises <= iterations) {
        suivant = &reserve[utilises++];
        suivant->coup = nouvelle;
        courant->enfants[courant->nb_enfants++] = suivant;
      } else {
        // UCB1 parmi les enfants dont l'action est légale ici
        double meilleur = -1;
        for (int e = 0; e < courant->nb_enfants; e++) {
          noeud *f = courant->enfants[e];
          bool legal = false;
          for (int i = 0; i < nb && !legal; i++) legal = memes_actions(f->coup, liste[i]);
          if (!legal) continue;
          double ucb = f->gains / f->visites + 0.7 * sqrt(log(courant->visites + 1) / f->visites);
          if (ucb > meilleur) meilleur = ucb, suivant = f;
        }
        if (suivant == NULL) break;
      }
      appliquer_action(&s, suivant->coup);
      courant = suivant;
      chemin[profondeur++] = courant;
      if (trouvee) break;  // nœud tout juste créé : on passe à la simulation
    }

    double resultat = simuler(&s, joueur);
    for (int p = 0; p < profondeur; p++) {
      chemin[p]->visites++;
      chemin[p]->gains += resultat;
    }
  }

  // l'action la plus visitée depuis la racine
  noeud *choix = racine->enfants[0];
  for (int e = 1; e < racine->nb_enfants; e++) {
    if (racine->enfants[e]->visites > choix->visites) choix = racine->enfants[e];
  }
  action meilleure = choix->coup;
  free(reserve);
  return meilleure;
}
