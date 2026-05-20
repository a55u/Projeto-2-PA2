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
#include <stdlib.h>
#include <string.h>
#include "utils/utils.h"

void data(FILE *fp_in, Fase jogo[], int *total_fases){
    char linha;
    int f = -1;

    // Percorre o arquivo linha por linha
    while(fgets(linha, sizeof(linha),fp_in) != NULL){
        if(strncmp(linha, "FASE:", 5) == 0){
            f++;
            jogo[f].qtd_items = 0;
            sscanf(linha, "FASE: %[^\n]", jogo[f].nome);
        }
        else if(strncmp(linha, "CAPACIDADE:", 11) == 0){
            sscanf(linha, "CAPACIDADE: %f", &jogo[f].capacidade_mochila);
        }
        else if(strncmp(linha, "REGRA:", 6) == 0){
            sscanf(linha, "REGRA: %s", jogo[f].regra);
        }
        else if(strncmp(linha, "ITEM:",5) == 0){
            int i = jogo[f].qtd_items;
            sscanf(linha, "ITEM: %[^,], %f, %f, %s", jogo[f].itens[i].nome, &jogo[f].itens[i].peso, &jogo[f].itens[i].valor, jogo[f].itens[i].tipo);
            jogo[f].qtd_items++;
        }
    }
    
    // Atualiza o ponteiro de total de fases no final da leitura
    if (total_fases != NULL) {
        *total_fases = f + 1;
    }
}

int main(int argc, char *argv[]){
    // 1. Validação de Argumentos
    if(argc < 3){
        printf("Uso: %s path: <entrada.txt>  path: <saida.txt>\n", argv);
        return 1;
    }

    char *in = argv[1];
    char *out = argv[2];

    // 2. Abertura e Validação de Arquivos
    FILE *fp_in = fopen(in, "r");
    if(fp_in == NULL){
        printf("Erro ao abrir arquivo de entrada: verifique se %s está correto ou existe\n", argv[1]);
        return 1;
    }
    
    FILE *fp_out = fopen(out, "w");
    if(fp_out == NULL){
        printf("Erro ao criar arquivo de saida\n");
        fclose(fp_in); // CORREÇÃO: Fecha o arquivo de entrada que abriu com sucesso
        return 1;      // Removido o fclose(fp_out) porque não se fecha um arquivo nulo
    }

    printf("Arquivos de I/O definidos: %s e %s\n", in, out);

    // 3. Inicialização e Processamento dos Dados
    Fase jogo[10];       // Vetor de fases (tamanho 10 é mais do que suficiente para as 4 do PDF)
    int total_fases = 0; // Variável para rastrear quantas fases foram carregadas

    // Passa os arquivos e variáveis para a função popular o array "jogo"
    data(fp_in, jogo, &total_fases);
    
    // Teste rápido para validar se o carregamento funcionou
    printf("Total de fases carregadas: %d\n", total_fases);

    // 4. Fechamento Limpo
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}