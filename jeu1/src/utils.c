#include "utils.h"

 // Include the header file that contains the definition of 'enum forme'


int estdanslaliste(int forme,list * listdejaparcouru){
    list * tmp = listdejaparcouru;
    while (tmp != NULL)
    {
        if (tmp->value == forme)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
void ajoutliste(int forme,list * listdejaparcouru){
    list * tmp = listdejaparcouru;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(list));
    tmp->next->value = forme;
    tmp->next->next = NULL;
}

