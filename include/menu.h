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
    SEARCH_OPTION_BACK = 0,
    SEARCH_OPTION_NAME,
    SEARCH_OPTION_CODE,
} search_options;

main_options menu();
search_options search_menu();
void splash();
void clear_input_buffer();

#endif // MENU_H