#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "menu.h"

const float tax_table[] = {0.0, 0.05, 0.1, 0.2, 0.08, 0.15};

/*
    Inits the list
    Must be called at the beginning of the code
*/
ProductList *list_init() {
    ProductList *p = (struct ProductList*)malloc(sizeof(*p));
    if(p == NULL) {
        printf("Falha na alocacao de memoria");
        exit(1); // Encerra o programa com código de erro 1
    }
    p->head = NULL;
    return p;
}

/*
    Frees the list
    Must be called at the beginning of the code
*/
void free_list(ProductList *list) {
    ProductNode *current = list->head;
    while(current != NULL) {
        ProductNode *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

/*
    Create a new node and increments the code
*/
void create_node(ProductList *list, ProductNode *newnode) {
    if(list->head == NULL) {
        newnode->product.code = 1;
        list->head = newnode;
    } else {
        ProductNode* last = list->head;
        while(last->next != NULL) {
            last = last->next;
        }
        last->next = newnode;
        newnode->product.code = last->product.code + 1;
    }
}

void calculate_total_tax(Product *product) {
    switch (product->type) {
        case TYPE_BOOK:
            product->total_tax = product->quantity * product->price * tax_table[TYPE_BOOK]; // 5% de taxa para livros
            break;
        case TYPE_ELECTRONICS:
            product->total_tax = product->quantity * product->price * tax_table[TYPE_ELECTRONICS]; // 10% de taxa para eletrônicos
            break;
        case TYPE_CLOTHING:
            product->total_tax = product->quantity * product->price * tax_table[TYPE_CLOTHING]; // 20% de taxa para vestuário
            break;
        case TYPE_FOOD:
            product->total_tax = product->quantity * product->price * tax_table[TYPE_FOOD]; // 8% de taxa para alimentos
            break;
        case TYPE_OTHER:
            product->total_tax = product->quantity * product->price * tax_table[TYPE_OTHER]; // 15% de taxa para outros produtos
            break;
        case TYPE_DEFAULT:
        default:
            product->total_tax = tax_table[TYPE_DEFAULT]; // Valor padrão para tipos de produto desconhecidos
            break;
    }
}

/*
    Insert a new product in the list
    All parameters must be entered correctly
*/
void insert_product(ProductList *list) {
    ProductNode *newnode = (struct ProductNode*)malloc(sizeof(*newnode));
    if(newnode == NULL) {
        printf("Falha na alocacao de memoria");
        exit(1); // Encerra o programa com código de erro 1
    }

    clear_input_buffer();

    printf("Digite o nome do produto: ");
    fgets(newnode->product.name, sizeof(newnode->product.name), stdin);
    newnode->product.name[strcspn(newnode->product.name, "\n")] = '\0';

    printf("Escolha o tipo de produto:\n");
    printf("1 - Livro\n");
    printf("2 - Eletronicos\n");
    printf("3 - Vestuario\n");
    printf("4 - Alimentos\n");
    printf("5 - Outros\n");
    printf("Opcao escolhida: ");
    while (scanf("%d", (int*)&newnode->product.type) != 1 || newnode->product.type < TYPE_DEFAULT || newnode->product.type > TYPE_OTHER) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }
    printf("\n");

    printf("Digite a quantidade do produto em estoque: ");
    while(scanf("%d", &newnode->product.quantity) != 1 || newnode->product.quantity < 0) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }

    printf("Digite o preco de venda do produto: ");
    while(scanf("%f", &newnode->product.price) != 1 || newnode->product.price <= 0.0f) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }

    calculate_total_tax(&(newnode->product));

    newnode->next = NULL;

    create_node(list, newnode);
}

void print_header() {
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-10s %-10s %-10s %-10s\n", "Nome", "Tipo", "Codigo", "Qtd", "Preco", "Imposto");
    printf("-----------------------------------------------------------------------------------------\n");
}

/*
    Print the product in console
*/
void display_product(const Product* product) {
    const char* type_str = "";
    switch (product->type) {
        case TYPE_BOOK:
            type_str = "Livro";
            break;
        case TYPE_ELECTRONICS:
            type_str = "Eletronicos";
            break;
        case TYPE_CLOTHING:
            type_str = "Roupas";
            break;
        case TYPE_FOOD:
            type_str = "Alimentos";
            break;
        case TYPE_OTHER:
            type_str = "Outros";
            break;
        default:
            break;
    }

    printf("%-20s %-20s %-10d %-10d %-10.2f %-10.2f\n",
           product->name, type_str, product->code, product->quantity, product->price, product->total_tax);
    printf("-----------------------------------------------------------------------------------------\n");
}

/*
    Print all products of the list
*/
void print_list(const ProductList *list) {

    print_header();
    
    ProductNode* product = list->head;
    while (product != NULL) {
        display_product(&(product->product));
        product = product->next;
    }
    
}
/*
    Search the product in the list based on the name
*/
ProductNode *search_by_name(const ProductList *list, const char *name) {
    ProductNode* p = list->head;
    while(p != NULL) {
        if(strcmp(p->product.name, name) == 0) {
            print_header();
            display_product(&(p->product));
            return p;
            break;
        }
        p = p->next;
    }
    printf("Produto nao encontrado\n");
    return NULL;
}

/*
    Search the product in the list based on the code
*/
ProductNode *search_by_code(const ProductList *list, const int code) {
    ProductNode* p = list->head;
    while(p != NULL) {
        if(p->product.code == code) {
            print_header();
            display_product(&(p->product));
            return p;
            break;
        }
        p = p->next;
    }
    printf("Produto nao encontrado\n");
    return NULL;
}

/*
    Search the product in the list
*/
void search_product(const ProductList *list) {
    char name[MAXCHAR];
    int code;
    search_options option;
    do {
        option = search_menu();
        switch (option)
        {
        case SEARCH_OPTION_NAME:
            printf("Digite o nome do produto: ");
            while(scanf(" %[^\n]", name) != 1 || sizeof(name) == 0) {
                printf("Entrada invalida, digite um valor valido: ");
                clear_input_buffer();
            }
            (void)search_by_name(list, name);
            break;
        case SEARCH_OPTION_CODE:
            printf("Digite o codigo do produto: ");
            while(scanf("%d", &code) != 1 || code < 0) {
                printf("Entrada invalida, digite um valor valido: ");
                clear_input_buffer();
            }
            (void)search_by_code(list, code);
            break;
        case SEARCH_OPTION_BACK:
        default:
            break;
        }
    }while(option != SEARCH_OPTION_BACK);
}

/*
    Optade the quantity of the product
*/
void update_product(Product *product) {
    printf("Digite a quantidade do produto em estoque: ");
    while(scanf("%d", &(product->quantity)) != 1 || product->quantity < 0) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }
}

/*
    Request a code and update the quantity of the product
*/
void update_stock(ProductList *list) {
    int code;
    printf("Digite o codigo do produto: ");
    while(scanf("%d", &code) != 1 || code < 0) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }
    ProductNode* p = search_by_code(list, code);
    if(p != NULL) {
        update_product(&(p->product));
        display_product(&(p->product));
    }
}