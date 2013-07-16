#ifndef INC_OPCOES_H
#define INC_OPCOES_H

#include <allegro.h>

#include "main.h"
#include "stars.h"

#define NUM_ITENS 4
#define OPCOES_GAP 10

#define CODE_PLAY 0
#define CODE_CONFIG 1
#define CODE_RECORDS 2
#define CODE_EXIT 3

typedef struct
{
	char *text;
	PONTO p1, p2;
	int code;
} OPCAO;

typedef struct
{
	OPCAO itens[NUM_ITENS];
	int w, h, x, y;
} OPCOES;

void inicializaMenu(OPCOES *menu);
void desenhaMenu(BITMAP *buffer, OPCOES *menu, int selected);
int abrirMenu(BITMAP *buffer, OPCOES *menu, ESTRELA *estrelas);
int selecionarItemTeclado(OPCOES *menu, int *selected, int *keyCount);

#endif
