#ifndef INC_ASTEROIDS_H
#define INC_ASTEROIDS_H

#define AST_X 64
#define AST_Y 64
#define AST_NUM 64

typedef struct
{
	int x, y; 	// posicao
	int vel; 	// velocidade
	int imgIndex; 	// indice da imagem
	int refresh; 	// "refresh rate" da imagem
} ASTEROIDE;

#include <allegro.h>

#include "main.h"
#include "nave.h"

void desenhaAsteroides(BITMAP *buffer, ASTEROIDE *asteroids);
void atualizarAsteroides(ASTEROIDE *asteroids);
void carregarSpritesAsteroide(void);
void gerarAsteroides(NAVE *nave, ASTEROIDE *asteroids);

PONTO pegarCentroAsteroide(ASTEROIDE *roid);

#endif
