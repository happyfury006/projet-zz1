#include "SDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IA.h"
#include "jeu.h"

#define WINDOW_LARGEUR 1300
#define WINDOW_HAUTEUR 900
#define NB_PIECES (2 * NB_FORMES * NB_EXEMPLAIRES)
#define RAYON_CASE 60  // distance maximale pour lâcher une pièce sur une case

// Plateau (nouveaufond.png, 695 x 655) centré dans la fenêtre
#define PLATEAU_X ((WINDOW_LARGEUR - 695) / 2)
#define PLATEAU_Y ((WINDOW_HAUTEUR - 655) / 2)

// Centre des 16 cases, mesuré sur l'image du plateau
static const int CENTRE_X[TAILLE][TAILLE] = {
    {117, 256, 399, 543}, {117, 256, 399, 543}, {117, 258, 403, 548}, {117, 258, 403, 548}};
static const int CENTRE_Y[TAILLE] = {104, 252, 383, 556};

typedef enum { MENU, REGLES, PARTIE, FIN } etat_t;

typedef struct piece {  // une pièce affichée à l'écran
  SDL_Texture *texture;
  SDL_Rect rect;    // position actuelle
  SDL_Rect depart;  // position dans la réserve
  int forme;
  int joueur;
  bool posee;
} piece;

typedef struct textures {
  SDL_Texture *fond, *plateau, *titre, *regles, *un_joueur, *deux_joueurs;
  SDL_Texture *joueur[2], *ia, *gagne[2], *ia_gagne, *reflexion, *retour_menu;
  SDL_Texture *regles_detail, *touches;
  SDL_Texture *formes[2][NB_FORMES + 1];
} textures;

typedef struct jeu_sdl {
  etat_t etat;
  int contre_ia;  // 1 : le joueur 2 est l'IA
  grille plateau;
  piece pieces[NB_PIECES];
  int deplacee;  // pièce en cours de glisser-déposer, -1 sinon
  int gagnant;
  bool zone_gagnante[TAILLE][TAILLE];
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

static void dessiner(SDL_Renderer *renderer, SDL_Texture *t, int x, int y, float echelle) {
  SDL_Rect r = {x, y, 0, 0};
  SDL_QueryTexture(t, NULL, NULL, &r.w, &r.h);
  r.w = (int)(r.w * echelle);
  r.h = (int)(r.h * echelle);
  SDL_RenderCopy(renderer, t, NULL, &r);
}

static void dessiner_centre(SDL_Renderer *renderer, SDL_Texture *t, int cx, int cy) {
  int w, h;
  SDL_QueryTexture(t, NULL, NULL, &w, &h);
  dessiner(renderer, t, cx - w / 2, cy - h / 2, 1.0f);
}

static void disque(SDL_Renderer *renderer, int cx, int cy, int r) {
  for (int dy = -r; dy <= r; dy++) {
    int dx = 0;
    while ((dx + 1) * (dx + 1) + dy * dy <= r * r) dx++;
    SDL_RenderDrawLine(renderer, cx - dx, cy + dy, cx + dx, cy + dy);
  }
}

static SDL_Point centre_case(int x, int y) {
  return (SDL_Point){PLATEAU_X + CENTRE_X[x][y], PLATEAU_Y + CENTRE_Y[x]};
}

// ---------- mise en place ----------

static void nouvelle_partie(jeu_sdl *jeu, textures *tx) {
  creationplateau(&jeu->plateau);
  jeu->deplacee = -1;
  jeu->gagnant = personne;
  memset(jeu->zone_gagnante, 0, sizeof jeu->zone_gagnante);

  // réserve : le joueur 1 (blanc) en bas, le joueur 2 (noir) en haut
  int largeur = WINDOW_LARGEUR / (NB_FORMES * NB_EXEMPLAIRES);
  int i = 0;
  for (int j = 0; j < 2; j++) {
    for (int f = cone; f <= sphere; f++) {
      for (int e = 0; e < NB_EXEMPLAIRES; e++, i++) {
        piece *p = &jeu->pieces[i];
        p->texture = tx->formes[j][f];
        p->forme = f;
        p->joueur = j;
        p->posee = false;
        SDL_QueryTexture(p->texture, NULL, NULL, &p->depart.w, &p->depart.h);
        int colonne = (f - 1) * NB_EXEMPLAIRES + e;
        p->depart.x = colonne * largeur + (largeur - p->depart.w) / 2;
        p->depart.y = j == joueur1 ? WINDOW_HAUTEUR - p->depart.h - 10 : 10;
        p->rect = p->depart;
      }
    }
  }
}

static bool est_ia(const jeu_sdl *jeu, int joueur) { return jeu->contre_ia && joueur == joueur2; }

// Pose la pièce i en (x, y), puis vérifie la victoire et le blocage
static void poser(jeu_sdl *jeu, int i, int x, int y) {
  piece *p = &jeu->pieces[i];
  int joueur = jeu->plateau.trait;
  jouercoup(&jeu->plateau, (coups){x, y, p->forme});
  p->posee = true;
  SDL_Point c = centre_case(x, y);
  p->rect.x = c.x - p->rect.w / 2;
  p->rect.y = c.y - p->rect.h / 2;

  if (victoire(&jeu->plateau, x, y)) {
    jeu->gagnant = joueur;
    // on retient les cases des zones complétées (ligne, colonne ou carré de
    // la pièce posée) pour les mettre en évidence
    for (int a = 0; a < TAILLE; a++) {
      for (int b = 0; b < TAILLE; b++) {
        int types[3] = {a == x, b == y, region(a, b) == region(x, y)};
        for (int t = 0; t < 3; t++) {
          if (!types[t]) continue;
          bool vu[NB_FORMES + 1] = {false};
          int n = 0;
          for (int u = 0; u < TAILLE; u++) {
            for (int v = 0; v < TAILLE; v++) {
              bool meme = (t == 0 && u == x) || (t == 1 && v == y) || (t == 2 && region(u, v) == region(x, y));
              int f = jeu->plateau.forme[u][v];
              if (meme && f != vide && !vu[f]) vu[f] = true, n++;
            }
          }
          if (n == NB_FORMES) jeu->zone_gagnante[a][b] = true;
        }
      }
    }
    jeu->etat = FIN;
    return;
  }
  coups liste[NB_COUPS_MAX];
  if (coupspossibles(&jeu->plateau, liste) == 0) {  // le suivant est bloqué
    jeu->gagnant = joueur;
    jeu->etat = FIN;
  }
}

// ---------- affichage ----------

static void afficher(SDL_Renderer *renderer, textures *tx, jeu_sdl *jeu, bool ia_reflechit) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  dessiner(renderer, tx->fond, 0, 0, (float)WINDOW_LARGEUR / 1280);

  if (jeu->etat == MENU) {
    dessiner_centre(renderer, tx->titre, WINDOW_LARGEUR / 2, 190);
    dessiner_centre(renderer, tx->regles, WINDOW_LARGEUR / 2, 300);
    dessiner_centre(renderer, tx->un_joueur, WINDOW_LARGEUR / 2, 480);
    dessiner_centre(renderer, tx->deux_joueurs, WINDOW_LARGEUR / 2, 660);
    dessiner_centre(renderer, tx->touches, WINDOW_LARGEUR / 2, 830);
    SDL_RenderPresent(renderer);
    return;
  }
  if (jeu->etat == REGLES) {
    dessiner_centre(renderer, tx->regles_detail, WINDOW_LARGEUR / 2, WINDOW_HAUTEUR / 2 - 20);
    dessiner_centre(renderer, tx->touches, WINDOW_LARGEUR / 2, WINDOW_HAUTEUR - 70);
    SDL_RenderPresent(renderer);
    return;
  }

  dessiner(renderer, tx->plateau, PLATEAU_X, PLATEAU_Y, 1.0f);

  // cases gagnantes en vert, cases autorisées pour la pièce déplacée en bleu
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  for (int x = 0; x < TAILLE; x++) {
    for (int y = 0; y < TAILLE; y++) {
      SDL_Point c = centre_case(x, y);
      if (jeu->zone_gagnante[x][y]) {
        SDL_SetRenderDrawColor(renderer, 34, 197, 94, 200);
        disque(renderer, c.x, c.y, 58);
      } else if (jeu->deplacee >= 0 &&
                 valide(&jeu->plateau, jeu->plateau.trait, jeu->pieces[jeu->deplacee].forme, x, y)) {
        SDL_SetRenderDrawColor(renderer, 37, 99, 235, 150);
        disque(renderer, c.x, c.y, 38);
      }
    }
  }

  // indicateurs de tour, comme dans la version de Valentin : joueur 2 en haut à
  // gauche, joueur 1 en bas à droite ; celui qui ne joue pas est estompé
  SDL_Texture *haut = jeu->contre_ia ? tx->ia : tx->joueur[joueur2];
  SDL_SetTextureAlphaMod(haut, jeu->plateau.trait == joueur2 || jeu->etat == FIN ? 255 : 70);
  SDL_SetTextureAlphaMod(tx->joueur[joueur1], jeu->plateau.trait == joueur1 || jeu->etat == FIN ? 255 : 70);
  dessiner(renderer, haut, 12, 130, 0.85f);
  dessiner(renderer, tx->joueur[joueur1], WINDOW_LARGEUR - 284, WINDOW_HAUTEUR - 240, 0.85f);
  if (ia_reflechit) dessiner(renderer, tx->reflexion, 6, 250, 0.85f);

  // pièces, la pièce déplacée par-dessus les autres
  for (int i = 0; i < NB_PIECES; i++) {
    if (i != jeu->deplacee) SDL_RenderCopy(renderer, jeu->pieces[i].texture, NULL, &jeu->pieces[i].rect);
  }
  if (jeu->deplacee >= 0) {
    piece *p = &jeu->pieces[jeu->deplacee];
    SDL_RenderCopy(renderer, p->texture, NULL, &p->rect);
  }

  if (jeu->etat == FIN) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
    SDL_RenderFillRect(renderer, NULL);
    // panneau blanc derrière les deux messages, pour qu'ils restent lisibles
    SDL_Rect panneau = {WINDOW_LARGEUR / 2 - 310, WINDOW_HAUTEUR / 2 - 105, 620, 215};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 235);
    SDL_RenderFillRect(renderer, &panneau);
    SDL_Texture *message = est_ia(jeu, jeu->gagnant) ? tx->ia_gagne : tx->gagne[jeu->gagnant];
    dessiner_centre(renderer, message, WINDOW_LARGEUR / 2, WINDOW_HAUTEUR / 2 - 20);
    dessiner_centre(renderer, tx->retour_menu, WINDOW_LARGEUR / 2, WINDOW_HAUTEUR / 2 + 70);
  }
  SDL_RenderPresent(renderer);
}

// ---------- tour de l'IA ----------

static void tour_ia(SDL_Renderer *renderer, textures *tx, jeu_sdl *jeu) {
  afficher(renderer, tx, jeu, true);
  coups coup = trouver_meilleur_coup(&jeu->plateau, profondeurconseillee(&jeu->plateau), NULL);

  // on prend une pièce de la bonne forme dans la réserve de l'IA
  int i = 0;
  while (i < NB_PIECES && (jeu->pieces[i].joueur != joueur2 || jeu->pieces[i].posee ||
                           jeu->pieces[i].forme != coup.forme)) {
    i++;
  }
  // petite animation de la réserve vers la case
  piece *p = &jeu->pieces[i];
  SDL_Point arrivee = centre_case(coup.x, coup.y);
  SDL_Rect debut = p->rect;
  jeu->deplacee = i;
  for (int etape = 1; etape <= 24; etape++) {
    float t = etape / 24.0f;
    t = t * t * (3 - 2 * t);  // départ et arrivée en douceur
    p->rect.x = (int)(debut.x + t * (arrivee.x - p->rect.w / 2 - debut.x));
    p->rect.y = (int)(debut.y + t * (arrivee.y - p->rect.h / 2 - debut.y));
    afficher(renderer, tx, jeu, false);
    SDL_Delay(16);
  }
  jeu->deplacee = -1;
  poser(jeu, i, coup.x, coup.y);
}

// ---------- souris ----------

static void clic_menu(jeu_sdl *jeu, textures *tx, int mx, int my) {
  SDL_Point souris = {mx, my};
  SDL_Texture *boutons[2] = {tx->un_joueur, tx->deux_joueurs};
  int centres[2] = {480, 660};
  for (int b = 0; b < 2; b++) {
    SDL_Rect r;
    SDL_QueryTexture(boutons[b], NULL, NULL, &r.w, &r.h);
    r.x = WINDOW_LARGEUR / 2 - r.w / 2;
    r.y = centres[b] - r.h / 2;
    if (SDL_PointInRect(&souris, &r)) {
      jeu->contre_ia = b == 0;
      nouvelle_partie(jeu, tx);
      jeu->etat = REGLES;  // on affiche les règles avant de jouer
    }
  }
}

static void lacher(jeu_sdl *jeu) {
  piece *p = &jeu->pieces[jeu->deplacee];
  int cx = p->rect.x + p->rect.w / 2, cy = p->rect.y + p->rect.h / 2;
  for (int x = 0; x < TAILLE; x++) {
    for (int y = 0; y < TAILLE; y++) {
      SDL_Point c = centre_case(x, y);
      int dx = c.x - cx, dy = c.y - cy;
      if (dx * dx + dy * dy < RAYON_CASE * RAYON_CASE && valide(&jeu->plateau, p->joueur, p->forme, x, y)) {
        int i = jeu->deplacee;
        jeu->deplacee = -1;
        poser(jeu, i, x, y);
        return;
      }
    }
  }
  p->rect = p->depart;  // coup interdit ou lâchée hors du plateau : retour à la réserve
  jeu->deplacee = -1;
}

// Traite un événement clavier ou souris ; renvoie faux pour quitter le jeu
static bool traiter_evenement(SDL_Window *window, jeu_sdl *jeu, textures *tx, const SDL_Event *event) {
  switch (event->type) {
    case SDL_QUIT:
      return false;
    case SDL_WINDOWEVENT:
      // fenêtre redimensionnée (par l'utilisateur, le plein écran ou macOS) :
      // on recalcule la mise à l'échelle pour garder le jeu centré
      if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        SDL_RenderSetLogicalSize(SDL_GetRenderer(window), WINDOW_LARGEUR, WINDOW_HAUTEUR);
      }
      break;
    case SDL_KEYDOWN: {
      bool plein_ecran = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
      if (event->key.keysym.sym == SDLK_f) {
        SDL_SetWindowFullscreen(window, plein_ecran ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
      } else if (event->key.keysym.sym == SDLK_ESCAPE) {
        if (plein_ecran) {
          SDL_SetWindowFullscreen(window, 0);
        } else {
          jeu->deplacee = -1;
          jeu->etat = MENU;
        }
      }
      break;
    }
    case SDL_MOUSEBUTTONDOWN:
      if (event->button.button != SDL_BUTTON_LEFT) break;
      if (jeu->etat == MENU) {
        clic_menu(jeu, tx, event->button.x, event->button.y);
      } else if (jeu->etat == REGLES) {
        jeu->etat = PARTIE;
      } else if (jeu->etat == FIN) {
        jeu->etat = MENU;
      } else if (!est_ia(jeu, jeu->plateau.trait)) {
        // on ne peut prendre qu'une pièce de sa propre réserve
        SDL_Point souris = {event->button.x, event->button.y};
        for (int i = NB_PIECES - 1; i >= 0; i--) {
          piece *p = &jeu->pieces[i];
          if (!p->posee && p->joueur == jeu->plateau.trait && SDL_PointInRect(&souris, &p->rect)) {
            jeu->deplacee = i;
            break;
          }
        }
      }
      break;
    case SDL_MOUSEMOTION:
      if (jeu->deplacee >= 0) {
        piece *p = &jeu->pieces[jeu->deplacee];
        p->rect.x = event->motion.x - p->rect.w / 2;
        p->rect.y = event->motion.y - p->rect.h / 2;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      if (event->button.button == SDL_BUTTON_LEFT && jeu->deplacee >= 0 && jeu->etat == PARTIE) lacher(jeu);
      break;
  }
  return true;
}

// ---------- boucle principale ----------

int lancer_sdl(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    return 1;
  }
  IMG_Init(IMG_INIT_PNG);
  // les images sont dans jeu1/images, l'exécutable dans jeu1/build
  char *base = SDL_GetBasePath();
  snprintf(chemin_images, sizeof chemin_images, "%s../images/", base ? base : "./");
  SDL_free(base);

  // La fenêtre s'adapte à l'écran (sur un écran de 1366 x 768, une fenêtre de
  // 1300 x 900 sortait de l'écran et cachait la réserve du joueur 1). Le jeu est
  // dessiné en 1300 x 900 puis mis à l'échelle : SDL convertit aussi les
  // coordonnées de la souris.
  SDL_Rect ecran = {0, 0, WINDOW_LARGEUR, WINDOW_HAUTEUR};
  SDL_GetDisplayUsableBounds(0, &ecran);
  float echelle = SDL_min(1.0f, SDL_min(0.92f * ecran.w / WINDOW_LARGEUR, 0.92f * ecran.h / WINDOW_HAUTEUR));
  SDL_Window *window = SDL_CreateWindow("Quantik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        (int)(WINDOW_LARGEUR * echelle), (int)(WINDOW_HAUTEUR * echelle),
                                        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer, WINDOW_LARGEUR, WINDOW_HAUTEUR);

  textures tx = {
      .fond = charger(renderer, "fondblanc.png"),
      .plateau = charger(renderer, "nouveaufond.png"),
      .titre = charger(renderer, "titre.png"),
      .regles = charger(renderer, "regles.png"),
      .un_joueur = charger(renderer, "1j.png"),
      .deux_joueurs = charger(renderer, "2J.png"),
      .joueur = {charger(renderer, "joueur1.png"), charger(renderer, "joueur2.png")},
      .ia = charger(renderer, "IA2.png"),
      .gagne = {charger(renderer, "j1gagne.png"), charger(renderer, "j2gagne.png")},
      .ia_gagne = charger(renderer, "iagagne.png"),
      .reflexion = charger(renderer, "reflexion.png"),
      .retour_menu = charger(renderer, "retourmenu.png"),
      .regles_detail = charger(renderer, "reglesdetail.png"),
      .touches = charger(renderer, "touches.png"),
  };
  const char *noms[NB_FORMES + 1] = {NULL, "cone", "cube", "cylindre", "sphere"};
  for (int f = cone; f <= sphere; f++) {
    char nom[64];
    snprintf(nom, sizeof nom, "%s%s.png", noms[f], f == sphere ? "blanche" : "blanc");
    tx.formes[joueur1][f] = charger(renderer, nom);
    snprintf(nom, sizeof nom, "%snoir.png", noms[f]);
    tx.formes[joueur2][f] = charger(renderer, nom);
  }

  jeu_sdl jeu = {.etat = MENU, .deplacee = -1};
  bool continuer = true;
  while (continuer) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (!traiter_evenement(window, &jeu, &tx, &event)) continuer = false;
    }
    if (jeu.etat == PARTIE && est_ia(&jeu, jeu.plateau.trait)) {
      tour_ia(renderer, &tx, &jeu);
      SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);  // les clics pendant la réflexion sont ignorés
    }
    afficher(renderer, &tx, &jeu, false);
  }

  SDL_Texture *toutes[] = {tx.fond, tx.plateau, tx.titre, tx.regles, tx.un_joueur, tx.deux_joueurs,
                           tx.joueur[0], tx.joueur[1], tx.ia, tx.gagne[0], tx.gagne[1], tx.ia_gagne,
                           tx.reflexion, tx.retour_menu, tx.regles_detail, tx.touches};
  for (size_t i = 0; i < sizeof toutes / sizeof toutes[0]; i++) SDL_DestroyTexture(toutes[i]);
  for (int j = 0; j < 2; j++) {
    for (int f = cone; f <= sphere; f++) SDL_DestroyTexture(tx.formes[j][f]);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
