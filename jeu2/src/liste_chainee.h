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


typedef struct noeud2{
    int aechanger[5];
    int arecevoir[5];
    struct noeud2* next;
}noeud2;

typedef struct liste_chainee_2{
    struct noeud2* head;
}liste_chainee_2;


liste_chainee* creerListe();
noeud* creernoeud(int* data, int size);
void insert_tete(struct liste_chainee* list, int* data, int size);
void suppr_tete(struct liste_chainee* list);
void affiche_list(struct liste_chainee* list);
void freeList(struct liste_chainee* list);


liste_chainee_2* creerListe2();
noeud2* creer_noeud2(int aechanger[5], int arecevoir[5]); 
void inser_tete2(liste_chainee_2* liste, noeud2* new_node);
void suppr_tete2(liste_chainee_2* liste); 
void free_liste2(liste_chainee_2* liste); 


#endif // GARDIEN_UNIQUE_LISTE_CHAINEE_H