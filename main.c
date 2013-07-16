/* 
 * Programa: Aerolitius
 * Versao: 0.02
 * Autor: Felipe Ribeiro Granja, Flavio Coutinho Costa, Edimar Babilon Santos
 * Data: 29/10/2007
 */

#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "jogo.h"
#include "stars.h"
#include "shots.h"
#include "asteroids.h"
#include "nave.h"
#include "menu.h"
#include "records.h"
#include "configuration.h"
#include "shield.h"
#include "explosion.h"
 
int main (void)
{
	/* Iniciado gerador de numeros aleatorios */
	srand(time(NULL));

	/* Iniciando o Allegro */
	inicia();
	
	/* Alocando memoria para os circulos */
	NAVE *nave;
	TIRO *tiros;
	ESTRELA *estrelas;
	ASTEROIDE *asteroids;
	EXPLOSAO *explosoes;
	OPCOES *menu;
	RECORDE *records;
	CONFIG *config;
		
	asteroids = (ASTEROIDE *) malloc(NUM_CIRC * sizeof(ASTEROIDE));
	explosoes = (EXPLOSAO *) malloc(NUM_CIRC * sizeof(EXPLOSAO));
	nave = (NAVE *) malloc(sizeof(NAVE));
	tiros = (TIRO *) malloc(MAX_TIROS * sizeof(TIRO));
	estrelas = (ESTRELA *) malloc(NUM_ESTRELAS * sizeof(ESTRELA));
	menu = (OPCOES *) malloc(sizeof(OPCOES));
	records = (RECORDE *) malloc(MAX_RECORDS * sizeof(RECORDE));
	config = (CONFIG *) malloc(sizeof(CONFIG));
		
	if (!asteroids || !nave || !tiros || !estrelas || !menu || !records || !config || !explosoes)
	{
		puts("Falha durante a alocacao de memoria");
		return 1;
	}
	
	/* Carregandp Sprites */
	carregarSpritesAsteroide();
	carregarSpritesNave();
	carregarSpriteEscudo();
	carregarSpritesExplosao();
	
	/* Criando o buffer */
	BITMAP *buffer;	
	buffer = create_bitmap(RES_X, RES_Y);

	/* Criando entidades */
	gerarEstrelas(estrelas);
	inicializarExplosoes(explosoes);
	inicializaRecordes(records);
	carregarConfiguracao(config);
	
	/* Loop principal */
	int code;	
	while (TRUE)
	{
		if (key[KEY_ENTER])
		{
			rest(10);
			continue;
		}
	
		code = abrirMenu(buffer, menu, estrelas);
		
		if (code == CODE_PLAY)
		{
			/* iniciando dados para uma nova partida */
			inicializaTiros(tiros);
			gerarNave(nave);
			gerarAsteroides(nave, asteroids);
			
			jogo(buffer, config, asteroids, explosoes, nave, tiros, estrelas);	
			gameOver(buffer, nave, records);
			code = -1;
		}
		
		if (code == CODE_RECORDS)
		{
			mostrarRecordes(buffer, records, estrelas);
			code = -1;
		}
		
		if (code == CODE_CONFIG)
		{
			mostrarConfig(buffer, config, estrelas);
			code = -1;		
		}
		
		if (code == CODE_EXIT)
		{
			break;
		}
		
		rest(10);
	}
	
	/* Descarregando Allegro */
	allegro_exit();
	
	/* Liberando memória */
	free(asteroids);
	free(nave);
	free(tiros);
	free(estrelas);
	free(menu);
	free(records);
	free(config);
	free(explosoes);
	
	return 0;
}
END_OF_MAIN();

/* Funcao para ajustar configuracoes de hardware e inicio da Allegro */
void inicia (void)
{
	/* Tentando iniciar Allegro */
	allegro_init();

	/* Instalando teclado e video */
	install_keyboard();
	set_color_depth(CORES);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, RES_X, RES_Y, 0, 0);
	clear_to_color(screen, makecol(0, 0, 0));
}

BITMAP *carregaImagem(char* path)
{
	BITMAP *img;
	img = load_bitmap(path, NULL);
	if (!img)
	{
		printf("Falha ao carregar imagem: %s\n", path);
		exit(1);
	}
	
	return img;
}

BITMAP *grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame)
{
	BITMAP *temp = create_bitmap(width, height);

	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;

	blit(source, temp, x, y, 0, 0, width, height);

	return temp;
}
