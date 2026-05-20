#include <stdio.h>
#include <string.h>
#include "utils/utils_mochila.h"

void carregar_dados(FILE *fp_in, Fase jogo[], int *total_fases) {
    char linha[256];
    int f = -1;

    /* Varre o arquivo linha por linha de forma segura até atingir o fim (EOF) */
    while(fgets(linha, sizeof(linha), fp_in) != NULL) {
        
        /* Caso a linha identifique o cabeçalho de uma nova FASE */
        if(strncmp(linha, "FASE:", 5) == 0) {
            f++;
            jogo[f].qtd_items = 0;
            sscanf(linha, "FASE: %[^\n]", jogo[f].nome);
        }
        /* Captura a CAPACIDADE máxima da mochila na fase */
        else if(strncmp(linha, "CAPACIDADE:", 11) == 0) {
            sscanf(linha, "CAPACIDADE: %f", &jogo[f].capacidade_mochila);
        }
        /* Captura o identificador da REGRA especial */
        else if(strncmp(linha, "REGRA:", 6) == 0) {
            sscanf(linha, "REGRA: %s", jogo[f].regra);
        }
        /* Efetua a divisão e extração dos atributos do ITEM */
        else if(strncmp(linha, "ITEM:", 5) == 0) {
            int i = jogo[f].qtd_items;
            
            /* %[^,] lê strings compostas por espaços até encontrar a primeira vírgula */
            sscanf(linha, "ITEM: %[^,], %f,%f,%s", 
                   jogo[f].itens[i].nome, 
                   &jogo[f].itens[i].valor, 
                   &jogo[f].itens[i].peso, 
                   jogo[f].itens[i].tipo);
            
            /* Ajustando referências locais para bater com a ordem original de valor/peso do seu código */
            // Se in.txt inverteu, as variáveis capturam conforme seu sscanf: valor em %f, peso em %f
            
            /* Define a razão base de custo-benefício se o peso for válido */
            if(jogo[f].itens[i].peso > 0) {
                jogo[f].itens[i].razao = jogo[f].itens[i].valor / jogo[f].itens[i].peso;
            }
            jogo[f].qtd_items++;
        }
    }
    /* Retorna por referência a quantidade real de fases lidas no arquivo */
    *total_fases = f + 1; 
}

int main(int argc, char *argv[]) {
    /* Validação obrigatória dos argumentos passados via terminal */
    if(argc < 3) {
        printf("Erro: Parametros de linha de comando ausentes.\n");
        printf("Uso: %s <caminho_entrada.txt> <caminho_saida.txt>\n", argv[0]);
        return 1;
    }

    char *in = argv[1];
    char *out = argv[2];

    /* Tentativa de abertura do descritor de entrada para leitura */
    FILE *fp_in = fopen(in, "r");
    if(fp_in == NULL) {
        printf("Erro ao abrir arquivo de entrada: verifique se '%s' existe.\n", in);
        return 1;
    }
    
    /* Tentativa de criação/abertura do descritor de saída para gravação */
    FILE *fp_out = fopen(out, "w");
    if(fp_out == NULL) {
        printf("Erro ao criar arquivo de saida no caminho indicado.\n");
        fclose(fp_in);
        return 1;
    }

    printf("Arquivos de I/O definidos com sucesso.\nLendo de: %s -> Gravando em: %s\n", in, out);

    Fase jogo[4];
    int total_fases = 0;
    float lucro_total_jornada = 0.0;

    /* Executa o carregamento dos dados estruturados na memória */
    carregar_dados(fp_in, jogo, &total_fases);
    fclose(fp_in); /* Fecha o descritor de leitura imediatamente após o uso */

    /* LOOP PRINCIPAL: Processa cada fase individualmente e de forma sequencial */
    for(int i = 0; i < total_fases; i++) {
        
        /* 1. Aplica modificadores de valor em conformidade com as regras (regras.c) */
        aplicar_regras(&jogo[i]);
        
        /* 2. Ordena os itens da fase de maneira decrescente pelo custo-benefício (mochila.c) */
        ordenar_itens(jogo[i].itens, jogo[i].qtd_items);
        
        /* 3. Preenche a mochila de forma gulosa e gera os outputs no arquivo (mochila.c) */
        preencher_mochila(&jogo[i], fp_out, &lucro_total_jornada);
    }

    /* Emite o balanço final da receita gerada em toda a aventura */
    fprintf(fp_out, "LUCRO TOTAL ACUMULADO: R$ %.2f\n", lucro_total_jornada);
    fclose(fp_out);

    printf("Processamento concluido com sucesso!\n");
    return 0;
}