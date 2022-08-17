#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;


void print_list(TSortedList list) {
    while (list != NULL) {
        printf("%d ",list->value);
        list= list->next;
    }
    printf("\n");
}

TSortedList create(T value) {
    TSortedList lista = malloc(sizeof(TNode));
    lista->value = value;
    lista->next = NULL;
    return lista;
}

int isEmpty(TSortedList lista) {
    if (lista == NULL) {
        return 1;
    }
    return 0;
}

int contains(TSortedList lista, T element) {
    while(lista != NULL){
        if (lista->value == element) {
            return 1;
        }
        lista = lista->next;
    }
    return 0;
}

TSortedList insert(TSortedList lista, T element) {
    if (isEmpty(lista)) {
        lista = create(element);
        return lista;
    }

    TSortedList aux = lista;
    TNode *new = malloc(sizeof(TNode));
    new->value = element;
    new->next = NULL;

    if (element < lista->value) {
        new->next = lista;
        lista = new;
        return lista;
    } else {
        while(aux != NULL) {
            if ((aux->next) != NULL){
                if ((element < (aux->next)->value)) {
                    new->next = aux->next;
                    aux->next = new;
                    return  lista;
                }
            } else {
                aux->next = new;
                return lista;
            }
            aux = aux->next;
        }
    } 
}

TSortedList deleteOnce(TSortedList lista, T element) {
    TSortedList aux = lista;
    if (element == lista->value) {
        if (lista->next != NULL) {
            TSortedList delete = lista->next;
            free(lista);
            lista = delete;
        } else {
            free(lista);
        }
    }
    if (contains(lista,element)) {
        while(aux != NULL) {
            if ((aux->next) != NULL){
                if ((element == (aux->next)->value)) {
                    TSortedList delete = aux->next->next;
                    free(aux->next);
                    aux->next = delete;
                    return  lista;
                }
            }
            aux = aux->next;
        }
    }
    return lista;
}

long length(TSortedList lista) {
    long length = 0;
    TNode *aux=lista;
    while (aux != NULL) {
        length++;
        aux = aux->next;
    }
    return length;
}

T getNth(TSortedList lista, int N) {
    for (int i = 0; i < N-1; i++) {
        lista = lista->next;
    }
    return lista->value;
}

TSortedList freeTSortedList(TSortedList lista) {
    while(lista != NULL) {
        TSortedList nod = lista->next;
        free(lista);
        lista = nod;
    }
    return lista;
}


#endif
