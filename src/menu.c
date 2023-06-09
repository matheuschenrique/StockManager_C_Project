#include <stdio.h>
#include "menu.h"

/*
    Clears input buffer
*/
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/*
    Select option to main menu
*/
main_options menu() {
    int option;
    printf("Escolha uma das opcoes:\n");
    printf("1 - Registrar novo produto\n");
    printf("2 - Buscar produto\n");
    printf("3 - Atualizar estoque\n");
    printf("4 - Mostrar todos os produtos\n");
    printf("0 - Sair\n");
    printf("Opcao escolhida: ");
    while(scanf("%d", &option) != 1 || option < 0 || option > 4) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }
    printf("\n");
    return (main_options)option;
}

/*
    Select option to search menu
*/
search_options search_menu() {
    int option;
    printf("Escolha uma das opcoes:\n");
    printf("1 - Procurar por nome\n");
    printf("2 - Procurar por codigo\n");
    printf("0 - Voltar\n");
    printf("Opcao escolhida: ");
    while(scanf("%d", &option) != 1 || option < 0 || option > 2) {
        printf("Entrada invalida, digite um valor valido: ");
        clear_input_buffer();
    }
    printf("\n");
    return (search_options)option;
}

/*
    Displays initial message
*/
void splash() {
    printf("\n\n%22s%s\n", "", "Welcome to the system!");
    for(size_t i = 0; i < 66; i++) {
        printf("-");
    }
    printf("\n"); 
}