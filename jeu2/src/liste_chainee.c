#include <stdio.h>
#include <stdlib.h>
#include "coups.h"
#include "situation.h"
#include "liste_chainee.h"


liste_chainee* creerListe() {
    struct liste_chainee* list = (struct liste_chainee*)malloc(sizeof(struct liste_chainee));
    list->head = NULL;
    return list;
}


noeud* creernoeud(int* data, int size) {
    if (size < 1 || size > 2) {
        printf("Erreur : la taille du tableau doit être 1 ou 2.\n");
        return NULL;
    }
    struct noeud* newnoeud = (struct noeud*)malloc(sizeof(struct noeud));
    newnoeud->size = size;
    for (int i = 0; i < size; i++) {
        newnoeud->data[i] = data[i];
    }
    newnoeud->next = NULL;
    return newnoeud;
}


void insert_tete(struct liste_chainee* list, int* data, int size) {
    struct noeud* newnoeud = creernoeud(data, size);
    if (newnoeud == NULL) {
        return;
    }
    newnoeud->next = list->head;
    list->head = newnoeud;
}


void suppr_tete(struct liste_chainee* list) {
    if (list->head == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    struct noeud* temp = list->head;
    list->head = list->head->next;
    free(temp);
}


// Fonction pour afficher la liste
void affiche_list(struct liste_chainee* list) {
    struct noeud* current = list->head;
    while (current != NULL) {
        printf("[");
        for (int i = 0; i < current->size; i++) {
            printf("%d", current->data[i]);
            if (i < current->size - 1) {
                printf(", ");
            }
        }
        printf("] -> ");
        current = current->next;
    }
    printf("NULL\n");
}


// Fonction pour libérer toute la liste
void freeList(struct liste_chainee* list) {
    struct noeud* current = list->head;
    struct noeud* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}


tab* creertab(){
    struct tab* list = (struct tab*)malloc(sizeof(struct tab));
    list->main=creerListe();
    list->marchee=creerListe();
    return liste;
}
