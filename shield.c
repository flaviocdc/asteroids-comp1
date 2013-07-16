#include <allegro.h>
#include <stdio.h>

#include "shield.h"
#include "nave.h"
#include "asteroids.h"
#include "main.h"
#include "matematica.h"
#include "explosion.h"

BITMAP *spriteEscudo;

void verificaColisaoEscudo(NAVE *nave, ASTEROIDE *asteroids, EXPLOSAO *explosoes)
{
	int i, j, dist;
	PONTO p, centroRoid, centroNave, coordsEscudo[4];	
	ASTEROIDE *roid;
	
	if (!nave->usandoEscudo)
		return;
	
	centroNave = pegarCentroNave(nave);	
	coordenadasEscudo(centroNave.x, centroNave.y, coordsEscudo);
	
	for (i = 0; i < NUM_CIRC; i++)
	{
		roid = (asteroids + i);
		centroRoid = pegarCentroAsteroide(roid);
		
		for (j = 0; j < 4; j++)
		{
			p = coordsEscudo[j];
			dist = distanciaPontos(p.x, centroRoid.x, p.y, centroRoid.y);
			
			if (dist <= AST_X/2)
			{
				criarExplosao(explosoes, roid->x, roid->y);
			
				roid->x = RES_X+RAIO;
				roid->y = rand() % RES_Y;
				nave->pontos += PONTOS_ROID/4;
				nave->escudo -= 7;
				
				if (nave->escudo < 0)
					nave->escudo = 0;
				
				break;
			}
		}
	}
}

void coordenadasEscudo(int a, int b, PONTO *pts){
	a += NAVE_X/2;
	b += 5;
	
	pts[0].x = a;
	pts[0].y = b - ESCUDO_H/2;
	
	pts[1].x = a;
	pts[1].y = b + ESCUDO_H/2;
	
	pts[2].x = a + ESCUDO_W;
	pts[2].y = b - ESCUDO_H/2;

	pts[3].x = a + ESCUDO_W;
	pts[3].y = b + ESCUDO_H/2;
}

void desenhaEscudo(BITMAP* buffer, NAVE* nave)
{
	if (!nave->usandoEscudo)
		return; // nao preciso desenhar.

	PONTO centroNave, cEscudo[4];
	centroNave = pegarCentroNave(nave);
	coordenadasEscudo(centroNave.x, centroNave.y, cEscudo);
	
	draw_sprite(buffer, spriteEscudo, cEscudo[0].x, cEscudo[0].y);
			
	//rectfill(buffer, cEscudo[0].x, cEscudo[0].y, cEscudo[3].x, cEscudo[3].y, makecol(255,255,255));
}

void carregarSpriteEscudo(void) {
	spriteEscudo = carregaImagem("imgs/shield.bmp");
}
