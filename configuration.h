#ifndef INC_CONFIGURATION_H
#define INC_CONFIGURATION_H

#define DIREITA 0
#define ESQUERDA 1
#define CIMA 2
#define BAIXO 3
#define ATAQUE 4
#define DEFESA 5
#define AJUDA 6
#define SAIR 7
#define PAUSE 8
#define RECOMECA 9

#define NUM_TECLAS 10

#include <allegro.h>

#include "stars.h"

typedef struct
{
	char desc[50];
	int val;
	int scancode;
	int ascii;
} TECLA;

typedef struct
{
	TECLA teclas[NUM_TECLAS];
} CONFIG;

void descricaoParaTecla(char desc[50], int scancode, int ascii);
void carregarConfiguracao(CONFIG *config);
void salvarConfiguracao(CONFIG *config);
void mostrarConfig(BITMAP *buffer, CONFIG *config, ESTRELA *estrelas);
void editarTeclas(BITMAP *buffer, CONFIG *config, ESTRELA *estrelas);

#endif
