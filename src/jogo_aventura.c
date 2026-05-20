#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/utils_mochila.h"


void data(FILE *fp_in, Fase jogo[], int *total_fases){
    char linha[256];
    int f = -1;


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
            sscanf(linha, "ITEM: %[^,], %f,%f,%s",jogo[f].itens[i].nome,&jogo[f].itens[i].valor,&jogo[f].itens[i].peso,jogo[f].itens[i].tipo);
            jogo[f].qtd_items ++;
        }

    }

}


int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Uso: %s path: <entrada.txt>  path: <saida.txt>\n", argv[0]);
        return 1;
    }

    char *in = argv[1];
    char *out = argv[2];

    FILE *fp_in = fopen(in, "r");
    if(fp_in == NULL){
        printf("Erro ao abrir arquivo de entrada: verifique se %s está correto ou existe\n", argv[1]);
        fclose(fp_in);
        return 1;
    }
    FILE *fp_out = fopen(out, "w");
    if(fp_out == NULL){
        printf("Erro ao criar arquivo de saida\n");
        fclose(fp_out);
        return 1;
    }

    printf("arquivos de I/O definidos: %s e %s", in, out);



    
    fclose(fp_in);
    fclose(fp_out);


    return 0;
}
