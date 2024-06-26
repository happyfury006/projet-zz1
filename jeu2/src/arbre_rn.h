#ifndef GARDIEN_UNIQUE_ARBRE_RN_H
#define GARDIEN_UNIQUE_ARBRE_RN_H

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct RBTree {
    Node* root;
    Node* nil; 
} RBTree;


Node* createNode(int key, Color color, Node* nil);
RBTree* createRBTree();
void leftRotate(RBTree* tree, Node* x);
void rightRotate(RBTree* tree, Node* y);
void insertFixUp(RBTree* tree, Node* z);
void insert(RBTree* tree, int key);
Node* search(RBTree* tree, int key);
void inOrderTraversal(Node* node, Node* nil);
void displayTree(Node* root, Node* nil);
void freeNode(Node* node, Node* nil);
void freeRBTree(RBTree* tree);


#endif // GARDIEN_UNIQUE_ARBRE_RN_H