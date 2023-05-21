#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

t_List *list_init() {
    t_List *list = (struct t_List*)malloc(sizeof(*list));
    if(list == NULL) {
        printf("Falha na alocacao de memoria");
        exit(1); // Encerra o programa com código de erro 1
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void free_list(t_List *list) {
    t_Node *current = list->head;
    while(current != NULL) {
        t_Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int list_push(t_List *list, void *data, int node_size) {

    t_Node* newnode = (t_Node*)malloc(node_size + sizeof(void*));
    if (newnode == NULL) {
        printf("Falha na alocação de memória");
        exit(1); // Encerra o programa com código de erro 1
    }
    newnode->data = data;
    newnode->next = NULL;

    if(list->head == NULL) {
        // newnode->product.code = 1;
        list->head = newnode;
    } else {
        t_Node* last = list->head;
        while(last->next != NULL) {
            last = last->next;
        }
        last->next = newnode;
        // newnode->product.code = last->product.code + 1;
    }
    list->size++;
    return list->size;
}