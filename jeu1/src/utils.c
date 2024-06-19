#include "utils.h"


int estdanslaliste(forme forme,list * listdejaparcouru){
    list * tmp = listdejaparcouru;
    while (tmp != NULL)
    {
        if (tmp->value == value)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
void ajoutliste(forme forme,list * listdejaparcouru){
    list * tmp = listdejaparcouru;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(list));
    tmp->next->value = value;
    tmp->next->next = NULL;
}