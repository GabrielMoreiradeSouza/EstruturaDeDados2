#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _arvore {
    int info;
    struct _arvore *esq;
    struct _arvore *dir;
} Arvore;

typedef struct _pilha {
    Arvore *no;
    struct _pilha *prox;
} Pilha;

// Empilha um nó (adiciona no topo)
static inline void push(Pilha **topo, Arvore *no) {
    Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
    if (!novo) exit(EXIT_FAILURE);
    novo->no = no;
    novo->prox = *topo;
    *topo = novo;
}

static inline Arvore* pop(Pilha **topo) {
    if (*topo == NULL) return NULL;
    Pilha *tmp = *topo;
    Arvore *no = tmp->no;
    *topo = (*topo)->prox;
    free(tmp);
    return no;
}

static inline int pilha_vazia(Pilha *topo) {
    return topo == NULL;
}


static inline Arvore* cria_arv_vazia (void) {
    return NULL;
}

static inline Arvore* inserir (Arvore *a, int v){
    if(a == NULL){
        a = (Arvore*)malloc(sizeof(Arvore));
        if (!a) exit(EXIT_FAILURE);
        a->info = v;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if(v < a->info){
        a->esq = inserir(a->esq,v);
    }
    else if (v > a->info){ 
        a->dir = inserir(a->dir,v);
    }
    return a;
}

static inline int buscar (Arvore *a, int v){
    if(a == NULL){
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
    while(a->esq != NULL) {
        a = a->esq;
    }
    return a->info;
}

static inline int max (Arvore *a){
    if(!a){ fprintf(stderr,"Erro: arvore vazia em max()\n"); exit(EXIT_FAILURE); }
    while(a->dir != NULL) {
        a = a->dir;
    }
    return a->info;
}

static inline void destroi_arv (Arvore *arv) {
    if (arv != NULL) {
        destroi_arv (arv->esq);
        destroi_arv (arv->dir);
        free(arv);
    }
}

static inline void imprimir_em_ordem_iterativo(Arvore *a) {
    if (a == NULL) return;
    Pilha *p = NULL;
    Arvore *atual = a;

    while (atual != NULL || !pilha_vazia(p)) {
        while (atual != NULL) {
            push(&p, atual);
            atual = atual->esq;
        }
        atual = pop(&p);
        printf("%d ", atual->info);
        atual = atual->dir;
    }
}

static inline void imprimir_pre_ordem_iterativo(Arvore *a) {
    if (a == NULL) return;
    Pilha *p = NULL;
    push(&p, a);

    while (!pilha_vazia(p)) {
        Arvore *atual = pop(&p);
        printf("%d ", atual->info);

        if (atual->dir != NULL) push(&p, atual->dir);
        if (atual->esq != NULL) push(&p, atual->esq);
    }
}

static inline void imprimir_pos_ordem_iterativo(Arvore *a) {
    if (a == NULL) return;
    Pilha *p1 = NULL, *p2 = NULL;
    push(&p1, a);

    while (!pilha_vazia(p1)) {
        Arvore *atual = pop(&p1);
        push(&p2, atual);

        if (atual->esq != NULL) push(&p1, atual->esq);
        if (atual->dir != NULL) push(&p1, atual->dir);
    }

    while (!pilha_vazia(p2)) {
        Arvore *atual = pop(&p2);
        printf("%d ", atual->info);
    }
}

#endif