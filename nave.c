#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>

#include "nave.h"
#include "main.h"
#include "asteroids.h"
#include "matematica.h"

BITMAP *naveSprites[NAVE_NUM];

void desenhaNave(BITMAP *buffer, NAVE *nave)
{
	int index;
	index = (nave->imgIndex % 16) / 4;
	draw_sprite(buffer, naveSprites[index], nave->x, nave->y);
}

void atualizarNave(NAVE *nave)
{
	nave->imgIndex++;
}

void gerarNave(NAVE *nave)
{
	nave->x = NAVE_X / 2;
	nave->y = RES_Y / 2;
	nave->vel = VELOCIDADE;
	nave->status = 0;
	nave->tiros = 0;
	nave->maxTiros = MAX_TIROS;
	nave->fuel = (RES_Y * RES_X) / 100;
	nave->maxFuel = (RES_Y * RES_X) / 100;
	nave->escudo = 100;
	nave->maxEscudo = 100;
	nave->usandoEscudo = 0;
	nave->imgIndex = 0;
	nave->vidas = VIDAS;
	nave->pontos = 0;
}

void teletransporte(NAVE *nave, ASTEROIDE *asteroids)
{
	PONTO centroNave;

	while (TRUE)
	{
		nave->x = rand() % RES_X;
		nave->y = rand() % RES_Y;

		centroNave.x = nave->x + NAVE_X/2;
		centroNave.y = nave->y + NAVE_Y/2;

		/* Nova posicao do circulo controlado somente e valida caso esteja
		 * dentro da tela e nao esteja sobre um circulo aleatorio */
		if ((centroNave.x > RAIO && centroNave.x < RES_X - RAIO) &&
				(centroNave.y > RAIO && centroNave.y < RES_Y - RAIO) &&
				verificaDistancia(centroNave.x, centroNave.y, asteroids))
			break;
	}
}

void carregarSpritesNave(void)
{
	BITMAP *temp;
	char *imgsPath[4];
	imgsPath[0] = "imgs/nave1.bmp";
	imgsPath[1] = "imgs/nave2.bmp";
	imgsPath[2] = "imgs/nave3.bmp";
	imgsPath[3] = "imgs/nave4.bmp";
	
	int i;
	for (i = 0; i < NAVE_NUM; i++)
	{
		temp = carregaImagem(imgsPath[i]);
		naveSprites[i] = temp;
	}
}

PONTO pegarCentroNave(NAVE *nave)
{
	PONTO p;
	p.x = nave->x + NAVE_X/2;
	p.y = nave->y + NAVE_Y/2 - 5;
	return p;
}

int verificaCombustivel(NAVE *nave)
{
	return nave->fuel > 0;
}
