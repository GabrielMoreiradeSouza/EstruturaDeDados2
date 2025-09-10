#ifndef HASHTABLE_H
#define HASHTABLE_H

#ifndef TABLE_SIZE
#define TABLE_SIZE 2      
#endif

#ifndef MAX_NOME
#define MAX_NOME 100      
#endif

typedef struct Node {
    Aluno data;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

void setAluno(Aluno* a, long int mat, const char* nome) {
    if (!a) return;
    a->matricula = mat;
    strncpy(a->nome, nome ? nome : "", sizeof(a->nome) - 1);
    a->nome[sizeof(a->nome) - 1] = '\0';
}

int hashFunction(long int mat) {
    if (mat < 0) mat = -mat;
    return (int)(mat % TABLE_SIZE);
}

void initHashTable(HashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < TABLE_SIZE; ++i)
        ht->buckets[i] = NULL;
}

void insertItem(HashTable* ht, Aluno* aluno) {
    if (!ht || !aluno) return;
    int idx = hashFunction(aluno->matricula);
    Node* curr = ht->buckets[idx];

    for (Node* p = curr; p; p = p->next) {
        if (p->data.matricula == aluno->matricula) {
            p->data = *aluno; 
            return;
        }
    }

    Node* novo = (Node*)malloc(sizeof(Node));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para Node.\n");
        return;
    }
    novo->data = *aluno; 
    novo->next = ht->buckets[idx];
    ht->buckets[idx] = novo;
}

void deleteItem(HashTable* ht, Aluno* aluno) {
    if (!ht || !aluno) return;
    int idx = hashFunction(aluno->matricula);
    Node* curr = ht->buckets[idx];
    Node* prev = NULL;

    while (curr) {
        if (curr->data.matricula == aluno->matricula) {
            if (prev) prev->next = curr->next;
            else ht->buckets[idx] = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void displayHashTable(HashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("[%d] ", i);
        Node* p = ht->buckets[i];
        if (!p) {
            printf("∅\n");
            continue;
        }
        while (p) {
            printf("(%ld, %s)", p->data.matricula, p->data.nome);
            if (p->next) printf(" -> ");
            p = p->next;
        }
        printf("\n");
    }
}

#endif 
