#include <stdio.h>
#include <stdlib.h>

/***************** Estrutura da Árvore *********************/

typedef struct _arvore {
   int info;
   struct _arvore *esq;
   struct _arvore *dir;
} Arvore;


/***************** Estrutura da Fila (para BFS) *********************/

typedef struct _fila {
    Arvore *no;
    struct _fila *prox;
} Fila;

void enfileirar(Fila **ini, Fila **fim, Arvore *no){
    Fila *novo = (Fila*)malloc(sizeof(Fila));
    novo->no = no;
    novo->prox = NULL;
    if(*fim != NULL) (*fim)->prox = novo;
    else *ini = novo;
    *fim = novo;
}

Arvore* desenfileirar(Fila **ini, Fila **fim){
    if(*ini == NULL) return NULL;
    Fila *tmp = *ini;
    Arvore *no = tmp->no;
    *ini = (*ini)->prox;
    if(*ini == NULL) *fim = NULL;
    free(tmp);
    return no;
}


/***************** Funções da Árvore *********************/

Arvore* cria_arv_vazia () {
   return NULL;
}

Arvore* inserir (Arvore *a, int v){
    if(a == NULL){
        a=(Arvore*)malloc(sizeof(Arvore));
        a->info = v;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if(v < a->info){
        a->esq = inserir(a->esq,v);
    }
    else{
        a->dir = inserir(a->dir,v);
    }
    return a;
}

int buscar (Arvore *a, int v){
    if(a==NULL){
        return 0;
    }
    else if(v < a->info){
        return buscar(a->esq,v);
    }
    else if(v > a->info){
        return buscar(a->dir,v);
    }
    else{
        return 1;
    }
}

int min (Arvore *a){
    if( a->esq != NULL){
        return min(a->esq);
    }
    else{
         return a->info;
    }
}

int max (Arvore *a){
    if (a->dir != NULL){
        return max(a->dir);
    }
    else{
        return a->info;
    }
}

void destroi_arv (Arvore *arv) {
   if (arv != NULL) {
      destroi_arv (arv->esq);
      destroi_arv (arv->dir);
      free(arv);
   }
}


/***************** Impressão em largura (BFS) *********************/

void imprimir_largura(Arvore *a){
    if(a == NULL){
        printf("Arvore vazia!\n");
        return;
    }
    Fila *ini = NULL, *fim = NULL;
    enfileirar(&ini, &fim, a);
    while(ini != NULL){
        Arvore *atual = desenfileirar(&ini, &fim);
        printf("%d ", atual->info);
        if(atual->esq != NULL) enfileirar(&ini, &fim, atual->esq);
        if(atual->dir != NULL) enfileirar(&ini, &fim, atual->dir);
    }
    printf("\n");
}


/****************** Programa Principal **********************/

int main () {
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
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                a = inserir(a, valor);
                break;
            case 2:
                printf("Arvore em largura: ");
                imprimir_largura(a);
                break;
            case 3:
                printf("Digite o valor a verificar: ");
                scanf("%d", &valor);
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
