#ifndef INC_SHOTS_H
#define INC_SHOTS_H

#include <allegro.h>

#include "main.h"
#include "nave.h"
#include "explosion.h"

/**
 * Estrutura que define um tiro.
 */
typedef struct
{
	int x, y;
	/// Velocidade do tiro.
	int vel;
	/**
	 * Status do tiro.
	 * 1 significa que o tiro deve ser desenhado, pois está ativo.
	 * 0 significa que o tiro não deve ser desenhado.
	 */
	int status;
	/// Referencia para o BITMAP.
	BITMAP *img;
} TIRO;

/**
 * Inicializa os tiros com valores padrão.
 * @param tiros um vetor de TIRO.
 */
void inicializaTiros(TIRO *tiros);

/**
 * Funcao chamada para gerar um tiro na tela.
 * @param tiros um vetor de TIRO.
 * @param nave um referencia a nave.
 * @param i "slot" que o tiro ocupara.
 */
void gerarTiros (TIRO *tiros, NAVE *nave, int i);

/**
 * Desenha o tiros na tela.
 * @param buffer
 * @param tiros um vetor de TIRO.
 */
void desenhaTiros (BITMAP *buffer, TIRO *tiros);

/**
 * Movimenta os tiros e verifica se eles colidem com algum asteroide.
 * @param tiros um vetor de TIRO.
 * @param asteroids um vetor de ASTEROIDE para que a verificacao de colisao seja possivel.
 */
void movimentaTiros (TIRO *tiros, ASTEROIDE *asteroids, NAVE *nave, EXPLOSAO *explosoes);

/**
 * Funcao secundaria. Ajuda na verificacao de colisao.
 */
void verificaColisaoRoid(TIRO *tiro, ASTEROIDE *asteroids, NAVE *nave, EXPLOSAO *explosoes);

/**
 * @return o centro do tiro baseado em sua coordenadas x e y.
 */
PONTO pegarCentroTiro(TIRO *tiro);

#endif
