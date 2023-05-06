#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "menu.h"

ProductList *list_init() {
    ProductList *p = (struct ProductList*)malloc(sizeof(ProductList));
    p->head = NULL;
    return p;
}

void free_list(ProductList *l) {
    ProductNode *current = l->head;
    while(current != NULL) {
        ProductNode *next = current->next;
        free(current);
        current = next;
    }
    free(l);
}

void create_node(ProductList *l, ProductNode *newnode) {
    if(l->head == NULL) {
        newnode->product.code = 1;
        l->head = newnode;
    } else {
        ProductNode* last = l->head;
        while(last->next != NULL) {
            last = last->next;
        }
        last->next = newnode;
        newnode->product.code = last->product.code + 1;
    }
}

void insert_product(ProductList *l) {
    ProductNode *newnode = (struct ProductNode*)malloc(sizeof(ProductNode));
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", newnode->product.name);
    printf("Digite a quantidade do produto em estoque: ");
    scanf("%d", &newnode->product.quantity);
    printf("Digite o preco de venda do produto: ");
    scanf("%f", &newnode->product.price);
    newnode->next = NULL;

    create_node(l, newnode);
}

void print_product(const Product *p) {
    printf("Nome: %s, Código: %d, Quantidade: %d, Preço: %.2f\n",
               p->name, p->code, p->quantity, p->price);
}

void print_list(const ProductList *l) {
    ProductNode* product = l->head;
    while(product != NULL) {
        print_product(&(product->product));
        product = product->next;
    }
}

ProductNode *search_by_name(const ProductList *l, const char *name) {
    ProductNode* p = l->head;
    while(p != NULL) {
        if(strcmp(p->product.name, name) == 0) {
            printf("Produto encontrado\n");
            print_product(&(p->product));
            return p;
            break;
        }
        p = p->next;
    }
    printf("Produto nao encotnrado\n");
    return NULL;
}

ProductNode *search_by_code(const ProductList *l, const int code) {
    ProductNode* p = l->head;
    while(p != NULL) {
        if(p->product.code == code) {
            printf("Produto encontrado\n");
            print_product(&(p->product));
            return p;
            break;
        }
        p = p->next;
    }
    printf("Produto nao encotnrado\n");
    return NULL;
}

// Função que busca um produto pelo código
void search_product(const ProductList *l) {
    char name[MAXCHAR];
    int code;
    search_options option;
    do {
        option = search_menu();
        switch (option)
        {
        case SEARCH_OPTION_NAME:
            printf("Digite o nome do produto: ");
            scanf(" %[^\n]", name);
            (void)search_by_name(l, name);
            break;
        case SEARCH_OPTION_CODE:
            printf("Digite o código do produto: ");
            scanf("%d", &code);
            (void)search_by_code(l, code);
            break;
        case SEARCH_OPTION_BACK:
        default:
            break;
        }
    }while(option != 0);
}

void update_product(Product *p) {
    printf("Digite a quantidade do produto em estoque: ");
    scanf("%d", &(p->quantity));
}

void update_stock(ProductList *l) {
    int code;
    printf("Digite o código do produto: ");
    scanf("%d", &code);
    ProductNode* p = search_by_code(l, code);
    update_product(&(p->product));
    print_product(&(p->product));
}