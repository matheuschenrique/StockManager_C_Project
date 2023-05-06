#ifndef MENU_H
#define MENU_H

typedef enum {
    OPTION_EXIT = 0,
    OPTION_REGISTER_PRODUCT,
    OPTION_SEARCH_PRODUCT,
    OPTION_UPDATE_STOCK,
    OPTION_SHOW_PRODUCTS,
}main_options;

typedef enum {
    SEARCH_OPTION_NAME = 1,
    SEARCH_OPTION_CODE,
    SEARCH_OPTION_BACK,
} search_options;

main_options menu();
search_options search_menu();
void splash();

#endif // MENU_H