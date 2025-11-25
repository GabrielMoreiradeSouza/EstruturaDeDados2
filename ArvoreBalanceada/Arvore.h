#include <stdio.h>
#include <stdlib.h>

#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

//FUNÇÕES AUXILIARES
int height(Node* n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->height = 1;
    n->left = n->right = NULL;

    printf("[CRIACAO] Novo nó criado com valor %d\n", key);
    return n;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// ROTAÇÃO AVL COM LOGS
Node* rightRotate(Node* y) {
    printf("  -> Rotacao SIMPLES à DIREITA no nó %d\n", y->key);

    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    printf("  -> Rotacao SIMPLES à ESQUERDA no nó %d\n", x->key);

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

//INSERÇÃO AVL + LOGS
Node* insert(Node* node, int key) {

    if (node == NULL) {
        printf("[INSERCAO] Inserindo %d\n", key);
        return newNode(key);
    }

    if (key < node->key) {
        printf("[INSERCAO] %d < %d (indo para esquerda)\n", key, node->key);
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        printf("[INSERCAO] %d > %d (indo para direita)\n", key, node->key);
        node->right = insert(node->right, key);
    }
    else {
        printf("[INSERCAO] Valor duplicado! Ignorando.\n");
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    printf("[BALANCEAMENTO] Nó %d -> fator = %d\n", node->key, balance);

    //ROTAÇÃO SIMPLES A DIREITA
    if (balance > 1 && key < node->left->key) {
        printf("[ROTACAO] Simples à DIREITA (LL) no nó %d\n", node->key);
        return rightRotate(node);
    }

    //ROTAÇÃO SIMPLES A ESQUERDA
    if (balance < -1 && key > node->right->key) {
        printf("[ROTACAO] Simples à ESQUERDA (RR) no nó %d\n", node->key);
        return leftRotate(node);
    }

    //ROTAÇÃO DUPLA ESQUERDA-DIREITA
    if (balance > 1 && key > node->left->key) {
        printf("[ROTACAO] DUPLA ESQUERDA-DIREITA (LR) no nó %d\n", node->key);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //ROTAÇÃO DUPLA DIREITA-ESQUERDA
    if (balance < -1 && key < node->right->key) {
        printf("[ROTACAO] DUPLA DIREITA-ESQUERDA (RL) no nó %d\n", node->key);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//BUSCA
int search(Node* root, int key) {
    if (!root) return 0;
    if (root->key == key) return 1;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

//PERCURSO
void inOrder(Node* root) {
    if (!root) return;
    inOrder(root->left);
    printf("%d ", root->key);
    inOrder(root->right);
}

void preOrder(Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->key);
}

//BUSCAR LARGURA
void breadthSearch(Node* root) {
    if (!root) return;

    Node* queue[1000];
    int start = 0, end = 0;

    queue[end++] = root;

    while (start < end) {
        Node* cur = queue[start++];

        printf("%d ", cur->key);

        if (cur->left) queue[end++] = cur->left;
        if (cur->right) queue[end++] = cur->right;
    }

    printf("\n");
}

//LIMPAR
void clearTree(Node* root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    printf("[FREE] Removendo nó %d\n", root->key);
    free(root);
}

#endif
