#ifndef UTILS_MOCHILA_H
#define UTILS_MOCHILA_H

#include <stdio.h>

/* Tamanho máximo para strings de nomes */
#define MAX_NOME 50

/**
 * @struct Item
 * @brief Estrutura que armazena as propriedades individuais de cada item do jogo.
 */
typedef struct Item {
    char nome[MAX_NOME];   /**< Nome do item */
    float peso;            /**< Peso do item em kg */
    float valor;           /**< Valor monetário do item em R$ */
    char tipo[20];         /**< Categoria/Tipo do item (ex: magico, tecnologico) */
    float razao;           /**< Razão de custo-benefício (Valor / Peso) usada pelo algoritmo guloso */
} Item;

/**
 * @struct Fase
 * @brief Estrutura que agrupa todos os dados de um cenário específico do jogo.
 */
typedef struct Fase {
    char nome[MAX_NOME];            /**< Nome identificador da fase */
    float capacidade_mochila;      /**< Limite máximo de peso suportado pela mochila nesta etapa */
    char regra[30];                /**< Identificador textual da regra especial vigente */
    Item itens[100];               /**< Vetor de itens disponíveis para coleta na fase */
    int qtd_items;                 /**< Contador de itens cadastrados na fase */
} Fase;

/* =========================================================================
   PROTÓTIPOS DAS FUNÇÕES (Interfaces de Comunicação entre Módulos)
   ========================================================================= */

/**
 * @brief Efetua o parse (leitura estruturada) dos dados das fases a partir do arquivo txt.
 * @param fp_in Ponteiro para o descritor do arquivo de entrada (modo leitura).
 * @param jogo Vetor de structs onde as fases carregadas serão armazenadas.
 * @param total_fases Ponteiro de retorno para armazenar a quantidade total de fases lidas.
 */
void carregar_dados(FILE *fp_in, Fase jogo[], int *total_fases);

/**
 * @brief Aplica os modificadores de valor aos itens com base na regra especial da fase.
 * @param fase Ponteiro para a fase cujos itens sofrerão as alterações de valor.
 */
void aplicar_regras(Fase *fase);

/**
 * @brief Ordena os itens em ordem decrescente de custo-benefício (Razão Valor/Peso).
 * @param itens Vetor contendo a lista de itens a ser ordenada.
 * @param qtd_itens Quantidade total de elementos válidos no vetor.
 */
void ordenar_itens(Item itens[], int qtd_itens);

/**
 * @brief Implementa o Algoritmo da Mochila Fracionária baseado na estratégia gulosa.
 * @param fase Ponteiro para a fase atual contendo os itens e a capacidade da mochila.
 * @param fp_out Ponteiro para o arquivo onde o relatório de decisões será gravado.
 * @param lucro_total Ponteiro acumulador do lucro obtido ao longo de toda a jornada.
 */
void preencher_mochila(Fase *fase, FILE *fp_out, float *lucro_total);

#endif /* UTILS_MOCHILA_H */