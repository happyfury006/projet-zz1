#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mcts.h"


Conteneur initConteneurUnique(int entier) {
    Conteneur conteneur;
    conteneur.valeur.entierUnique = entier;
    conteneur.type = UNIQUE;
    return conteneur;
}


Conteneur initConteneurCouple(int premier, int second) {
    Conteneur conteneur;
    conteneur.valeur.coupleEntiers.premier = premier;
    conteneur.valeur.coupleEntiers.second = second;
    conteneur.type = COUPLE;
    return conteneur;
}


ConteneurCouple initConteneurCoupleSimple(int premier, int second) {
    ConteneurCouple conteneur;
    conteneur.valeur.couple.premier = premier;
    conteneur.valeur.couple.second = second;
    conteneur.type = COUPLE_SIMPLE;
    return conteneur;
}


ConteneurCouple initConteneurCoupleDeCouples(int premier1, int second1, int premier2, int second2) {
    ConteneurCouple conteneur;
    conteneur.valeur.coupleDeCouples.premierCouple.premier = premier1;
    conteneur.valeur.coupleDeCouples.premierCouple.second = second1;
    conteneur.valeur.coupleDeCouples.secondCouple.premier = premier2;
    conteneur.valeur.coupleDeCouples.secondCouple.second = second2;
    conteneur.type = COUPLE_DE_COUPLES;
    return conteneur;
}

Nodemcts* initNodemcts(Conteneur* defausse,ConteneurCouple* marche, int construction) {
    Nodemcts* nouveauNoeud = (Nodemcts*)malloc(sizeof(Nodemcts));
    if (nouveauNoeud == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    nouveauNoeud->visite = 0;
    nouveauNoeud->victoire = 0;
    nouveauNoeud->esperance = 0.0;
    nouveauNoeud->phase_echange = true;
    nouveauNoeud->coup_construction = construction;
    nouveauNoeud->coup_defausse = defausse;
    nouveauNoeud->coup_marche = marche;
    nouveauNoeud->next = NULL;

    return nouveauNoeud;
}


void freeNodemcts(Nodemcts* tete) {
    Nodemcts* courant = tete;
    Nodemcts* prochainNoeud;

    while (courant != NULL) {
        prochainNoeud = courant->next;
        free(courant);
        courant = prochainNoeud;
    }
}


Nodemcts* trouverPremierNonVisite(Nodemcts* tete) {
    Nodemcts* courant = tete;

    while (courant != NULL) {
        if (courant->visite == 0) {
            return courant;
        }
        courant = courant->next;
    }

    return NULL; 
}
