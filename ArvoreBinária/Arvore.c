#include <stdio.h>
#include "Arvore.h"

int main (void) {
    Arvore *a = cria_arv_vazia();
    int opcao, valor;

    do {
        printf("\n############################################\n");
        printf(" GENERIC BINARY SEARCH TREE\n");
        printf(" (ARVORE BINARIA GENERICA DE BUSCA)\n");
        printf("############################################\n");
        printf("## [Selecione uma operacao]               ##\n");
        printf("## 1 - Insert Node                        ##\n");
        printf("## 2 - Breadth Search (Busca em largura)  ##\n");
        printf("## 3 - Verify item                        ##\n");
        printf("## 4 - Get MIN / MAX                      ##\n");
        printf("## 5 - Exit                               ##\n");
        printf("############################################\n");
        printf("Digite a opcao: ");
        if (scanf("%d", &opcao) != 1) return 0;

        switch(opcao){
            case 1:
                printf("Digite o valor: ");
                if (scanf("%d", &valor) != 1) return 0;
                a = inserir(a, valor);
                break;
            case 2:
                printf("Arvore em largura: ");
                imprimir_largura(a);
                break;
            case 3:
                printf("Digite o valor a verificar: ");
                if (scanf("%d", &valor) != 1) return 0;
                if(buscar(a, valor)) printf("Encontrado!\n");
                else printf("Nao encontrado!\n");
                break;
            case 4:
                if(a != NULL){
                    printf("MIN: %d | MAX: %d\n", min(a), max(a));
                } else {
                    printf("Arvore vazia!\n");
                }
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 5);

    destroi_arv(a);
    return 0;
}
