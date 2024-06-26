#include <stdio.h>
#include <stdlib.h>
#include "coups.h"
#include "situation.h"

coups* init_coups() {
    coups* coup = (coups*)malloc(sizeof(coups));
    for (int i = 0; i < 5; i++) {
        coup->echange_pioche[i] = 0;
        coup->carte_donnee_marche[i] = 0;
        coup->carte_recu_marche[i] = 0;
    }
    coup->construction = -1;
    coup->coup_suivant = NULL;
    return coup;
}

void supprimer_1coup_possible(coups* coup) {
    coups* copie_coups = coup;
    if (coup->coup_suivant != NULL) {
        coup = coup->coup_suivant;
        free(copie_coups);
    } else {
        free(coup);
    }
}

void ajouter_coup(coups** tete, coups* nouveau_coup) {
    nouveau_coup->coup_suivant = *tete;
    *tete = nouveau_coup;
}

void phase_echange_pioche_ordi(sitjoueur* joueur1, coups** tete) {
    // Test tous les nombres d'échanges possibles et toutes les cartes possibles échanger avec la pioche
    for (int nb_echange = 0; nb_echange < 5; nb_echange++) {
        for (int choix_main = 0; choix_main < 5; choix_main++) {
            if (joueur1->mainjoueur[choix_main] > 0) {
                coups* nouveau_coup = init_coups();
                nouveau_coup->echange_pioche[choix_main] = nb_echange;
                ajouter_coup(tete, nouveau_coup);
            }
        }
    }
}

void phase_echange_marche_ordi(sitjoueur* joueur1, coups** tete) {
    // Pour chaque combinaison possible de carte à échanger avec le marché on alloue les cartes à échanger en tête de structure coup
    for (int nb_echange = 0; nb_echange < 5; nb_echange++) {
        for (int choix_main = 0; choix_main < 5; choix_main++) {
            if (joueur1->mainjoueur[choix_main] > 0) {
                for (int choix_marche = 0; choix_marche < 5; choix_marche++) {
                    if (joueur1->marchee[choix_marche] > 0) {
                        coups* nouveau_coup = init_coups();
                        nouveau_coup->carte_donnee_marche[choix_main] = nb_echange;
                        nouveau_coup->carte_recu_marche[choix_marche] = nb_echange;
                        ajouter_coup(tete, nouveau_coup);
                    }
                }
            }
        }
    }
}

void phase_construction_ordi(sitjoueur* joueur, coups** tete) {
    for (int choix = 0; choix < 4; choix++) {
        if (valide_construction(joueur, choix) == 1) {
            coups* nouveau_coup = init_coups();
            nouveau_coup->construction = choix;
            ajouter_coup(tete, nouveau_coup);
        }
    }
}

coups* liste_coup_possible(sitjoueur* joueur) {
    coups* tete = NULL;
    phase_echange_pioche_ordi(joueur, &tete);
    phase_echange_marche_ordi(joueur, &tete);
    phase_construction_ordi(joueur, &tete);
    return tete;
}

void afficher_listes_coup_possible(coups* tete) {
    coups* coup = tete;
    while (coup != NULL) {
        printf("Echange pioche : ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", coup->echange_pioche[i]);
        }
        printf("\n");
        printf("Echange marche : ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", coup->carte_donnee_marche[i]);
        }
        printf("\n");
        printf("Reception marche : ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", coup->carte_recu_marche[i]);
        }
        printf("\n");
        printf("Construction : %d\n", coup->construction);
        coup = coup->coup_suivant;
    }
}
