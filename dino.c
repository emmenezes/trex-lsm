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

void apagaMatriz(volatile char* matriz){
    char i,j;
    for (i=0; i<17; i++){
        for (j=1; j<20; j++){
            matriz[i*20 + j]=0;
        }
    }
}
