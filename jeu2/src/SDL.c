#include "SDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "action.h"
#include "construction.h"
#include "mcts.h"
#include "regles.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define WINDOW_LARGEUR 1300
#define WINDOW_HAUTEUR 900
#define DELAI_IA 450  // pause entre deux actions de l'IA, en millisecondes

// Taille des cartes à l'écran
#define MAIN_W 110
#define MAIN_H 170
#define CARTE_W 95
#define CARTE_H 147
#define MINI_W 46
#define MINI_H 71

// Position des zones (coordonnées du jeu, avant mise à l'échelle)
#define PIOCHE_X 40
#define PIOCHE_Y 195
#define MARCHE_X 250
#define MARCHE_Y 195
#define CONSTRU_X 250
#define CONSTRU_Y 405
#define CONSTRU_PAS 130
#define MAIN_X 40
#define MAIN_Y 650
#define MAIN_PAS 120
#define PANNEAU_X 960
#define FIN_X 1030
#define FIN_Y 535

// Phases de l'interface, comme l'automate de la branche jeu2fixSDL
typedef enum { MENU, REGLES, TRANSITION, PARTIE, FIN } etat_t;

typedef struct textures {
  SDL_Texture *fond, *titre, *soustitre, *bouton_ia, *bouton_2j, *bouton_fin, *touches, *regles;
  SDL_Texture *lbl_pioche, *lbl_defausse, *lbl_marche, *lbl_constructions, *lbl_main, *lbl_ia, *lbl_j[2];
  SDL_Texture *lbl_points, *lbl_ech_pioche, *lbl_ech_marche, *aide, *ia_reflechit, *deja_construit;
  SDL_Texture *transition[2], *gagne[2], *egalite, *victoire, *defaite, *retour_menu, *chiffres;
  SDL_Texture *ressources[NB_RESSOURCE], *dos;
  SDL_Texture *constructions[NB_CONSTRUCTION][2];  // faces A et B (identiques sauf route et chevalier)
} textures;

typedef struct jeu_sdl {
  etat_t etat;
  bool contre_ia;
  situation s;
  int selection;  // ressource de la carte choisie dans la main, -1 sinon
} jeu_sdl;

static char chemin_images[1024];

static SDL_Texture *charger(SDL_Renderer *renderer, const char *nom) {
  char chemin[1200];
  snprintf(chemin, sizeof chemin, "%s%s", chemin_images, nom);
  SDL_Texture *t = IMG_LoadTexture(renderer, chemin);
  if (t == NULL) {
    fprintf(stderr, "Image introuvable : %s (%s)\n", chemin, IMG_GetError());
    exit(EXIT_FAILURE);
  }
  return t;
}

// Version web (make web) : dans un navigateur, le programme doit rendre la main
// à la page pour qu'elle affiche l'image et reçoive les clics. Sans effet dans
// la version de bureau.
static void rendre_la_main(int ms) {
#ifdef __EMSCRIPTEN__
  emscripten_sleep(ms);
#else
  (void)ms;
#endif
}

// ---------- dessin ----------

static void dessiner(SDL_Renderer *r, SDL_Texture *t, int x, int y) {
  SDL_Rect d = {x, y, 0, 0};
  SDL_QueryTexture(t, NULL, NULL, &d.w, &d.h);
  SDL_RenderCopy(r, t, NULL, &d);
}

static void dessiner_centre(SDL_Renderer *r, SDL_Texture *t, int cx, int cy) {
  int w, h;
  SDL_QueryTexture(t, NULL, NULL, &w, &h);
  dessiner(r, t, cx - w / 2, cy - h / 2);
}

static void carte(SDL_Renderer *r, SDL_Texture *t, SDL_Rect d, Uint8 opacite) {
  SDL_SetTextureAlphaMod(t, opacite);
  SDL_RenderCopy(r, t, NULL, &d);
  SDL_SetTextureAlphaMod(t, 255);
}

static void cadre(SDL_Renderer *r, SDL_Rect d, Uint8 rouge, Uint8 vert, Uint8 bleu) {
  SDL_SetRenderDrawColor(r, rouge, vert, bleu, 255);
  for (int e = 0; e < 4; e++) {
    SDL_Rect c = {d.x - 2 - e, d.y - 2 - e, d.w + 4 + 2 * e, d.h + 4 + 2 * e};
    SDL_RenderDrawRect(r, &c);
  }
}

// Fond clair semi-transparent : le parchemin est foncé dans les coins
static void panneau(SDL_Renderer *r, SDL_Rect d, Uint8 opacite) {
  SDL_SetRenderDrawColor(r, 246, 234, 208, opacite);
  SDL_RenderFillRect(r, &d);
}

// Image mise à l'échelle et centrée en (cx, cy)
static void dessiner_echelle(SDL_Renderer *r, SDL_Texture *t, int cx, int cy, float echelle) {
  int w, h;
  SDL_QueryTexture(t, NULL, NULL, &w, &h);
  SDL_Rect d = {cx - (int)(w * echelle) / 2, cy - (int)(h * echelle) / 2, (int)(w * echelle), (int)(h * echelle)};
  SDL_RenderCopy(r, t, NULL, &d);
}

// Écrit un nombre avec la planche de chiffres (30 x 46 par chiffre), à l'échelle voulue
static void nombre(SDL_Renderer *r, textures *tx, int n, int x, int y, float echelle) {
  char texte[12];
  snprintf(texte, sizeof texte, "%d", n);
  for (int i = 0; texte[i]; i++) {
    SDL_Rect src = {(texte[i] - '0') * 30, 0, 30, 46};
    SDL_Rect dst = {x + (int)(i * 22 * echelle), y, (int)(30 * echelle), (int)(46 * echelle)};
    SDL_RenderCopy(r, tx->chiffres, &src, &dst);
  }
}

// Texture de la prochaine carte construction (face A ou B selon ce que le joueur a déjà)
static SDL_Texture *texture_construction(textures *tx, const sitjoueur *j, int c, bool prochaine) {
  int n = j->tab_constru_joueur[c] + (prochaine ? 1 : 0);
  return tx->constructions[c][(c == ROUTE || c == CHEVALIER) && n % 2 == 0 ? 1 : 0];
}

// ---------- zones cliquables ----------

static int joueur_bas(const jeu_sdl *jeu) { return jeu->contre_ia ? 0 : jeu->s.trait; }

static SDL_Rect rect_marche(int i) { return (SDL_Rect){MARCHE_X + i * 105, MARCHE_Y, CARTE_W, CARTE_H}; }
static SDL_Rect rect_constru(int c) { return (SDL_Rect){CONSTRU_X + c * CONSTRU_PAS, CONSTRU_Y, CARTE_W, CARTE_H}; }
static SDL_Rect rect_main(int i) { return (SDL_Rect){MAIN_X + i * MAIN_PAS, MAIN_Y, MAIN_W, MAIN_H}; }
static const SDL_Rect RECT_PIOCHE = {PIOCHE_X, PIOCHE_Y, CARTE_W, CARTE_H};
static const SDL_Rect RECT_FIN = {FIN_X, FIN_Y, 230, 70};

// Les cartes d'un tas, rangées par ressource : liste[i] = ressource de la i-ème carte
static int etaler(const int tas[NB_RESSOURCE], int liste[64]) {
  int n = 0;
  for (int r = 0; r < NB_RESSOURCE; r++) {
    for (int k = 0; k < tas[r] && n < 64; k++) liste[n++] = r;
  }
  return n;
}

static bool est_tour_humain(const jeu_sdl *jeu) {
  return jeu->etat == PARTIE && !jeu->s.finie && !(jeu->contre_ia && jeu->s.trait == 1);
}

// ---------- affichage ----------

static void afficher_partie(SDL_Renderer *r, textures *tx, jeu_sdl *jeu, bool ia_reflechit) {
  situation *s = &jeu->s;
  int bas = joueur_bas(jeu), haut = 1 - bas;
  const sitjoueur *moi = &s->joueurs[bas], *lui = &s->joueurs[haut];
  bool a_moi = est_tour_humain(jeu);

  panneau(r, (SDL_Rect){10, 8, 1280, 116}, 110);
  panneau(r, (SDL_Rect){PANNEAU_X - 14, 150, 345, 345}, 110);
  panneau(r, (SDL_Rect){20, 150, 150, 340}, 80);

  // adversaire, en haut : nom, points, dos de ses cartes et ses constructions
  dessiner(r, jeu->contre_ia ? tx->lbl_ia : tx->lbl_j[haut], 20, 12);
  nombre(r, tx, lui->compteur_points_joueur, 30, 55, 1.0f);
  dessiner(r, tx->lbl_points, 70, 62);
  int n_lui = nbr_carte_liste(lui->mainjoueur, NB_RESSOURCE);
  for (int i = 0; i < n_lui; i++) carte(r, tx->dos, (SDL_Rect){430 + i * 50, 15, 60, 93}, 255);
  for (int c = 0; c < NB_CONSTRUCTION; c++) {
    if (lui->tab_constru_joueur[c] == 0) continue;
    carte(r, texture_construction(tx, lui, c, false), (SDL_Rect){900 + c * 76, 15, MINI_W, MINI_H}, 255);
    nombre(r, tx, lui->tab_constru_joueur[c], 905 + c * 76, 90, 0.6f);
  }

  // pioche et défausse
  dessiner(r, tx->lbl_pioche, PIOCHE_X - 4, 158);
  carte(r, tx->dos, RECT_PIOCHE, 255);
  nombre(r, tx, nbr_carte_liste(s->pioche, NB_RESSOURCE), PIOCHE_X + 25, PIOCHE_Y + CARTE_H + 6, 0.8f);
  dessiner(r, tx->lbl_defausse, PIOCHE_X - 4, 400);
  nombre(r, tx, nbr_carte_liste(s->defausse, NB_RESSOURCE), PIOCHE_X + 25, 440, 0.8f);

  // marché
  dessiner(r, tx->lbl_marche, MARCHE_X - 4, 158);
  int marche[64];
  int n_marche = etaler(s->marchee, marche);
  for (int i = 0; i < n_marche; i++) {
    SDL_Rect d = rect_marche(i);
    carte(r, tx->ressources[marche[i]], d, 255);
    if (a_moi && jeu->selection >= 0 && valide_echange_marchee(s, jeu->selection, marche[i])) cadre(r, d, 34, 160, 70);
  }
  if (a_moi && jeu->selection >= 0 && valide_echange_pioche(s, jeu->selection)) cadre(r, RECT_PIOCHE, 34, 160, 70);

  // constructions disponibles, avec leur coût en petites cartes ressource
  dessiner(r, tx->lbl_constructions, CONSTRU_X - 4, 368);
  for (int c = 0; c < NB_CONSTRUCTION; c++) {
    SDL_Rect d = rect_constru(c);
    bool possible = a_moi && valide_construction(s, c);
    carte(r, texture_construction(tx, moi, c, true), d, s->tab_constru_board[c] > 0 && (possible || !a_moi) ? 255 : 110);
    if (possible) cadre(r, d, 34, 160, 70);
    int k = 0;
    for (int res = 0; res < NB_RESSOURCE; res++) {
      for (int q = 0; q < GUIDE_CONSTRUCTION[c][res]; q++, k++) {
        carte(r, tx->ressources[res], (SDL_Rect){d.x - 10 + k * 24, d.y + CARTE_H + 8, 22, 34}, 255);
      }
    }
  }

  // panneau du joueur du bas
  dessiner(r, jeu->contre_ia ? tx->lbl_j[0] : tx->lbl_j[bas], PANNEAU_X, 158);
  nombre(r, tx, moi->compteur_points_joueur, PANNEAU_X + 10, 200, 1.0f);
  dessiner(r, tx->lbl_points, PANNEAU_X + 50, 207);
  if (s->trait == bas) {
    nombre(r, tx, s->echanges_pioche_restants, PANNEAU_X + 10, 255, 0.7f);
    dessiner(r, tx->lbl_ech_pioche, PANNEAU_X + 40, 252);
    nombre(r, tx, s->echanges_marchee_restants, PANNEAU_X + 10, 292, 0.7f);
    dessiner(r, tx->lbl_ech_marche, PANNEAU_X + 40, 289);
    if (s->a_construit) dessiner(r, tx->deja_construit, PANNEAU_X + 4, 326);
  }
  if (ia_reflechit) dessiner(r, tx->ia_reflechit, PANNEAU_X, 255);
  for (int c = 0; c < NB_CONSTRUCTION; c++) {
    if (moi->tab_constru_joueur[c] == 0) continue;
    carte(r, texture_construction(tx, moi, c, false), (SDL_Rect){PANNEAU_X + c * 62, 380, MINI_W, MINI_H}, 255);
    nombre(r, tx, moi->tab_constru_joueur[c], PANNEAU_X + 5 + c * 62, 455, 0.6f);
  }
  if (a_moi) dessiner(r, tx->bouton_fin, FIN_X, FIN_Y);

  // main du joueur du bas, la carte choisie est relevée
  dessiner(r, tx->lbl_main, MAIN_X - 4, 588);
  int main_bas[64];
  int n_main = etaler(moi->mainjoueur, main_bas);
  int choisie = -1;
  for (int i = 0; i < n_main; i++) {
    if (choisie < 0 && main_bas[i] == jeu->selection) choisie = i;
  }
  for (int i = 0; i < n_main; i++) {
    SDL_Rect d = rect_main(i);
    if (i == choisie) d.y -= 20;
    carte(r, tx->ressources[main_bas[i]], d, 255);
    if (i == choisie) cadre(r, d, 37, 99, 235);
  }
  if (a_moi) {
    panneau(r, (SDL_Rect){40, 857, 1220, 36}, 150);
    dessiner_centre(r, tx->aide, WINDOW_LARGEUR / 2, 875);
  }
}

static void afficher(SDL_Renderer *r, textures *tx, jeu_sdl *jeu, bool ia_reflechit) {
  SDL_SetRenderDrawColor(r, 120, 80, 40, 255);
  SDL_RenderClear(r);
  SDL_RenderCopy(r, tx->fond, NULL, NULL);
  SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);

  switch (jeu->etat) {
    case MENU:
      dessiner_centre(r, tx->titre, WINDOW_LARGEUR / 2, 200);
      dessiner_centre(r, tx->soustitre, WINDOW_LARGEUR / 2, 300);
      dessiner_centre(r, tx->bouton_ia, WINDOW_LARGEUR / 2, 470);
      dessiner_centre(r, tx->bouton_2j, WINDOW_LARGEUR / 2, 620);
      dessiner_centre(r, tx->touches, WINDOW_LARGEUR / 2, 830);
      break;
    case REGLES:
      dessiner_centre(r, tx->regles, WINDOW_LARGEUR / 2, WINDOW_HAUTEUR / 2 - 15);
      dessiner_centre(r, tx->touches, WINDOW_LARGEUR / 2, WINDOW_HAUTEUR - 40);
      break;
    case TRANSITION:  // à deux joueurs, on cache la main du joueur précédent
      dessiner_centre(r, tx->transition[jeu->s.trait], WINDOW_LARGEUR / 2, WINDOW_HAUTEUR / 2);
      break;
    case PARTIE:
      afficher_partie(r, tx, jeu, ia_reflechit);
      break;
    case FIN: {
      afficher_partie(r, tx, jeu, false);
      SDL_SetRenderDrawColor(r, 40, 25, 10, 150);
      SDL_RenderFillRect(r, NULL);
      // résultat et score final dans un panneau clair
      int g = jeu->s.gagnant, cx = WINDOW_LARGEUR / 2, cy = WINDOW_HAUTEUR / 2;
      panneau(r, (SDL_Rect){cx - 330, cy - 200, 660, 390}, 240);
      cadre(r, (SDL_Rect){cx - 330, cy - 200, 660, 390}, 59, 36, 18);
      if (jeu->contre_ia && g >= 0) {
        dessiner_echelle(r, g == 0 ? tx->victoire : tx->defaite, cx, cy - 70, g == 0 ? 0.36f : 1.4f);
      } else {
        dessiner_centre(r, g < 0 ? tx->egalite : tx->gagne[g], cx, cy - 70);
      }
      SDL_Texture *noms[2] = {tx->lbl_j[0], jeu->contre_ia ? tx->lbl_ia : tx->lbl_j[1]};
      for (int j = 0; j < 2; j++) {
        dessiner(r, noms[j], cx - 230 + j * 270, cy + 55);
        nombre(r, tx, jeu->s.joueurs[j].compteur_points_joueur, cx - 230 + j * 270, cy + 92, 1.0f);
        dessiner(r, tx->lbl_points, cx - 190 + j * 270, cy + 99);
      }
      dessiner_centre(r, tx->retour_menu, cx, cy + 165);
      break;
    }
  }
  SDL_RenderPresent(r);
}

// ---------- actions ----------

static void apres_action(jeu_sdl *jeu, int trait_avant) {
  if (jeu->s.finie) {
    jeu->etat = FIN;
  } else if (jeu->s.trait != trait_avant && !jeu->contre_ia) {
    jeu->etat = TRANSITION;
  }
  // la carte choisie n'est plus dans la main
  if (jeu->selection >= 0 && jeu->s.joueurs[jeu->s.trait].mainjoueur[jeu->selection] == 0) jeu->selection = -1;
}

static void jouer(jeu_sdl *jeu, action a) {
  int trait = jeu->s.trait;
  appliquer_action(&jeu->s, a);
  if (a.type != CONSTRUIRE) jeu->selection = -1;
  apres_action(jeu, trait);
}

static void tour_ia(SDL_Renderer *r, textures *tx, jeu_sdl *jeu) {
  while (jeu->etat == PARTIE && !jeu->s.finie && jeu->s.trait == 1) {
    afficher(r, tx, jeu, true);
    rendre_la_main(0);  // le message « L'IA réfléchit » s'affiche avant le calcul
    action a = choisir_action_mcts(&jeu->s, ITERATIONS_IA);
    jouer(jeu, a);
    afficher(r, tx, jeu, a.type != FIN_TOUR);
    SDL_Delay(DELAI_IA);
  }
  SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);  // les clics pendant le tour de l'IA sont ignorés
}

static void clic_partie(jeu_sdl *jeu, SDL_Point souris) {
  situation *s = &jeu->s;
  if (SDL_PointInRect(&souris, &RECT_FIN)) {
    jouer(jeu, (action){FIN_TOUR, 0, 0});
    return;
  }
  for (int c = 0; c < NB_CONSTRUCTION; c++) {
    SDL_Rect d = rect_constru(c);
    if (SDL_PointInRect(&souris, &d)) {
      if (valide_construction(s, c)) jouer(jeu, (action){CONSTRUIRE, c, 0});
      return;
    }
  }
  int liste[64];
  int n = etaler(s->joueurs[s->trait].mainjoueur, liste);
  for (int i = n - 1; i >= 0; i--) {  // de droite à gauche : les cartes se chevauchent légèrement
    SDL_Rect d = rect_main(i);
    if (SDL_PointInRect(&souris, &d)) {
      jeu->selection = jeu->selection == liste[i] ? -1 : liste[i];
      return;
    }
  }
  if (jeu->selection < 0) return;
  if (SDL_PointInRect(&souris, &RECT_PIOCHE)) {
    if (valide_echange_pioche(s, jeu->selection)) jouer(jeu, (action){ECHANGE_PIOCHE, jeu->selection, 0});
    return;
  }
  n = etaler(s->marchee, liste);
  for (int i = 0; i < n; i++) {
    SDL_Rect d = rect_marche(i);
    if (SDL_PointInRect(&souris, &d) && valide_echange_marchee(s, jeu->selection, liste[i])) {
      jouer(jeu, (action){ECHANGE_MARCHEE, jeu->selection, liste[i]});
      return;
    }
  }
}

static void clic_menu(jeu_sdl *jeu, textures *tx, SDL_Point souris) {
  SDL_Texture *boutons[2] = {tx->bouton_ia, tx->bouton_2j};
  int centres[2] = {470, 620};
  for (int b = 0; b < 2; b++) {
    SDL_Rect d;
    SDL_QueryTexture(boutons[b], NULL, NULL, &d.w, &d.h);
    d.x = WINDOW_LARGEUR / 2 - d.w / 2;
    d.y = centres[b] - d.h / 2;
    if (SDL_PointInRect(&souris, &d)) {
      jeu->contre_ia = b == 0;
      creation_situation(&jeu->s);
      jeu->selection = -1;
      jeu->etat = REGLES;
    }
  }
}

// Traite un événement clavier ou souris ; renvoie faux pour quitter le jeu
static bool traiter_evenement(SDL_Window *window, jeu_sdl *jeu, textures *tx, const SDL_Event *e) {
  switch (e->type) {
    case SDL_QUIT:
      return false;
    case SDL_WINDOWEVENT:
      // fenêtre redimensionnée : on recalcule la mise à l'échelle
      if (e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        SDL_RenderSetLogicalSize(SDL_GetRenderer(window), WINDOW_LARGEUR, WINDOW_HAUTEUR);
      }
      break;
    case SDL_KEYDOWN: {
      bool plein_ecran = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
      if (e->key.keysym.sym == SDLK_f) {
        SDL_SetWindowFullscreen(window, plein_ecran ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
      } else if (e->key.keysym.sym == SDLK_ESCAPE) {
        if (plein_ecran) SDL_SetWindowFullscreen(window, 0);
        else jeu->etat = MENU;
      }
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      if (e->button.button != SDL_BUTTON_LEFT) break;
      SDL_Point souris = {e->button.x, e->button.y};
      switch (jeu->etat) {
        case MENU: clic_menu(jeu, tx, souris); break;
        case REGLES:
        case TRANSITION: jeu->etat = PARTIE; break;
        case FIN: jeu->etat = MENU; break;
        case PARTIE:
          if (est_tour_humain(jeu)) clic_partie(jeu, souris);
          break;
      }
      break;
    }
  }
  return true;
}

// ---------- chargement et boucle principale ----------

static void charger_textures(SDL_Renderer *r, textures *tx) {
  *tx = (textures){
      .fond = charger(r, "background.png"),
      .titre = charger(r, "titre.png"),
      .soustitre = charger(r, "soustitre.png"),
      .bouton_ia = charger(r, "bouton_ia.png"),
      .bouton_2j = charger(r, "bouton_2j.png"),
      .bouton_fin = charger(r, "bouton_fin.png"),
      .touches = charger(r, "touches.png"),
      .regles = charger(r, "regles_detail.png"),
      .lbl_pioche = charger(r, "lbl_pioche.png"),
      .lbl_defausse = charger(r, "lbl_defausse.png"),
      .lbl_marche = charger(r, "lbl_marche.png"),
      .lbl_constructions = charger(r, "lbl_constructions.png"),
      .lbl_main = charger(r, "lbl_main.png"),
      .lbl_ia = charger(r, "lbl_ia.png"),
      .lbl_j = {charger(r, "lbl_j1.png"), charger(r, "lbl_j2.png")},
      .lbl_points = charger(r, "lbl_points.png"),
      .lbl_ech_pioche = charger(r, "lbl_ech_pioche.png"),
      .lbl_ech_marche = charger(r, "lbl_ech_marche.png"),
      .aide = charger(r, "aide.png"),
      .ia_reflechit = charger(r, "ia_reflechit.png"),
      .deja_construit = charger(r, "deja_construit.png"),
      .transition = {charger(r, "transition1.png"), charger(r, "transition2.png")},
      .gagne = {charger(r, "gagne_j1.png"), charger(r, "gagne_j2.png")},
      .egalite = charger(r, "egalite.png"),
      .victoire = charger(r, "victoire.png"),
      .defaite = charger(r, "defaite.png"),
      .retour_menu = charger(r, "retour_menu.png"),
      .chiffres = charger(r, "chiffres.png"),
      .dos = charger(r, "dos.png"),
      .ressources = {charger(r, "ressource_bois.png"), charger(r, "ressource_argile.png"),
                     charger(r, "ressource_mouton.png"), charger(r, "ressource_minerai.png"),
                     charger(r, "ressource_ble.png")},
  };
  tx->constructions[ROUTE][0] = charger(r, "routeA.png");
  tx->constructions[ROUTE][1] = charger(r, "routeB.png");
  tx->constructions[CHEVALIER][0] = charger(r, "chevalierA.png");
  tx->constructions[CHEVALIER][1] = charger(r, "chevalierB.png");
  tx->constructions[COLONIE][0] = tx->constructions[COLONIE][1] = charger(r, "colonie.png");
  tx->constructions[VILLE][0] = tx->constructions[VILLE][1] = charger(r, "ville.png");
  tx->constructions[CARTE_DEVELOPPEMENT][0] = tx->constructions[CARTE_DEVELOPPEMENT][1] =
      charger(r, "developpement_eglise.png");
}

int lancer_sdl(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    return 1;
  }
  IMG_Init(IMG_INIT_PNG);
#ifdef __EMSCRIPTEN__
  // version web : les images sont empaquetées dans /Images (--preload-file)
  snprintf(chemin_images, sizeof chemin_images, "/Images/");
#else
  // les images sont dans jeu2/Images, l'exécutable dans jeu2/build
  char *base = SDL_GetBasePath();
  snprintf(chemin_images, sizeof chemin_images, "%s../Images/", base ? base : "./");
  SDL_free(base);
#endif

  // fenêtre adaptée à l'écran : le jeu est dessiné en 1300 x 900 puis mis à l'échelle
  SDL_Rect ecran = {0, 0, WINDOW_LARGEUR, WINDOW_HAUTEUR};
  SDL_GetDisplayUsableBounds(0, &ecran);
  float echelle = SDL_min(1.0f, SDL_min(0.92f * ecran.w / WINDOW_LARGEUR, 0.92f * ecran.h / WINDOW_HAUTEUR));
#ifdef __EMSCRIPTEN__
  echelle = 1.0f;  // dans la page web, c'est le CSS qui adapte le canvas à l'écran
#endif
  SDL_Window *window = SDL_CreateWindow("Catane", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        (int)(WINDOW_LARGEUR * echelle), (int)(WINDOW_HAUTEUR * echelle),
                                        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_RenderSetLogicalSize(renderer, WINDOW_LARGEUR, WINDOW_HAUTEUR);

  textures tx;
  charger_textures(renderer, &tx);
  jeu_sdl jeu = {.etat = MENU, .selection = -1};

  bool continuer = true;
  while (continuer) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (!traiter_evenement(window, &jeu, &tx, &e)) continuer = false;
    }
    if (jeu.contre_ia && jeu.etat == PARTIE && !jeu.s.finie && jeu.s.trait == 1) tour_ia(renderer, &tx, &jeu);
    afficher(renderer, &tx, &jeu, false);
    rendre_la_main(16);
  }

  SDL_DestroyRenderer(renderer);  // détruit aussi les textures
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
