#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct no {
    int valor;
    char pergunta[200];
    char alternativas[4][100];
    char resposta_correta;
    int altura;
    struct no *esquerda;
    struct no *direita;
} No;

// ----------- Funções auxiliares --------------
int altura(No *n) {
    return n ? n->altura : 0;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

No *criarNo(int valor, char *pergunta, char alternativas[4][100], char resposta) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    strcpy(novo->pergunta, pergunta);

    for (int i = 0; i < 4; i++)
        strcpy(novo->alternativas[i], alternativas[i]);

    novo->resposta_correta = resposta;
    novo->esquerda = novo->direita = NULL;
    novo->altura = 1;
    return novo;
}

int balanceamento(No *n) {
    return n ? altura(n->esquerda) - altura(n->direita) : 0;
}

// ----------- Rotações AVL --------------
No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = maior(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = maior(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No *rotacaoEsquerda(No *x) {
    No *y = x->direita;
    No *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = maior(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = maior(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

// ----------- INSERIR --------------
No *inserir(No *raiz, int valor, char *pergunta, char alternativas[4][100], char resposta) {
    if (!raiz)
        return criarNo(valor, pergunta, alternativas, resposta);

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor, pergunta, alternativas, resposta);
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor, pergunta, alternativas, resposta);
    else
        return raiz;

    raiz->altura = 1 + maior(altura(raiz->esquerda), altura(raiz->direita));

    int bf = balanceamento(raiz);

    if (bf > 1 && valor < raiz->esquerda->valor)
        return rotacaoDireita(raiz);
    if (bf < -1 && valor > raiz->direita->valor)
        return rotacaoEsquerda(raiz);
    if (bf > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    if (bf < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// ----------- MENOR VALOR --------------
No *minValor(No *n) {
    No *atual = n;
    while (atual->esquerda)
        atual = atual->esquerda;
    return atual;
}

// ----------- REMOVER (FUNDAMENTAL!) --------------
No *remover(No *raiz, int valor) {
    if (!raiz) return raiz;

    if (valor < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = remover(raiz->direita, valor);
    else {
        if (!raiz->esquerda || !raiz->direita) {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (!temp) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            No *temp = minValor(raiz->direita);
            raiz->valor = temp->valor;
            strcpy(raiz->pergunta, temp->pergunta);
            for (int i = 0; i < 4; i++)
                strcpy(raiz->alternativas[i], temp->alternativas[i]);
            raiz->resposta_correta = temp->resposta_correta;

            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }

    if (!raiz) return raiz;

    raiz->altura = 1 + maior(altura(raiz->esquerda), altura(raiz->direita));

    int bf = balanceamento(raiz);

    if (bf > 1 && balanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);
    if (bf > 1 && balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    if (bf < -1 && balanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);
    if (bf < -1 && balanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// ----------- JOGO (REMOVENDO NÓ) --------------
void iniciaJogo(No **raiz) {
    int pontuacao = 0;

    while (*raiz != NULL) {
        No *atual = *raiz;

        printf("\nPergunta (Nível %d): %s\n", atual->valor, atual->pergunta);
        for (int i = 0; i < 4; i++)
            printf("%s\n", atual->alternativas[i]);

        printf("Resposta: ");
        char resp;
        scanf(" %c", &resp);

        if (toupper(resp) == atual->resposta_correta) {
            printf("✓ Correto!\n");
            pontuacao += atual->valor;
        } else {
            printf("✗ Errado! Correta: %c\n", atual->resposta_correta);
        }

        *raiz = remover(*raiz, atual->valor);
    }

    printf("\n--- FIM DO JOGO ---\nPontuação final: %d\n", pontuacao);
}

// ---------- LIBERAR --------------
void liberarArvore(No *raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

#endif
