#include <allegro.h>
#include <stdlib.h>

#include "shots.h"
#include "main.h"
#include "nave.h"
#include "asteroids.h"
#include "matematica.h"
#include "explosion.h"

void gerarTiros (TIRO *tiros, NAVE *nave, int i)
{
	PONTO centroNave;
	centroNave = pegarCentroNave(nave);

	TIRO *tiro = (tiros + i);

	tiro->x = centroNave.x + NAVE_X/2;
	tiro->y = centroNave.y;
	tiro->vel = (rand() % VELOCIDADE) + PASSO + 1;
	tiro->status = 1;
}

void desenhaTiros (BITMAP *buffer, TIRO *tiros)
{
	int i;
	TIRO *tiro;

	for (i = 0; i < MAX_TIROS; i++)
	{
		tiro = (tiros + i);

		/* O tiro saiu da tela, nao preciso processa-lo */
		if (!tiro->status)
			continue;
		/* O tiro esta na tela, processe-o */
		else
			draw_sprite(buffer, tiro->img, tiro->x, tiro->y);
	}
}
void movimentaTiros (TIRO *tiros, ASTEROIDE *asteroids, NAVE *nave, EXPLOSAO *explosoes)
{
	int i;
	TIRO *tiro;

	for (i = 0; i < MAX_TIROS; i++)
	{
		tiro = (tiros + i);
		
		if (!tiro->status)
			continue;
			
		verificaColisaoRoid(tiro, asteroids, nave, explosoes);	

		/* O tiro vai sair da tela, nao preciso processa-lo */
		if (tiro->x > RES_X + tiro->img->w)
			tiro->status = 0;
		/* O tiro esta na tela, processe-o */
		else
			tiro->x += tiro->vel;
	}
}

void verificaColisaoRoid(TIRO *tiro, ASTEROIDE *asteroids, NAVE *nave, EXPLOSAO *explosoes)
{
	ASTEROIDE *roid;
	
	PONTO centroTiro, centroRoid;
	centroTiro = pegarCentroTiro(tiro);
	
	int i, dist;
	for (i = 0; i < NUM_CIRC; i++)
	{
		roid = (asteroids + i);
		centroRoid = pegarCentroAsteroide(roid);
		
		dist = distanciaPontos(centroTiro.x, centroRoid.x, centroTiro.y, centroRoid.y);
		
		if (dist <= tiro->img->w + AST_X/2)
		{
			criarExplosao(explosoes, roid->x ,roid->y);
			
			tiro->status = 0;
			roid->x = RES_X+RAIO;
			roid->y = rand() % RES_Y;
			nave->pontos += PONTOS_ROID;
			
			
		}
	}
}

void inicializaTiros(TIRO *tiros)
{
	int i;
	TIRO *tiro;
	
	BITMAP *tiroImg;
	tiroImg = carregaImagem("imgs/tiro.bmp");

	for (i = 0; i < MAX_TIROS; i++)
	{
		tiro = (tiros + i);
		tiro->img = tiroImg;
		tiro->status = 0;
	}
}

PONTO pegarCentroTiro(TIRO *tiro)
{
	PONTO p;
	p.x = tiro->x + tiro->img->w/2;
	p.y = tiro->y + tiro->img->h/2;
	return p;
}
