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
}



liste_chainee* init_defausse(sitjoueur* sit){
    liste_chainee* L_defausse=creerListe();
    generer_combinaisons_main(sit->mainjoueur, 5, L_defausse);
    int combinaison[1] = { -1 };
    insert_tete(L_defausse, combinaison, 1);

    return L_defausse;  
}


int* init_construction(sitjoueur* sit){
    int* L_construction = malloc(5*sizeof(int));
    int compteur =0;
    for (int i=0;i<5;i++)
    {
        if (valide_construction(sit,i))
        {
            L_construction[compteur]=i;
            compteur++;
        }
    } 
    return L_construction;
}


tab* init_echange1(sitjoueur* sit){
    tab* L_echange=creertab();
    generer_combinaisons_main(sit->mainjoueur, 5, L_echange->main);
    generer_combinaisons_main(sit->marchee, 5, L_echange->marche);

    return L_echange;  
}