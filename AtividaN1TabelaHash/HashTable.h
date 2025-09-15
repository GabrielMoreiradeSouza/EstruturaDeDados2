#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "Aluno.h"

#ifndef TABLE_SIZE
#define TABLE_SIZE 2
#endif

typedef struct Node {
    Aluno data;
    struct Node* prox;
} Node;

typedef struct {
    Node* tabela[TABLE_SIZE];   
} HashTable;

int hashFunction(long int mat) {
    if (mat < 0) mat = -mat;
    return (int)(mat % TABLE_SIZE);
}

void initHashTable(HashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < TABLE_SIZE; ++i)
        ht->tabela[i] = NULL;
}

void insertItem(HashTable* ht, Aluno* aluno) {
    if (!ht || !aluno) return;
    int idx = hashFunction(aluno->matricula);
    Node* novo = (Node*)malloc(sizeof(Node));
    if (!novo) return;
    novo->data = *aluno;            
    novo->prox = ht->tabela[idx];
    ht->tabela[idx] = novo;
}

void deleteItem(HashTable* ht, Aluno* aluno) {
    if (!ht && !aluno) return;
    int idx = hashFunction(aluno->matricula);
    Node *cur = ht->tabela[idx], *prev = NULL;

    while (cur) {
        if (cur->data.matricula == aluno->matricula) {
            if (prev) prev->prox = cur->prox;
            else ht->tabela[idx] = cur->prox;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->prox;
    }
}

void displayHashTable(HashTable* ht) {
    if (!ht) return;
    printf("\nTabela Hash:\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("%d", i);
        for (Node* n = ht->tabela[i]; n; n = n->prox)
            printf(" -> [%ld, %s]", n->data.matricula, n->data.nome);
        printf("\n");
    }
}

#endif 
