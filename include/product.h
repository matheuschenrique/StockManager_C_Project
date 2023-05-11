#ifndef PRODUCT_H
#define PRODUCT_H

#define MAXCHAR 1000

typedef struct Product{
    int code;
    char name[MAXCHAR];
    int quantity;
    float price;
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