#include <allegro.h>
#include <stdlib.h>

#include "stars.h"
#include "main.h"

void gerarEstrelas(ESTRELA *estrelas)
{
	int i;
	for (i = 0; i < NUM_ESTRELAS; i++)	
	{
		ESTRELA* e = (estrelas + i);
		e->x = rand() % RES_X;
		e->y = rand() % RES_Y;
	}	
}

void desenhaEstrelas(BITMAP *buffer, ESTRELA *estrelas)
{
	int i;
	for (i = 0; i < NUM_ESTRELAS; i++)
	{
		ESTRELA* e = (estrelas + i);
		putpixel(buffer, e->x, e->y, makecol(189,189,189));
	}
}

void movimentaEstrelas(ESTRELA *estrelas)
{
	int i;
	for (i = 0; i < NUM_ESTRELAS; i++)
	{
		ESTRELA* e = (estrelas + i);
		e->x -= VELOCIDADE;
		if (e->x < 0)
		{
			e->x = RES_X;
			e->y = rand() % RES_Y;
		}
	}
}
	

