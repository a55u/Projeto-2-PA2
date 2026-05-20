/*
========================================
NOME                            RA

Aline Vidal                     10721348
Beatriz Ferreira Vianna         10729512
João Vitor Fernandes Messias    10723552
Kauê Lima Rodrigues Meneses     10410594
Rayana Pimentel Marques Lopes   10435370
========================================
*/
#define MAX_NOME 50

/*
    .h para controle de variaveis globais do jogo.
    
    MAX_NOME = 50 somente para testes, da pra reduzir depois para 15-20.
    cada variavel das estruturas representa um atributo da mochila fracionaria
    e das fases.

    Esse arquivo é essencial para o processamento das regras em ../regras.c!
    
    
*/

typedef struct Item{
    char nome[MAX_NOME];
    float peso;
    float valor;
    char tipo[20];
}Item;

typedef struct Fase{
    char nome[MAX_NOME];
    float capacidade_mochila;
    char regra[30];
    Item itens[100];
    int qtd_items;
}Fase;