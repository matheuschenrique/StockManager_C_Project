#ifndef PRODUCT_H
#define PRODUCT_H

#define MAXCHAR 1000
#define YEAR_IN_DAYS 365
#define MAX_SIZE_LENGTH 3

typedef enum {
    TYPE_DEFAULT = 0,
    TYPE_BOOK,
    TYPE_ELECTRONICS,
    TYPE_CLOTHING,
    TYPE_FOOD,
    TYPE_OTHER,
} product_type;

typedef enum {
    SIZE_P = 0,
    SIZE_M,
    SIZE_G,
    SIZE_GG,
    SIZE_XG,
    SIZE_XXG
} clothing_size;

typedef struct Product {
    int code;
    char name[MAXCHAR];
    int quantity;
    float cost_price;
    float sale_price;
    product_type type;
    union {
        int hard_cover;
        clothing_size size;
        struct tm *manufacturing_date;
        struct tm *expiration_date;
    } details;
} Product;

typedef struct t_List t_List;
typedef struct t_Node t_Node;

void insert_product(t_List *list);
void list_print(const t_List *list);
void display_product(const Product* product);
void search_product(const t_List *list);
void update_stock(t_List *list);
t_Node *search_by_name(const t_List *list, const char *name);
t_Node *search_by_code(const t_List *list, const int code);

#endif // PRODUCT_H