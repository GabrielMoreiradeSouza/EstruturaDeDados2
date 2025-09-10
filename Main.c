#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aluno.h"

/* Usadas pelo Main.c; deixe aqui para garantir a compilação */
#ifndef TABLE_SIZE
#define TABLE_SIZE 10
#endif

#ifndef MAX_NOME
#define MAX_NOME 100
#endif

typedef struct Node {
    Aluno dado;           
    struct Node* prox;
} Node;

typedef struct {
    int tamanhoTabela;     
    Node** tabela;         
} HashTable;

void setAluno(Aluno* a, long int mat, const char* nome) {
    if (!a) return;
    a->matricula = mat;
    if (nome) {
        strncpy(a->nome, nome, sizeof(a->nome) - 1);
        a->nome[sizeof(a->nome) - 1] = '\0';
    } else {
        a->nome[0] = '\0';
    }
}

int hashFunction(long int mat) {
    if (mat < 0) mat = -mat;
    return (int)(mat % TABLE_SIZE);
}

void initHashTable(HashTable* ht) {
    if (!ht) return;
    ht->tamanhoTabela = TABLE_SIZE;
    ht->tabela = (Node**)malloc(ht->tamanhoTabela * sizeof(Node*));
    if (!ht->tabela) {
        fprintf(stderr, "Falha ao alocar tabela hash.\n");
        ht->tamanhoTabela = 0;
        return;
    }
    for (int i = 0; i < ht->tamanhoTabela; i++)
        ht->tabela[i] = NULL;
}

void insertItem(HashTable* ht, Aluno* aluno) {
    if (!ht || !ht->tabela || !aluno) return;
    int idx = hashFunction(aluno->matricula);

    Node* novo = (Node*)malloc(sizeof(Node));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar nó.\n");
        return;
    }
    novo->dado = *aluno;   
    novo->prox = ht->tabela[idx];
    ht->tabela[idx] = novo;
}

void deleteItem(HashTable* ht, Aluno* aluno) {
    if (!ht || !ht->tabela || !aluno) return;
    int idx = hashFunction(aluno->matricula);

    Node* atual = ht->tabela[idx];
    Node* anterior = NULL;

    while (atual) {
        if (atual->dado.matricula == aluno->matricula) {
            if (anterior) anterior->prox = atual->prox;
            else ht->tabela[idx] = atual->prox;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void displayHashTable(HashTable* ht) {
    if (!ht || !ht->tabela) return;
    for (int i = 0; i < ht->tamanhoTabela; i++) {
        printf("[%d] ", i);
        Node* p = ht->tabela[i];
        if (!p) {
            printf("∅\n");
            continue;
        }
        while (p) {
            printf("(%ld, %s)", p->dado.matricula, p->dado.nome);
            if (p->prox) printf(" -> ");
            p = p->prox;
        }
        printf("\n");
    }
}
#endif 