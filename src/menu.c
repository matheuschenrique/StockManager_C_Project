#include <stdio.h>
#include "menu.h"

main_options menu() {
    int option;
    printf("Escolha uma das opcoes:\n");
    printf("1 - Registrar novo produto\n");
    printf("2 - Buscar produto\n");
    printf("3 - Atualizar estoque\n");
    printf("4 - Mostrar todos os produtos\n");
    printf("0 - Sair\n");
    printf("Opcao escolhida: ");
    scanf("%d", &option);
    printf("\n");
    return (main_options)option;
}

search_options search_menu() {
    int option;
    printf("Escolha uma das opcoes:\n");
    printf("1 - Procurar por nome\n");
    printf("2 - Procurar por código\n");
    printf("0 - Voltar\n");
    printf("Opcao escolhida: ");
    scanf("%d", &option);
    printf("\n");
    return (search_options)option;
}

void splash() {
    printf("\n\n%22s%s\n", "", "Welcome to the system!");
    for(size_t i = 0; i < 66; i++) {
        printf("-");
    }
    printf("\n"); 
}