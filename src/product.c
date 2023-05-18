#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "product.h"
#include "menu.h"

const float tax_table[] = {0.0, 0.05, 0.1, 0.2, 0.08, 0.15};

void print_date(const struct tm *date) {
    printf("%d/%d/%d", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900);
}

void insert_date(struct tm *destiny) {
    int day, month, year;
    char date_string[11];

    clear_input_buffer();

    do {
        if (fgets(date_string, sizeof(date_string), stdin) == NULL) {
            printf("Erro na leitura da data\n");
            clear_input_buffer();
            continue;
        }

        if (sscanf(date_string, "%d/%d/%d", &day, &month, &year) != 3) {
            printf("Formato de data incorreto. Tente novamente.\n");
            continue;
        }

        // Verifica se os valores estão dentro de intervalos validos
        if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
            printf("Data invalida. Tente novamente.\n");
            continue;
        }

        memset(destiny, 0, sizeof(struct tm));  // Initialize the struct with zeros

        destiny->tm_mday = day;
        destiny->tm_mon = month - 1;
        destiny->tm_year = year - 1900;

        break;

    } while (1);
}

struct tm *get_current_time() {
    time_t current_time = time(NULL);
    return localtime(&current_time);
}

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

void get_clothing_size(Product *product) {
    clear_input_buffer();
    printf("Digite o tamanho da roupa (P, M, G, GG, XG, XXG): ");
    do {
        if(fgets(product->size, sizeof(product->size), stdin) == NULL) {
            printf("Entrada invalida, digite um valor valido: ");
            clear_input_buffer();
            continue;
        }
        product->size[strcspn(product->size, "\n")] = '\0';
        if (strcmp(product->size, "P") != 0 && strcmp(product->size, "M") != 0 &&
            strcmp(product->size, "G") != 0 && strcmp(product->size, "GG") != 0 &&
            strcmp(product->size, "XG") != 0 && strcmp(product->size, "XXG") != 0) {
            printf("Entrada invalida, digite um valor valido: ");
            clear_input_buffer();
            continue;
        }
        break;
    } while (1);
}

void get_cover_style(Product *product) {
    printf("O livro possui capa dura? ");
    clear_input_buffer();
    while (scanf("%d", &product->hard_cover) != 1 || product->hard_cover < 0 || product->hard_cover > 1) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }
}

void get_manufacturing_date(Product *product) {
    printf("Digite a data de fabricacao do produto (no formato DD/MM/YYYY): ");
    product->manufacturing_date = malloc(sizeof(struct tm));
    insert_date(product->manufacturing_date);
}

void get_expiration_date(Product *product) {
    printf("Digite a data de validade do produto (no formato DD/MM/YYYY): ");
    product->expiration_date = malloc(sizeof(struct tm));
    insert_date(product->expiration_date);
}

void calculate_total_price(Product *product) {
    int diferenca = 0;
    switch (product->type) {
        case TYPE_BOOK: // preco relacionado à quantidade de paginas
            product->sale_price = product->cost_price * (1 + tax_table[TYPE_BOOK] + (0.1f * product->hard_cover));
            break;
        case TYPE_ELECTRONICS: // preco relacionado à data de fabricacao
            diferenca = difftime(mktime(get_current_time()), mktime(product->manufacturing_date)) / (60 * 60 * 24);
            if (diferenca <= (int)(YEAR_IN_DAYS / 2)) {
                product->sale_price = product->cost_price * (1 + tax_table[TYPE_ELECTRONICS] + 0.1f);
            } else if (diferenca <= YEAR_IN_DAYS * 2) {
                product->sale_price = product->cost_price * (1 + tax_table[TYPE_ELECTRONICS] + 0.05f);
            } else {
                product->sale_price = product->cost_price * (1 + tax_table[TYPE_ELECTRONICS]);
            }
            break;
        case TYPE_CLOTHING: // preco relacionado ao tamanho
            if (strcmp(product->size, "P") == 0) {
                product->sale_price = product->cost_price *(1 + tax_table[TYPE_CLOTHING] + 0.02f);
                break;
            } else if (strcmp(product->size, "M") == 0) {
                product->sale_price = product->cost_price *(1 + tax_table[TYPE_CLOTHING] + 0.04f);
                break;
            } else if (strcmp(product->size, "G") == 0) {
                product->sale_price = product->cost_price *(1 + tax_table[TYPE_CLOTHING] + 0.06f);
                break;
            } else if (strcmp(product->size, "GG") == 0) {
                product->sale_price = product->cost_price *(1 + tax_table[TYPE_CLOTHING] + 0.08f);
                break;
            } else if (strcmp(product->size, "XG") == 0) {
                product->sale_price = product->cost_price *(1 + tax_table[TYPE_CLOTHING] + 0.10f);
                break;
            } else if (strcmp(product->size, "XXG") == 0) {
                product->sale_price = product->cost_price *(1 + tax_table[TYPE_CLOTHING] + 0.12f);
                break;
            } else {
                printf("Entrada invalida, digite um valor valido: ");
            }
            break;
        case TYPE_FOOD: // preco relacionado à data de validade
            diferenca = difftime(mktime(product->expiration_date), mktime(get_current_time())) / (60 * 60 * 24);
            if (diferenca <= 10) {
                product->sale_price = product->cost_price * (1 + tax_table[TYPE_FOOD]);
            } else if (diferenca <= 30) {
                product->sale_price = product->cost_price * (1 + tax_table[TYPE_FOOD] + 0.05f);
            } else if (diferenca <= 90) {
                product->sale_price = product->cost_price * (1 + tax_table[TYPE_FOOD] + 0.1f);
            } else {
                product->sale_price = product->cost_price * (1 + tax_table[TYPE_FOOD]);
            }
            break;
        case TYPE_OTHER:
        case TYPE_DEFAULT:
        default:
            product->sale_price = product->cost_price * (1 + tax_table[TYPE_OTHER]); // 15% de taxa para outros produtos
            break;
    }
}

/*
    Insert a new product in the list
    All parameters must be entered correctly
*/
void insert_product(ProductList *list) {
    ProductNode* newnode = (ProductNode*)malloc(sizeof(*newnode));
    if (newnode == NULL) {
        printf("Falha na alocação de memória");
        exit(1); // Encerra o programa com código de erro 1
    }
    newnode->next = NULL;

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

    switch(newnode->product.type) {
        case TYPE_BOOK:
            get_cover_style(&newnode->product);
            break;
        case TYPE_ELECTRONICS:
            get_manufacturing_date(&newnode->product);
            break;
        case TYPE_CLOTHING:
            get_clothing_size(&newnode->product);
            break;
        case TYPE_FOOD:
            get_expiration_date(&newnode->product);
            break;
        case TYPE_OTHER:
        case TYPE_DEFAULT:
        default:
            break;
    }

    printf("Digite a quantidade do produto em estoque: ");
    while(scanf("%d", &newnode->product.quantity) != 1 || newnode->product.quantity < 0) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }

    printf("Digite o preco de venda do produto: ");
    while(scanf("%f", &newnode->product.cost_price) != 1 || newnode->product.cost_price <= 0.0f) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }

    calculate_total_price(&(newnode->product));

    create_node(list, newnode);
}

void print_header() {
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-10s %-10s %-10s %-10s %-20s\n", "Nome", "Tipo", "Codigo", "Qtd", "Custo", "Venda", "Info");
    printf("-------------------------------------------------------------------------------------------------------------\n");
}

/*
    Print the product in console
*/
void display_product(const Product* product) {
    const char* type_str = "";
    const char* info = "";
    switch (product->type) {
        case TYPE_BOOK:
            type_str = "Livro";
            info = "Capa Dura:";
            printf("%-20s %-20s %-10d %-10d %-10.2f %-10.2f %s %-10d",
                product->name, type_str, product->code, product->quantity, product->cost_price, product->sale_price, info, product->hard_cover);
            break;
        case TYPE_ELECTRONICS:
            type_str = "Eletronicos";
            info = "Fabricacao:";
            printf("%-20s %-20s %-10d %-10d %-10.2f %-10.2f %s",
                product->name, type_str, product->code, product->quantity, product->cost_price, product->sale_price, info);
            print_date(product->manufacturing_date);
            break;
        case TYPE_CLOTHING:
            type_str = "Roupas";
            info = "Tamanho:";
            printf("%-20s %-20s %-10d %-10d %-10.2f %-10.2f %s %-20s",
                product->name, type_str, product->code, product->quantity, product->cost_price, product->sale_price, info, product->size);
            break;
        case TYPE_FOOD:
            type_str = "Alimentos";
            info = "Validade:";
            printf("%-20s %-20s %-10d %-10d %-10.2f %-10.2f %s",
                product->name, type_str, product->code, product->quantity, product->cost_price, product->sale_price, info);
            print_date(product->expiration_date);
            break;
        case TYPE_OTHER:
            type_str = "Outros";
            printf("%-20s %-20s %-10d %-10d %-10.2f %-10.2f",
                    product->name, type_str, product->code, product->quantity, product->cost_price, product->sale_price);
            break;
        default:
            break;
    }

    printf("\n-------------------------------------------------------------------------------------------------------------\n");
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