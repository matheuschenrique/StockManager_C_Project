#ifndef LIST_H
#define LIST_H

typedef struct t_Node{
    void *data;
    struct t_Node *next;
} t_Node;

typedef struct t_List{
    t_Node *head;
    int size;
} t_List;

t_List *list_init();
void free_list(t_List *list);
int list_push(t_List *list, void *data, int node_size);
void list_pop(t_List *list);

#endif // LIST_H
