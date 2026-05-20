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
/*
FASE 1 — Floresta Encantada ----------------------------------------
Capacidade da mochila: 5.0 kg
Regra especial: Todos os itens mágicos têm o valor dobrado.

FASE 2 — Ruínas Perdidas -------------------------------------------
Capacidade da mochila: 4.0 kg
Regra especial: Itens tecnológicos não podem ser fracionados.

FASE 3 — Montanhas Geladas -----------------------------------------
Capacidade da mochila: 3.5 kg
Regra especial: Itens de sobrevivência perdem 20% do valor original.

FASE 4 — Templo Subterrâneo ----------------------------------------
Capacidade da mochila: 6.0 kg
Regra especial: Apenas os três itens com maior valor/peso podem ser escolhidos.
*/

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