#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "jogo.h"
#include "matematica.h"
#include "stars.h"
#include "shots.h"
#include "asteroids.h"
#include "hud.h"
#include "shield.h"
#include "records.h"
#include "configuration.h"

volatile unsigned int ctrlFps = 0;
volatile unsigned int tempo = 0;

void jogo(BITMAP *buffer, CONFIG *config, ASTEROIDE *asteroids, EXPLOSAO *explosoes, NAVE *nave, TIRO *tiros, ESTRELA *estrelas)
{
	inicializaTimer();
	
	TECLA *teclas = config->teclas;

	int noFuel = 0;

	/* Variavel para evitar multiplos tiros seguidos */
	int contador = 0;

	/* Variável para controlar movimentacao dos tiros */
	int i = 0;
	
	/* Indica em qual estagio do jogo o jogador está */
	int stage = 1;
	
	/* Controle de tiro */
	TIRO *tiro;
	int tirosNaTela = 0, j;
	
	/* Centro da nave */
	PONTO centroNave;

	/* Comecando a jogar. Laco e satisfeito enquanto ESC nao for pressionado
	 * e nave nao colida com nenhum outro circulo */
	do
	{
		if (ctrlFps % 2 == 0)
		{
			rest(1);
			continue;
		}

		clear(buffer);

		centroNave = pegarCentroNave(nave);
	
		movimentaEstrelas(estrelas);
		atualizarAsteroides(asteroids);
		atualizarExplosoes(explosoes);
		atualizarNave(nave);
		movimentaTiros(tiros, asteroids, nave, explosoes);
		verificaColisaoEscudo(nave, asteroids, explosoes);
		
		desenhaEstrelas(buffer, estrelas);
		desenhaAsteroides(buffer, asteroids);
		desenhaNave(buffer, nave);		
		desenhaTiros(buffer, tiros);
		desenhaHud(buffer, nave, tempo);
		desenhaEscudo(buffer, nave);
		desenhaExplosoes(buffer, explosoes);
		
		if (noFuel)
		{
			textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2, makecol(255,0,0), -1, "S e m  C o m b u s t i v e l !");
			textprintf_centre_ex(buffer, font, RES_X/2+2, RES_Y/2+2, makecol(255,255,255), -1, "S e m  C o m b u s t i v e l !");
		}
		
		
		if (tempo < 3 && stage > 1)
		{
			textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2, makecol(255,0,0), -1, "Avancando para o estagio %d", stage);
			textprintf_centre_ex(buffer, font, RES_X/2+2, RES_Y/2+2, makecol(255,255,255), -1, "Avancando para o estagio %d", stage);
			textprintf_centre_ex(buffer, font, RES_X/2+20, RES_Y/2+20, makecol(255,0,0), -1, "Recarregam combustivel e escudo...");
			textprintf_centre_ex(buffer, font, RES_X/2+22, RES_Y/2+22, makecol(255,255,255), -1, "Recarregam combustivel e escudo...");
		}
		
		/* "Colando" 'buffer' sobre 'screen' */
		draw_sprite(screen, buffer, 0, 0);

		/* Verifica se a nave está colidindo. */
		if (!verificaDistancia(centroNave.x, centroNave.y, asteroids))
		{
			teletransporte(nave, asteroids);
			nave->vidas--;
			nave->pontos -= PONTOS_MORTE;
		}
		
		if (key[teclas[DEFESA].scancode] && nave->escudo > 0)
			nave->usandoEscudo = 1;
		else
			nave->usandoEscudo = 0;
		
		/* Atirando */
		if (key[teclas[ATAQUE].scancode] && !key[teclas[DEFESA].scancode] && contador == 0)
		{
			contador++;
			
			tirosNaTela = 0;
			for (j = 0; j < MAX_TIROS; j++)
			{
				tiro = (tiros + j);
				tirosNaTela += tiro->status;
			}
			
			if (tirosNaTela == MAX_TIROS)
				continue;
			
			if (i == MAX_TIROS)
				i = 0;
			gerarTiros(tiros, nave, i);
			i++;
		} 
		if (!key[teclas[ATAQUE].scancode]) {
			contador = 0;
		}
		
		/* A Nave não possui combustível, impossível se mecher */
		if (!verificaCombustivel(nave))
		{
			noFuel = 1;
			continue;
		}
		
		/* A nave so anda caso seja pressionada uma das setas,
		 * nao seja mandado para fora da tela e nenhuma das teclas de controle
		 * seja mantida pressionada */
		if (key[teclas[DIREITA].scancode] && nave->x < RES_X - RAIO)
		{
			nave->x += PASSO;
			nave->fuel--;
			continue;
		}
		if (key[teclas[ESQUERDA].scancode] && nave->x > RAIO-30)
		{
			nave->x -= PASSO;
			nave->fuel--;
			continue;
		}		
		if (key[teclas[CIMA].scancode] && nave->y > RAIO)
		{
			nave->y -= PASSO;
			nave->fuel--;
			continue;
		}
		if (key[teclas[BAIXO].scancode] && nave->y < RES_Y - RAIO)
		{
			nave->y += PASSO;
			nave->fuel--;
			continue;
		}
		if (key[teclas[PAUSE].scancode])
		{
			pauseGame(buffer, config);
		}
		
		
		if (tempo == DURACAO)
		{
			tempo = 0;
			stage++;
			
			nave->maxFuel = nave->maxFuel/stage;
			nave->fuel = nave->maxFuel;
			nave->escudo = nave->maxEscudo;
		}
		
	} while (!key[teclas[SAIR].scancode] && nave->vidas >= 0);
}

/* Funcao para imprimir Game over na tela quando o jogo terminar */
void gameOver(BITMAP *buffer, NAVE *nave, RECORDE *records)
{		
	/* verifica se o jogador obteve um recorde */
	adicionarRecorde(buffer, records, nave->pontos);		
	
	if (nave->vidas >= 0)
		/* Nao aconteceu um 'game over' */
		return;
	
	/* Gameover screen */
	clear_to_color(buffer, makecol(0, 0, 0));
	textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2, makecol(255,0,0), -1, "G a m e o v e r !");
	textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2 + 10, makecol(255,0,0), -1, "Pressione ESC para sair");
	draw_sprite(screen, buffer, 0, 0);

	/* Sair do gameover somente quando pressionar 'ESC' */
	while (!key[KEY_ESC])
		rest(10);
}

/* Funcao para imprimir Game over na tela quando o jogo terminar */
void pauseGame(BITMAP *buffer, CONFIG *config)
{
	/* Pause screen */
	textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2, makecol(255,0,0), -1, "P a u s a d o");
	textprintf_centre_ex(buffer, font, RES_X/2+2, RES_Y/2+2, makecol(255,255,255), -1, "P a u s a d o");
	draw_sprite(screen, buffer, 0, 0);

	/* Sair do gameover somente quando pressionar 'ESC' */
	while (!key[config->teclas[RECOMECA].scancode])
		rest(10);
}

/* Funcao para controlar a taxa de FPS */
void controleFps (void)
{
	ctrlFps++;
}
END_OF_FUNCTION(controleFps);

void controleTempo(void)
{
	tempo++;
}
END_OF_FUNCTION(controleTempo);

void inicializaTimer(void)
{
	/* Controlando FPS */
	LOCK_VARIABLE(ctrlFps);
	LOCK_FUNCTION(controleFps);
	install_int_ex(controleFps, BPS_TO_TIMER(60));
	
	LOCK_VARIABLE(tempo);
	LOCK_FUNCTION(controleTempo);
	install_int_ex(controleTempo, BPS_TO_TIMER(1));
}
