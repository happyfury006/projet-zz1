#include <stdio.h>
#include <stdlib.h>

#include "arbre_rn.h"


Node* createNode(int key, Color color, Node* nil) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = color;
    node->left = nil;
    node->right = nil;
    node->parent = nil;
    node->situation = NULL;
    node->coup_possible = NULL;
    node->esperance = 0;
    node->victoire = 0;
    node->visite = 0;
    return node;
}


// Initialisation de l'arbre
RBTree* createRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = createNode(0, BLACK, NULL);  // Créer un nœud nil noir
    tree->root = tree->nil;
    return tree;
}


// Rotation gauche
void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


// Rotation droite
void rightRotate(RBTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}


// Rééquilibrage après insertion
void insertFixUp(RBTree* tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;  // Oncle de z
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}


// Insertion d'un nœud
void insert(RBTree* tree, int key) {
    Node* z = createNode(key, RED, tree->nil);
    Node* y = tree->nil;
    Node* x = tree->root;
    
    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;
    
    insertFixUp(tree, z);
}


Node* search(RBTree* tree, int key) {
    Node* current = tree->root;
    while (current != tree->nil && key != current->key) {
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}


// Parcours infixe (in-order traversal)
void inOrderTraversal(Node* node, Node* nil) {
    if (node != nil) {
        inOrderTraversal(node->left, nil);
        printf("%d ", node->key);
        inOrderTraversal(node->right, nil);
    }
}


void displayTree(Node* root, Node* nil) {
    if (root == nil) {
        printf("nil");
        return;
    }
    
    printf("%d(%s) [", root->key, root->color == RED ? "R" : "B");
    displayTree(root->left, nil);
    printf("] [");
    displayTree(root->right, nil);
    printf("]");
}

// Libération des nœuds de l'arbre
void freeNode(Node* node, Node* nil) {
    if (node != nil) {
        freeNode(node->left, nil);
        freeNode(node->right, nil);
        free(node);
    }
}


// Libération de l'arbre
void freeRBTree(RBTree* tree) {
    freeNode(tree->root, tree->nil);
    free(tree->nil);  // Libérer le nœud sentinelle nil
    free(tree);
}

