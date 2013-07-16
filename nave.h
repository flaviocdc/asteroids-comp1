#ifndef INC_NAVE_H
#define INC_NAVE_H

#define NAVE_X 64
#define NAVE_Y 64
#define NAVE_NUM 4

#define ESCUDO_H NAVE_Y
#define ESCUDO_W 10

typedef struct
{
	int x, y; 	// posicao
	int vel; 	// velocidade
	unsigned int imgIndex; 	// indice da imagem
	int vidas; 	// vidas
	int status; 	// define se a nave está invulneravel ou nao
	int tiros, maxTiros; 	// quantidade de tiros "ativos"
	int fuel, maxFuel;
	int escudo, maxEscudo, usandoEscudo;
	int pontos;
} NAVE;

#include <allegro.h>

#include "asteroids.h"

void desenhaNave(BITMAP *buffer, NAVE *nave);
void atualizarNave(NAVE *nave);
void gerarNave(NAVE *nave);
void teletransporte(NAVE *nave, ASTEROIDE *asteroids);
void carregarSpritesNave(void);

PONTO pegarCentroNave(NAVE *nave);

int verificaCombustivel(NAVE *nave);

#endif
