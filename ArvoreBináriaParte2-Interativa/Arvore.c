#include <stdio.h>
#include "Arvore.h"

int main (void) {
    Arvore *a = cria_arv_vazia();
    int opcao, valor;

    do {
        printf("\n############################################\n");
        printf("     ARVORE BINARIA DE BUSCA (ITERATIVA)\n");
        printf("############################################\n");
        printf("## 1 - Inserir Valor                      ##\n");
        printf("## 2 - Buscar Valor                       ##\n");
        printf("## 3 - Exibir MIN / MAX                   ##\n");
        printf("## 4 - Imprimir Em-Ordem (Iterativo)      ##\n");
        printf("## 5 - Imprimir Pre-Ordem (Iterativo)     ##\n");
        printf("## 6 - Imprimir Pos-Ordem (Iterativo)     ##\n");
        printf("## 7 - Sair                               ##\n");
        printf("############################################\n");
        printf("Digite a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            opcao = 0;
        }

        switch(opcao){
            case 1:
                printf("Digite o valor a inserir: ");
                if (scanf("%d", &valor) != 1) {
                    while(getchar() != '\n');
                    printf("Entrada invalida!\n");
                    break;
                }
                a = inserir(a, valor);
                printf("Valor %d inserido.\n", valor);
                break;

            case 2:
                printf("Digite o valor a buscar: ");
                if (scanf("%d", &valor) != 1) {
                    while(getchar() != '\n');
                    printf("Entrada invalida!\n");
                    break;
                }
                if(buscar(a, valor)) printf("Valor %d encontrado na arvore.\n", valor);
                else printf("Valor %d NAO encontrado na arvore.\n", valor);
                break;

            case 3:
                if (a != NULL) {
                    printf("MIN: %d | MAX: %d\n", min(a), max(a));
                } else {
                    printf("A arvore esta vazia!\n");
                }
                break;

            case 4:
                if (a != NULL) {
                    printf("Impressao Em-Ordem: ");
                    imprimir_em_ordem_iterativo(a);
                    printf("\n");
                } else {
                    printf("A arvore esta vazia!\n");
                }
                break;

            case 5:
                if (a != NULL) {
                    printf("Impressao Pre-Ordem: ");
                    imprimir_pre_ordem_iterativo(a);
                    printf("\n");
                } else {
                    printf("A arvore esta vazia!\n");
                }
                break;

            case 6:
                if (a != NULL) {
                    printf("Impressao Pos-Ordem: ");
                    imprimir_pos_ordem_iterativo(a);
                    printf("\n");
                } else {
                    printf("A arvore esta vazia!\n");
                }
                break;

            case 7:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 7);

    destroi_arv(a);
    printf("Memoria liberada. Fim.\n");
    return 0;
}