/*
 * dino.c
 *
 *  Created on: 5 de mai de 2022
 *      Author: eduar
 */

#include <msp430.h>
#include <dino.h>
#include <Defines.h>
#include <Oled.h>
#include "Oled_Letras.h"


unsigned int printDino(int* dino, int ox, int oy, unsigned int ocupado)
{
    int addx = 0, addy = 0, valk;
    for (addy = 0; addy < 17; addy++){
        for (addx = 0; addx < 14; addx++){
            valk = dino[addy * 14 + addx];
            if (valk == 1){
                if (ocupado && oy > 20 ){
                    return 1;
                }
                oled_pix(addx + ox, addy + oy, PX_ON);
            }
        }
    }
    return 0;
}

unsigned int printCacto(int* cacto, int ox){
    int addx = 0, addy = 0, valk, ocupado = 0;
    for (addy = 0; addy < 16; addy++){
        for (addx = 0; addx < 9; addx++){
            valk = cacto[addy * 9 + addx];
            if (valk == 1){
                oled_pix(addx + ox, addy + 35, PX_ON);
                if (ox > 9 && ox < 14)
                    ocupado = 1;
            }
        }
    }
    return ocupado;
}

void apagaCacto(int* cacto, int ox){
    int addx = 0, addy = 0, valk;
    for (addy = 0; addy < 16; addy++){
        for (addx = 0; addx < 9; addx++){
            valk = cacto[addy * 9 + addx];
            if (valk == 1){
                oled_pix(addx + ox, addy + 35, PX_OFF);
            }
        }
    }
}

void printTelaInicio(int* dino, int*cacto){
    oled_buf_apaga();
    int addx = 0, addy = 0, valk;
    for (addy = 0; addy < 17; addy++){
        for (addx = 0; addx < 14; addx++){
            valk = dino[addy * 14 + addx];
            if (valk == 1){
                oled_pix(addx + 27, addy + 30, PX_ON);
            }
        }
    }

    for (addy = 0; addy < 16; addy++){
        for (addx = 0; addx < 9; addx++){
            valk = cacto[addy * 9 + addx];
            if (valk == 1){
                oled_pix(addx + 97, addy + 30, PX_ON);
            }
        }
    }

    oled_frase("T-REX GAME", 45, 4, PX_ON);
    oled_buf_vai();

}

void printTelaFim(int* dino, int*cacto, unsigned int max_pont){
    oled_buf_apaga();
    int addx = 0, addy = 0, valk;
    for (addy = 0; addy < 17; addy++){
        for (addx = 0; addx < 14; addx++){
            valk = dino[addy * 14 + addx];
            if (valk == 1){
                oled_pix(addx + 97, addy + 30, PX_ON);
            }
        }
    }

    for (addy = 0; addy < 16; addy++){
        for (addx = 0; addx < 9; addx++){
            valk = cacto[addy * 9 + addx];
            if (valk == 1){
                oled_pix(addx + 27, addy + 30, PX_ON);
            }
        }
    }

    oled_frase("GAME OVER", 45, 30, PX_ON);

    char num[] = "0123456789";
    char *score[10];
    char score_o[] = "MAX SCORE: XXX";

    score_o[11] = num[max_pont/100];
    score_o[12] = num[(max_pont/10)%10];
    score_o[13] = num[max_pont%10];

    *score = score_o;
    oled_frase(score_o, 38, 4, PX_ON);

    oled_buf_vai();
}

void printScore(int pontuacao){
    char num[] = "0123456789";
    char *score[10];
    char score_o[] = "SCORE: XXX";

    score_o[7] = num[pontuacao/100];
    score_o[8] = num[(pontuacao/10)%10];
    score_o[9] = num[pontuacao%10];

    *score = score_o;
    oled_frase(score_o, 45, 4, PX_ON);
}
