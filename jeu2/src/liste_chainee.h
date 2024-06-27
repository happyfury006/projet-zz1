#ifndef GARDIEN_UNIQUE_LISTE_CHAINEE_H
#define GARDIEN_UNIQUE_LISTE_CHAINEE_H


typedef struct noeud {
    int data[2];  // Tableau de 1 ou 2 éléments
    int size;     // Taille du tableau (1 ou 2)
    struct noeud* next;
}noeud;


typedef struct liste_chainee {
    struct noeud* head;
}liste_chainee;


typedef struct tab{
    struct liste_chainee* main;
    struct liste_chainee* marchee;
}tab;


liste_chainee* creerListe();
noeud* creernoeud(int* data, int size);
void insert_tete(struct liste_chainee* list, int* data, int size);
void suppr_tete(struct liste_chainee* list);
void affiche_list(struct liste_chainee* list);
void freeList(struct liste_chainee* list);
tab* creertab();

#endif // GARDIEN_UNIQUE_LISTE_CHAINEE_H