#ifndef INC_JOGO_H
#define INC_JOGO_H

#include <allegro.h>

#include "main.h"
#include "stars.h"
#include "shots.h"
#include "asteroids.h"
#include "records.h"
#include "explosion.h"
#include "configuration.h"

void jogo(BITMAP *buffer, CONFIG *config, ASTEROIDE *asteroids, EXPLOSAO *explosoes, NAVE *nave, TIRO *tiros, ESTRELA *estrelas);
	
void gameOver(BITMAP *buffer, NAVE *nave, RECORDE *records);
void pauseGame(BITMAP *buffer, CONFIG *config);

void inicializaTimer(void);
void controleFps(void);
void controleTempo(void);

#endif
