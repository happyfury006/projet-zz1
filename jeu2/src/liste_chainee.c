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



liste_chainee_2* creerListe2() {
    struct liste_chainee_2* list = (struct liste_chainee_2*)malloc(sizeof(struct liste_chainee_2));
    list->head = NULL;
    return list;
}


noeud2* creer_noeud2(int aechanger[5], int arecevoir[5]) {
    noeud2* new_node = (noeud2*)malloc(sizeof(noeud2));
    if (new_node == NULL) {
        return NULL; // Gestion de l'erreur en cas d'échec de l'allocation
    }
    for (int i = 0; i < 5; i++) {
        new_node->aechanger[i] = aechanger[i];
        new_node->arecevoir[i] = arecevoir[i];
    }
    new_node->next = NULL;
    return new_node;
}


void inser_tete2(liste_chainee_2* liste, noeud2* new_node) {
    if (liste == NULL || new_node == NULL) {
        return; // Gestion de l'erreur si les paramètres sont invalides
    }
    new_node->next = liste->head;
    liste->head = new_node;
}


void suppr_tete2(liste_chainee_2* liste) {
    if (liste == NULL || liste->head == NULL) {
        return; // Gestion de l'erreur si la liste est vide ou invalide
    }
    noeud2* temp = liste->head;
    liste->head = liste->head->next;
    free(temp);
}


void free_liste2(liste_chainee_2* liste) {
    if (liste == NULL) {
        return; // Gestion de l'erreur si la liste est invalide
    }
    noeud2* current = liste->head;
    while (current != NULL) {
        noeud2* next = current->next;
        free(current);
        current = next;
    }
    liste->head = NULL;
}
