#include <stdio.h>
#include "Arvore.h"

int main(void) {
    Arvore *a = cria_arv_vazia();
    int opcao, valor;

    do {
        printf("\n############################################\n");
        printf(" GENERIC BINARY SEARCH TREE\n");
        printf(" (ARVORE BINARIA GENERICA DE BUSCA)\n");
        printf("############################################\n");
        printf("## [Selecione uma operacao]              ##\n");
        printf("## 1 - Inserir no                        ##\n");
        printf("## 2 - Imprimir (Largura)                ##\n");
        printf("## 3 - Verificar item                    ##\n");
        printf("## 4 - Obter MIN / MAX                   ##\n");
        printf("## 5 - Imprimir (Em-ordem)               ##\n");
        printf("## 6 - Imprimir (Pre-ordem)              ##\n");
        printf("## 7 - Imprimir (Pos-ordem)              ##\n");
        printf("## 8 - Delete By Merging (por fusao)     ##\n");
        printf("## 9 - Delete By Copying (por copia)     ##\n");
        printf("## 10 - Sair                             ##\n");
        printf("############################################\n");
        printf("Digite a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Saindo.\n");
            return 0;
        }

        switch(opcao) {
            case 1:
                printf("Digite o valor: ");
                if (scanf("%d", &valor) != 1) return 0;
                a = inserir(a, valor);
                printf("Valor %d inserido!\n", valor);
                break;

            case 2:
                if (!a) printf("Arvore vazia!\n");
                else {
                    printf("Arvore em largura: ");
                    imprimir_largura(a);
                }
                break;

            case 3:
                printf("Digite o valor a verificar: ");
                if (scanf("%d", &valor) != 1) return 0;
                if (buscar(a, valor))
                    printf("O valor %d foi encontrado!\n", valor);
                else
                    printf("O valor %d nao foi encontrado!\n", valor);
                break;

            case 4:
                if (a != NULL)
                    printf("MIN: %d | MAX: %d\n", min(a), max(a));
                else
                    printf("Arvore vazia!\n");
                break;

            case 5:
                if (!a) printf("Arvore vazia!\n");
                else {
                    printf("Arvore em ordem: ");
                    imprimir_em_ordem(a);
                    printf("\n");
                }
                break;

            case 6:
                if (!a) printf("Arvore vazia!\n");
                else {
                    printf("Arvore em pre-ordem: ");
                    imprimir_pre_ordem(a);
                    printf("\n");
                }
                break;

            case 7:
                if (!a) printf("Arvore vazia!\n");
                else {
                    printf("Arvore em pos-ordem: ");
                    imprimir_pos_ordem(a);
                    printf("\n");
                }
                break;

            case 8:
                if (!a) {
                    printf("Arvore vazia!\n");
                } else {
                    printf("Digite o valor a remover (fusao): ");
                    if (scanf("%d", &valor) != 1) return 0;
                    a = remover_fusao(a, valor);
                    printf("Valor %d removido (por fusao)!\n", valor);
                }
                break;

            case 9:
                if (!a) {
                    printf("Arvore vazia!\n");
                } else {
                    printf("Digite o valor a remover (copia): ");
                    if (scanf("%d", &valor) != 1) return 0;
                    a = remover_copia(a, valor);
                    printf("Valor %d removido (por copia)!\n", valor);
                }
                break;

            case 10:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 10);

    destroi_arv(a);
    return 0;
}
