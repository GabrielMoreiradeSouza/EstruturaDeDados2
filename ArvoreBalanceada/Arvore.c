#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

int main() {
    Node* root = NULL;
    int opcao, valor;

    do {
        printf("\n#############################################\n");
        printf("                  AVL TREE\n");
        printf("               (ARVORE AVL)\n");
        printf("#############################################\n");
        printf("##                                         ##\n");
        printf("##     [Selecione uma operacao]            ##\n");
        printf("##                                         ##\n");
        printf("##  1 - Insert Node                        ##\n");
        printf("##  2 - Breadth Search (Busca em largura)  ##\n");
        printf("##  3 - Verify item                        ##\n");
        printf("##  4 - Clear Tree                         ##\n");
        printf("##  5 - Depth Search (In Order)            ##\n");
        printf("##  6 - Depth Search (Pre Order)           ##\n");
        printf("##  7 - Depth Search (Pos Order)           ##\n");
        printf("##  8 - Exit                               ##\n");
        printf("##                                         ##\n");
        printf("#############################################\n");
        printf("\nDigite a opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                printf("Digite um valor: ");
                scanf("%d", &valor);
                root = insert(root, valor);
                break;

            case 2:
                breadthSearch(root);
                break;

            case 3:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                if (search(root, valor))
                    printf("Item encontrado!\n");
                else
                    printf("Item NAO encontrado!\n");
                break;

            case 4:
                clearTree(root);
                root = NULL;
                printf("Arvore limpa!\n");
                break;

            case 5:
                inOrder(root);
                break;

            case 6:
                preOrder(root);
                break;

            case 7:
                postOrder(root);
                break;

            case 8:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 8);

    return 0;
}
