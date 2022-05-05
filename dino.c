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

void printDino(int* dino, int ox, int oy)
{
    int addx = 0, addy = 0, valk;
    for (addx = 0; addx < 24; addx++){
        for (addy = 0; addy < 22; addy++){
            valk = dino[addx * 22 + addy];
            if (valk == 1){
                oled_pix(addy + ox, addx + oy, PX_ON);
            }
        }
    }
}

void printCacto(int* cacto, int ox){
    int addx = 0, addy = 0, valk;
    if (ox < 0){
        addx = -ox;
    }
    for (addx = 0; addx < 16; addx++){
        for (addy = 0; addy < 9; addy++){
            valk = cacto[addx * 9 + addy];
            if (valk == 1){
                oled_pix(addy + ox, addx + 25, PX_ON);
            }
        }
    }
}
