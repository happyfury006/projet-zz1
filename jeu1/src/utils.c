#include "utils.h"
#include <stdlib.h>
#include "jeu.h"

 // Include the header file that contains the definition of 'enum forme'
// enum formes forme;

int estdanslaliste(piece* piece,list * listparcouru){
    list * tmp = listparcouru;
    while (tmp != NULL)
    {
        if (tmp->piece == piece)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
void ajoutliste(piece* piece,list * listparcouru){
    list * tmp = listparcouru;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = (list*)malloc(sizeof(list));
    tmp->next->piece = piece;
    tmp->next->next = NULL;
}

