#include <stdlib.h>
#include <math.h>
#include <allegro.h>

#include "asteroids.h"
#include "main.h"
#include "nave.h"

/* Funcao para calcular a distancia entre 2 pontos (x1, y1) (x2, y2) */
int distanciaPontos (int x1, int x2, int y1, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	return sqrt(dx * dx + dy * dy);
}

/* Funcao que retorna V somente se todos os asteroides nao estiverem
 * tocando na nave */
int verificaDistancia (int a, int b, ASTEROIDE *asteroids)
{
	int i, VF = TRUE;
	ASTEROIDE *roid;
	PONTO centroRoid;

	for (i = 0; i < NUM_CIRC; i++)
	{
		roid = (asteroids + i);
		centroRoid = pegarCentroAsteroide(roid);
		VF = VF && (distanciaPontos(a, centroRoid.x, b, centroRoid.y) > AST_X/2 + NAVE_X/2);
	}

	return VF;
}
