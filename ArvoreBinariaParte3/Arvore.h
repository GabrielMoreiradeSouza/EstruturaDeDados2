#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _arvore {
   int info;
   struct _arvore *esq;
   struct _arvore *dir;
} Arvore;

typedef struct _fila {
    Arvore *no;
    struct _fila *prox;
} Fila;

static inline void enfileirar(Fila **ini, Fila **fim, Arvore *no){
    Fila *novo = (Fila*)malloc(sizeof(Fila));
    if (!novo) exit(EXIT_FAILURE);
    novo->no = no;
    novo->prox = NULL;
    if(*fim != NULL) (*fim)->prox = novo;
    else *ini = novo;
    *fim = novo;
}

static inline Arvore* desenfileirar(Fila **ini, Fila **fim){
    if(*ini == NULL) return NULL;
    Fila *tmp = *ini;
    Arvore *no = tmp->no;
    *ini = (*ini)->prox;
    if(*ini == NULL) *fim = NULL;
    free(tmp);
    return no;
}

static inline Arvore* cria_arv_vazia (void) {
   return NULL;
}

static inline Arvore* inserir (Arvore *a, int v){
    if(a == NULL){
        a=(Arvore*)malloc(sizeof(Arvore));
        if (!a) exit(EXIT_FAILURE);
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

static inline int buscar (Arvore *a, int v){
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

static inline int min (Arvore *a){
    if(!a){ fprintf(stderr,"Erro: arvore vazia em min()\n"); exit(EXIT_FAILURE); }
    if( a->esq != NULL){
        return min(a->esq);
    }
    else{
         return a->info;
    }
}

static inline int max (Arvore *a){
    if(!a){ fprintf(stderr,"Erro: arvore vazia em max()\n"); exit(EXIT_FAILURE); }
    if (a->dir != NULL){
        return max(a->dir);
    }
    else{
        return a->info;
    }
}

static inline void destroi_arv (Arvore *arv) {
   if (arv != NULL) {
      destroi_arv (arv->esq);
      destroi_arv (arv->dir);
      free(arv);
   }
}

static inline void imprimir_largura(Arvore *a){
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

static inline void imprimir_em_ordem(Arvore *a){
    if(a != NULL){
        imprimir_em_ordem(a->esq);
        printf("%d ", a->info);
        imprimir_em_ordem(a->dir);
    }
}

static inline void imprimir_pre_ordem(Arvore *a){
    if(a != NULL){
        printf("%d ", a->info);
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
    }
}

static inline void imprimir_pos_ordem(Arvore *a){
    if(a != NULL){
        imprimir_pos_ordem(a->esq);
        imprimir_pos_ordem(a->dir);
        printf("%d ", a->info);
    }
}

static inline Arvore* remover_fusao(Arvore *a, int v) {
    if (a == NULL) return NULL;

    if (v < a->info) {
        a->esq = remover_fusao(a->esq, v);
    } else if (v > a->info) {
        a->dir = remover_fusao(a->dir, v);
    } else { // Achou o nó a remover
        Arvore *temp = a;
        if (a->esq == NULL) {
            a = a->dir;
            free(temp);
        } else if (a->dir == NULL) {
            a = a->esq;
            free(temp);
        } else {
            Arvore *aux = a->esq;
            while (aux->dir != NULL) aux = aux->dir;
            aux->dir = a->dir;
            a = a->esq;
            free(temp);
        }
    }
    return a;
}

static inline Arvore* remover_copia(Arvore *a, int v) {
    if (a == NULL) return NULL;

    if (v < a->info) {
        a->esq = remover_copia(a->esq, v);
    } else if (v > a->info) {
        a->dir = remover_copia(a->dir, v);
    } else { 
        Arvore *temp = a;
        if (a->esq == NULL) {
            a = a->dir;
            free(temp);
        } else if (a->dir == NULL) {
            a = a->esq;
            free(temp);
        } else {
            Arvore *aux = a->esq;
            while (aux->dir != NULL) aux = aux->dir;
            a->info = aux->info; 
            a->esq = remover_copia(a->esq, aux->info); 
        }
    }
    return a;
}
#endif 