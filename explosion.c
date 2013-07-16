#include <allegro.h>
#include <stdio.h>

#include "explosion.h"
#include "main.h"

int contExplosao = 0;
BITMAP *spritesExplosao[5];

void inicializarExplosoes(EXPLOSAO *explosoes)
{
	EXPLOSAO *e;
	int i = 0;
	
	for (i = 0; i < NUM_CIRC; i++)
	{
		e = (explosoes + i);
		zerarExplosao(e);
	}

}

void criarExplosao(EXPLOSAO *explosoes, int x, int y)
{
	EXPLOSAO *e;
	e = (explosoes + contExplosao);
	
	e->x = x;
	e->y = y;
	e->status = 1;
	
	contExplosao++;
	if (contExplosao > NUM_CIRC)
		contExplosao = 0;
}

void atualizarExplosoes(EXPLOSAO *explosoes)
{
	int i, fakeIndex;
	EXPLOSAO *e;
	
	for (i = 0; i < NUM_CIRC; i++)
	{
		e = (explosoes + i);
		
		if (e->status == 0)
		{	
			continue;
		}
		
		e->imgIndex += 1;
		
		fakeIndex = (e->imgIndex % 100) / 5;
		
		if (fakeIndex == 5) {
			zerarExplosao(e);
		}
	}
}

void desenhaExplosoes(BITMAP *buffer, EXPLOSAO *explosoes)
{
	int i, index;
	EXPLOSAO *e;
	
	for (i = 0; i < NUM_CIRC; i++)
	{
		e = (explosoes + i);
		
		if (e->status == 0)
			continue;
			
		index = (e->imgIndex % 100) / 5;
		draw_sprite(buffer, spritesExplosao[index], e->x, e->y);	
	}
}

void carregarSpritesExplosao(void)
{
	spritesExplosao[0] = carregaImagem("imgs/explosion1.bmp");
	spritesExplosao[1] = carregaImagem("imgs/explosion2.bmp");
	spritesExplosao[2] = carregaImagem("imgs/explosion3.bmp");
	spritesExplosao[3] = carregaImagem("imgs/explosion4.bmp");
	spritesExplosao[4] = carregaImagem("imgs/explosion5.bmp");
}

void zerarExplosao(EXPLOSAO *e)
{	
	e->x = 0;
	e->y = 0;
	e->imgIndex = 0;
	e->status = 0;
}
