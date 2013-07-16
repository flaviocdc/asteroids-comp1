#include <allegro.h>
#include <stdio.h>

#include "asteroids.h"
#include "matematica.h"
#include "main.h"
#include "nave.h"

BITMAP *asteroidsSprites[AST_NUM];

/* Funcao para geracao de dados aleatorias para os asteroides */
void gerarAsteroides(NAVE *nave, ASTEROIDE *asteroids)
{
	int i, x, y;
	ASTEROIDE *roid;

	for (i = 0; i < NUM_CIRC; i++)
	{
		roid = (asteroids + i);

		/* Atribuir novas coordenas a  x e y somente se estes ja nao
		 * tiverem coordenadas validas */
		while (TRUE)
		{
			/* Coordenadas fazem com que os asteroides venham da direita
			 * em um Y(que faz com que eles fiquem totalmente dentro
			 * da tela) aleatório */
			while (TRUE)
			{
				// posicionar o roids na 2a metade da tela
				x = (rand() % RES_X/2) + RES_X/2 + RAIO;
				y = rand() % RES_Y;

				if (y > RAIO && y < RES_Y - RAIO)
					break;
			}

			roid->x = x;
			roid->y = y;
			
			/* Circulos aleatorios nao podem aparecer sobrepondo
			 * circulo controlado */
			if (distanciaPontos(roid->x, nave->x, roid->y,
							nave->y))
				break;
		}

		/* Geracao índice de imagem aleatorio */
		roid->imgIndex = rand() % AST_NUM;
		
		/* Geracao de velocidades aleatorias para os asteroides */
		roid->vel = rand() % VELOCIDADE + 1;
	}
}

void desenhaAsteroides(BITMAP *buffer, ASTEROIDE *asteroids)
{
	int i;
	ASTEROIDE* roid;
	BITMAP* img;

	for (i = 0; i < NUM_CIRC; i++)
	{
		roid = (asteroids + i);
		img = asteroidsSprites[roid->imgIndex];
		
		draw_sprite(buffer, img, roid->x, roid->y);
	}
}

void atualizarAsteroides(ASTEROIDE *asteroids)
{
	int i;
	ASTEROIDE* roid;

	for (i = 0; i < NUM_CIRC; i++)
	{
		roid = (asteroids + i);
		roid->x -= roid->vel;

		/* Caso um circulo aleatorio saia completamente da tela, ele
		 * reaparece do outro lado em um Y aleatorio */
		if (roid->x < 0 - RAIO)
		{
			while (TRUE)
			{
				roid->x = RES_X + RAIO;
				roid->y = rand() % RES_Y;

				/* Coordenadas somente sao validas caso facam com
				 * que os circulos aleatorios fiquem completamente
				 * dentro da tela */
				if ((roid->y > RAIO) && (roid->y < RES_Y - RAIO))
					break;
			}
		}
		
		if (roid->imgIndex == AST_NUM-1)
			roid->imgIndex = 0;
		else
			roid->imgIndex++;
	}
}

void carregarSpritesAsteroide()
{
	BITMAP *temp;
	int i;
	
	//carrega os sprites lendo frames de 64x64.
	temp = carregaImagem("imgs/asteroids.bmp");
	for (i = 0; i < AST_NUM; i++)
	{
		asteroidsSprites[i] = grabframe(temp, AST_X, AST_Y, 0, 0, 8, i);
	}
	destroy_bitmap(temp);
}

PONTO pegarCentroAsteroide(ASTEROIDE *roid)
{
	PONTO p;
	p.x = roid->x + AST_X/2;
	p.y = roid->y + AST_Y/2;
	return p;	
}

