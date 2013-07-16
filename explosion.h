#ifndef INC_EXPLOSION_H
#define INC_EXPLOSION_H

#include <allegro.h>

typedef struct
{
	int x, y, status;
	unsigned int imgIndex;
} EXPLOSAO;

void inicializarExplosoes(EXPLOSAO *explosoes);
void criarExplosao(EXPLOSAO *explosoes, int x, int y);
void atualizarExplosoes(EXPLOSAO *explosoes);
void desenhaExplosoes(BITMAP *buffer, EXPLOSAO *explosoes);
void zerarExplosao(EXPLOSAO *e);
void carregarSpritesExplosao(void);

#endif
