#ifndef INC_STARS_H
#define INC_STARS_H

#include <allegro.h>

///Estrutura que define um estrela.
typedef struct
{
	int x, y;
} ESTRELA;

/**
 * Gera estrelas em posicoes aleatorias da tela.
 * @param estrelas um vetor de ESTRELA.
 */
void gerarEstrelas(ESTRELA* estrelas);

/**
 * Desenha as estrelas na tela.
 * @param buffer
 * @param estrelas um vetor de ESTRELA.
 */
void desenhaEstrelas(BITMAP* buffer, ESTRELA* estrelas);

/**
 * Movimentas as estrelas.
 * @param estrelas um vetor de ESTRELA.
 */
void movimentaEstrelas(ESTRELA *estrelas);

#endif
