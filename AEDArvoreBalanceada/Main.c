#include <stdio.h>
#include "Arvore.h"

int main() {
    No *raiz = NULL;

    char perguntas[15][200] = {
        "Quanto eh 2 + 2?",
        "Qual a capital do Brasil?",
        "Quem escreveu 'Dom Quixote'?",
        "Quantos planetas existem no sistema solar?",
        "Qual o elemento quimico representado por 'O'?",
        "Que ano terminou a Segunda Guerra Mundial?",
        "Qual o maior planeta do sistema solar?",
        "Quem pintou a 'Mona Lisa'?",
        "Qual a raiz quadrada de 64?",
        "Quantos ossos tem o corpo humano adulto?",
        "Qual pais eh conhecido como Terra do Sol Nascente?",
        "Em que continente fica o Egito?",
        "Quem desenvolveu a teoria da relatividade?",
        "Qual eh o maior deserto do mundo?",
        "Qual eh o simbolo quimico do ferro?"
    };

    char alternativas[15][4][100] = {
        { "A) 3", "B) 4", "C) 5", "D) 6" },
        { "A) Rio de Janeiro", "B) Brasilia", "C) Sao Paulo", "D) Salvador" },
        { "A) Machado de Assis", "B) Cervantes", "C) Shakespeare", "D) Lima Barreto" },
        { "A) 7", "B) 8", "C) 9", "D) 10" },
        { "A) Ouro", "B) Oxigenio", "C) Osmio", "D) Oganessao" },
        { "A) 1945", "B) 1939", "C) 1941", "D) 1950" },
        { "A) Terra", "B) Jupiter", "C) Saturno", "D) Marte" },
        { "A) Van Gogh", "B) Picasso", "C) Da Vinci", "D) Monet" },
        { "A) 6", "B) 7", "C) 8", "D) 9" },
        { "A) 206", "B) 207", "C) 208", "D) 209" },
        { "A) China", "B) Japao", "C) Coreia do Sul", "D) India" },
        { "A) Africa", "B) Asia", "C) Europa", "D) America" },
        { "A) Newton", "B) Einstein", "C) Galileo", "D) Tesla" },
        { "A) Saara", "B) Antartida", "C) Gobi", "D) Kalahari" },
        { "A) Fe", "B) Ir", "C) F", "D) In" }
    };

    char respostas[15] = { 'B','B','B','B','B','A','B','C','C','A','B','A','B','B','A' };

    for (int i = 0; i < 15; i++)
        raiz = inserir(raiz, i+1, perguntas[i], alternativas[i], respostas[i]);

    iniciaJogo(&raiz);

    liberarArvore(raiz);
    return 0;
}
