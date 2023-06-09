#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "menu.h"
#include "list.h"

int main() {
    main_options option;
    t_List* productList = list_init();
    do {
        splash();
        option = menu();

        switch (option) {
            case OPTION_REGISTER_PRODUCT:
                insert_product(productList);
                break;
            case OPTION_SEARCH_PRODUCT:
                search_product(productList);
                break;
            case OPTION_UPDATE_STOCK:
                update_stock(productList);
                break;
            case OPTION_SHOW_PRODUCTS:
                list_print(productList);
                break;
            case OPTION_EXIT:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (option != OPTION_EXIT);

    free_list(productList);
    return 0;
}