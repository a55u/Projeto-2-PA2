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
#include <stdio.h>
#include <string.h>
#include "utils_mochila.h"

void ordenar_itens(Item itens[], int qtd_itens) {
    /* Implementação manual do Bubble Sort.
    */
    for (int i = 0; i < qtd_itens - 1; i++) {
        for (int j = 0; j < qtd_itens - i - 1; j++) {
            /* Ordenação decrescente: o maior custo-benefício vai para o topo (índice 0) */
            if (itens[j].razao < itens[j + 1].razao) {
                Item temp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = temp;
            }
        }
    }
}

void preencher_mochila(Fase *fase, FILE *fp_out, float *lucro_total) {
    fprintf(fp_out, "FASE: %s\n", fase->nome);
    fprintf(fp_out, "Capacidade da mochila: %.2f kg\n", fase->capacidade_mochila);
    fprintf(fp_out, "Regra aplicada: %s\n", fase->regra);
    
    float capacidade_restante = fase->capacidade_mochila;
    float lucro_fase = 0.0;

    /* REGRA 4 (Templo Subterrâneo): Limita a avaliação estritamente aos 3 maiores coeficientes */
    int limite_itens = fase->qtd_items;
    if (strcmp(fase->regra, "TRES_MELHORES_VALOR_PESO") == 0 && limite_itens > 3) {
        limite_itens = 3;
    }

    /* Algoritmo Guloso Iterativo */
    for(int i = 0; i < limite_itens; i++) {
        /* Se a capacidade zerar antes de acabar os itens, interrompe o laço */
        if(capacidade_restante <= 0) break;

        Item atual = fase->itens[i];

        /* Caso A: O peso do item cabe inteiramente no espaço remanescente */
        if(atual.peso <= capacidade_restante) {
            capacidade_restante -= atual.peso;
            lucro_fase += atual.valor;
            fprintf(fp_out, "Pegou (inteiro) %s (%.2fkg, R$ %.2f)\n", atual.nome, atual.peso, atual.valor);
        } 
        /* Caso B: O item ultrapassa o peso limite. Tentativa de fracionamento */
        else {
            /* REGRA 2 (Ruínas Perdidas): Bloqueia o fracionamento caso o item seja tecnológico */
            if(strcmp(fase->regra, "TECNOLOGICOS_INTEIROS") == 0 && strcmp(atual.tipo, "tecnologico") == 0) {
                /* Ignora a porção fracionária e avança para buscar itens menores que caibam inteiros */
                continue; 
            }

            /* Executa o cálculo da fração necessária para preencher o espaço restante da mochila */
            float peso_fracionado = capacidade_restante;
            float fracao = peso_fracionado / atual.peso;
            float valor_fracionado = atual.valor * fracao; /* Lucro proporcional ao fragmento */
            
            lucro_fase += valor_fracionado;
            fprintf(fp_out, "Pegou (fracionado) %s (%.2fkg, R$ %.2f)\n", atual.nome, peso_fracionado, valor_fracionado);
            
            capacidade_restante = 0; /* A mochila atingiu sua capacidade limite */
        }
    }

    /* Registra os resultados parciais calculados para a fase atual */
    fprintf(fp_out, "Lucro da fase: R$ %.2f\n\n", lucro_fase);
    
    /* Atualiza o ponteiro acumulador do lucro global da campanha */
    *lucro_total += lucro_fase; 
}