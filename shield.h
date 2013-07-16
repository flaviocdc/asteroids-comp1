#ifndef INC_SHIELD_H
#define INC_SHIELD_H

#include "asteroids.h"
#include "nave.h"
#include "explosion.h"
#include "main.h"

void verificaColisaoEscudo(NAVE *nave, ASTEROIDE *asteroids, EXPLOSAO *explosoes);
void desenhaEscudo(BITMAP* buffer, NAVE* nave);

void coordenadasEscudo(int a, int b, PONTO *pts);
void carregarSpriteEscudo(void);
#endif
