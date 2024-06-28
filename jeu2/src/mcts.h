#ifndef GARDIEN_UNIQUE_MCTS_H
#define GARDIEN_UNIQUE_MCTS_H

#include <stdbool.h>


typedef struct CoupleInt{
    int premier;
    int second;
}CoupleInt;

//union pour contenir soit un entier, soit un couple d'entiers
typedef union EntierOuCouple{
    int entierUnique;
    CoupleInt coupleEntiers;
}EntierOuCouple;

//énumération pour indiquer le type de données stocké dans l'union
typedef enum TypeValeur{
    UNIQUE,
    COUPLE
}TypeValeur;

//structure pour contenir l'union et son type
typedef struct Conteneur{
    EntierOuCouple valeur;
    TypeValeur type;
}Conteneur;

//structure pour contenir un couple de couples d'entiers
typedef struct CoupleDeCouple{
    CoupleInt premierCouple;
    CoupleInt secondCouple;
}CoupleDeCouple;

//union pour contenir soit un couple d'entiers, soit un couple de couples d'entiers
typedef union CoupleOuCoupleDeCouple{
    CoupleInt couple;
    CoupleDeCouple coupleDeCouples;
}CoupleOuCoupleDeCouple;

//énumération pour indiquer le type de données stocké dans l'union
typedef enum TypeValeurCouple{
    COUPLE_SIMPLE,
    COUPLE_DE_COUPLES
}TypeValeurCouple;

//structure pour contenir l'union et son type
typedef struct ConteneurCouple{
    CoupleOuCoupleDeCouple valeur;
    TypeValeurCouple type;
}ConteneurCouple;

typedef struct Nodemcts{
    int visite;
    int victoire;
    float esperance;
    bool phase_echange;
    int coup_construction;
    struct Conteneur coup_defausse;
    struct ConteneurCouple coup_marche;
    struct Nodemcts* next;
}Nodemcts;


#endif