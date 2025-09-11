#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_NOME
#define MAX_NOME 100
#endif

typedef struct {
    long int matricula;
    char nome[MAX_NOME];
} Aluno;

static inline void setAluno(Aluno* a, long int mat, const char* nome) {
    if (!a) return;
    a->matricula = mat;
    if (nome) {
        strncpy(a->nome, nome, MAX_NOME - 1);
        a->nome[MAX_NOME - 1] = '\0';
    } else {
        a->nome[0] = '\0';
    }
}

#endif 
