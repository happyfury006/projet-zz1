#include <stdio.h>
#include <stdlib.h>
#include "coups.h"
#include "situation.h"
#include "liste_chainee.h"


void generer_combinaisons_main(int *main, int taille, liste_chainee* liste) {
    // Combinaisons de 2 cartes
    for (int i = 0; i < taille; i++) {
        if (main[i] > 0) {
            for (int j = i; j < taille; j++) {
                if (i == j && main[i] > 1) {
                    int combinaison[2] = { i, j };
                    insert_tete(liste, combinaison, 2);
                } else if (i != j && main[j] > 0) {
                    int combinaison[2] = { i, j };
                    insert_tete(liste, combinaison, 2);
                }
            }
        }
    }
    // Combinaisons de 1 carte
    for (int i = 0; i < taille; i++) {
        if (main[i] > 0) {
            int combinaison[1] = { i };
            insert_tete(liste, combinaison, 1);
        }
    }

    int combinaison[1] = { -1 };
    insert_tete(liste, combinaison, 1);
}


liste_chainee* init_defausse(sitjoueur* sit){
    liste_chainee* L_defausse=creerListe();
    generer_combinaisons_main(sit->mainjoueur, 5, L_defausse);

    return L_defausse;  
}


