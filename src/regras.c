#include <string.h>
#include "utils/utils_mochila.h"

void aplicar_regras(Fase *fase) {
    
    /* REGRA 1: Itens mágicos possuem seu valor comercial dobrado */
    if(strcmp(fase->regra, "MAGICOS_VALOR_DOBRADO") == 0) {
        for(int i = 0; i < fase->qtd_items; i++) {
            if(strcmp(fase->itens[i].tipo, "magico") == 0) {
                fase->itens[i].valor *= 2;
                /* Recalcula a razão com base no novo valor atualizado */
                fase->itens[i].razao = fase->itens[i].valor / fase->itens[i].peso;
            }
        }
    }
    /* REGRA 3: Itens de sobrevivência perdem 20% do seu valor original */
    else if(strcmp(fase->regra, "SOBREVIVENCIA_DESVALORIZADA") == 0) {
        for(int i = 0; i < fase->qtd_items; i++) {
            if(strcmp(fase->itens[i].tipo, "sobrevivencia") == 0) {
                fase->itens[i].valor *= 0.80; /* Deduz 20% do valor de face */
                /* Recalcula a razão com base no novo valor depreciado */
                fase->itens[i].razao = fase->itens[i].valor / fase->itens[i].peso;
            }
        }
    }

    /* As Regras 2 (TECNOLOGICOS_INTEIROS) e 4 (TRES_MELHORES_VALOR_PESO)
       modificam a mecânica de seleção estrutural, portanto, suas diretrizes 
       são processadas nativamente dentro do motor de decisão em ./utils/mochila.c.
    */
}