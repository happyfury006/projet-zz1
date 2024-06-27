#ifndef GARDIEN_UNIQUE_ARBRE_RN_H
#define GARDIEN_UNIQUE_ARBRE_RN_H

#include "situation.h"
#include "coups.h"
#include <stdbool.h>


typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    struct situation* sit;
    int visite;
    int victoire;
    float esperance;
    struct liste_chainee L_defausse;
    struct liste_chainee_2 L_echange;
    int* L_construction;
    bool defausse;
    bool echange;
    bool construction;
} Node;

typedef struct RBTree {
    Node* root;
    Node* nil; 
} RBTree;


Node* createNode(int key, Color color, Node* nil, sitjoueur* joueur1);
RBTree* createRBTree(sitjoueur* joueur1);
void leftRotate(RBTree* tree, Node* x);
void rightRotate(RBTree* tree, Node* y);
void insertFixUp(RBTree* tree, Node* z);
void insert(RBTree* tree, int key,sitjoueur* joueur1);
Node* search(RBTree* tree, int key);
void inOrderTraversal(Node* node, Node* nil);
void displayTree(Node* root, Node* nil);
void freeNode(Node* node, Node* nil);
void freeRBTree(RBTree* tree);


#endif // GARDIEN_UNIQUE_ARBRE_RN_H