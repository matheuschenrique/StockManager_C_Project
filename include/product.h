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

typedef struct Product {
    int code;
    char name[MAXCHAR];
    int quantity;
    float cost_price;
    float sale_price;
    product_type type;
    union {
        int hard_cover;
        char size[MAX_SIZE_LENGTH];
        struct tm *manufacturing_date;
        struct tm *expiration_date;
    } details;
} Product;

typedef struct ProductNode{
    Product product;
    struct ProductNode *next;
} ProductNode;

typedef struct ProductList{
    ProductNode *head;
} ProductList;

ProductList *list_init();
void free_list(ProductList *l);
void insert_product(ProductList *l);
void display_product(const Product *p);
void print_list(const ProductList *l);
void search_product(const ProductList *l);
void update_stock(ProductList *l);
ProductNode *search_by_name(const ProductList *l, const char *name);
ProductNode *search_by_code(const ProductList *l, const int code);


#endif // PRODUCT_H