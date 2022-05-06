/*
 * dino.h
 *
 *  Created on: 4 de mai de 2022
 *      Author: eduar
 */

#ifndef DINO_H_
#define DINO_H_

unsigned int printDino(int* dino, int ox, int oy, unsigned int ocupado);
unsigned int printCacto(int* cacto, int ox);
void apagaCacto(int* cacto, int ox);
void printTelaInicio(int* dino, int*cacto);
void printTelaFim(int* dino, int*cacto, unsigned int max_pont);
void printScore(int pontuacao);

#endif /* DINO_H_ */
