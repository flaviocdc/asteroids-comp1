#include <allegro.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "configuration.h"
#include "stars.h"

char* descricaoGeral[NUM_TECLAS] = { 
	"Mover p/ Direita" , "Mover p/ Esquerda", "Mover p/ Cima",
	"Mover p/ Baixo", "Atirar", "Escudo", "Mostrar ajuda",
	"Sair da partida", "Pausar", "Despausar"
};

void editarTeclas(BITMAP *buffer, CONFIG *config, ESTRELA *estrelas)
{
	int val, scancode, i, j, rep;
	char ascii;
	TECLA tecla;
	
	rep = 0;
	
	for (i = 0; i < NUM_TECLAS; i++)
	{	
		clear_keybuf();
				
		while (TRUE)
		{
			clear(buffer);
			
			movimentaEstrelas(estrelas);
			desenhaEstrelas(buffer, estrelas);
			
			textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2-50, makecol(255,255,255), -1,
				"Tecla para: %s", descricaoGeral[i]);
				
			if (rep)
			{
				textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2-30, makecol(255,0,0), -1,
					"Tecla repetida!");			
			}
		
			if (keypressed())
			{
				val = readkey();
				ascii = val & 0xff;
				scancode = val >> 8;

				descricaoParaTecla(tecla.desc, scancode, ascii);
				tecla.ascii=ascii;
				tecla.scancode=scancode;
				tecla.val = val;
				
				rep = 0;
				
				for (j = 0; j < i; j++)
				{	
					// verificando tecla repetida
					if (config->teclas[j].val == tecla.val)
					{
						rep = 1;
						break;
					}
				}
				
				if (!rep)				
				{
					// salvar tecla somente se nao for repetida
					config->teclas[i] = tecla;
					break;
				}
			}
			else
			{
				rest(10);
			}
			
			draw_sprite(screen, buffer, 0, 0);
		}
	}
	
	salvarConfiguracao(config);
}

void mostrarConfig(BITMAP *buffer, CONFIG *config, ESTRELA *estrelas)
{
	int i;
	TECLA tecla;
	
	PONTO p1, p2, pl;
	p1.x = RES_X/2-200;
	p1.y = RES_Y/2-200;
	p2.x = RES_X/2+200;
	p2.y = RES_Y/2+130;
	pl.x = RES_X/2-185;
	pl.y = RES_Y/2-170;
	
	clear_keybuf();
	
	while (TRUE)
	{
		if (key[KEY_ESC])
			break;
			
			
		if (key[KEY_E])
			editarTeclas(buffer, config, estrelas);
		
		clear(buffer);
		
		movimentaEstrelas(estrelas);
		desenhaEstrelas(buffer, estrelas);
	
		rectfill(buffer, p1.x, p1.y, p2.x, p2.y, makecol(255,0,0));
		rectfill(buffer, p1.x+5, p1.y+5, p2.x-5, p2.y-5, makecol(255,255,255));
		
		for (i = 0; i < NUM_TECLAS; i++)
		{
			tecla = config->teclas[i];
			textprintf_ex(buffer, font, pl.x, pl.y+i*30, makecol(0,0,0), -1, "%20s => %15s", descricaoGeral[i], tecla.desc);
		}
		
		textprintf_centre_ex(buffer, font, RES_X/2, p2.y + 40, makecol(255,255,255), -1,
			"Pressione ESC para sair ou 'E' para editar as configuracoes");
		
		draw_sprite(screen, buffer, 0, 0);
		
		rest(10);		
	}
}


void descricaoParaTecla(char desc[50], int scancode, int ascii)
{
	memset(desc, '\0', 50); 

	if (ascii >= 33 && ascii <= 126)
	{
		desc[0] = ascii;
		return;
	}
			
	switch (scancode)
	{
		case 59 : strcpy(desc, "ESC"); break;
		case 64 : strcpy(desc, "TAB"); break;
		case 67 : strcpy(desc, "Enter"); break;
		case 75 : strcpy(desc, "Espaço"); break;
		case 76 : strcpy(desc, "Insert"); break;
		case 77 : strcpy(desc, "Delete"); break;
		case 78 : strcpy(desc, "Home"); break;
		case 79 : strcpy(desc, "End"); break;
		case 80 : strcpy(desc, "Page-up"); break;			
		case 81 : strcpy(desc, "Page-down"); break;
		case 82 : strcpy(desc, "Seta-Esquerda"); break;
		case 83 : strcpy(desc, "Seta-Direita"); break;			
		case 84 : strcpy(desc, "Seta-Cima"); break;
		case 85 : strcpy(desc, "Seta-Baixo"); break;
		default : strcpy(desc, "Desconhecido"); break;
	}
}

void carregarConfiguracao(CONFIG *config)
{
	int i, val;
	TECLA tecla;	
	FILE *fd;
	
	fd = fopen("data/keyboard.dat", "r");
	i = 0;

	if (fd == NULL)
	{
		puts("Impossivel carregar as configuracoes, saindo...");
		exit(1);
	}

	fscanf(fd, "%d", &val);	
	while (!feof(fd) && i < NUM_TECLAS)
	{
		tecla.scancode =  val >> 8;
		tecla.ascii = val & 0xff;
		tecla.val = val;
		descricaoParaTecla(tecla.desc, tecla.scancode, tecla.ascii);
	
		config->teclas[i] = tecla;
		
		i++;
		fscanf(fd, "%d", &val);
	}
	
	fclose(fd);	
}

void salvarConfiguracao(CONFIG *config)
{
	FILE *fd;
	TECLA tecla;
	int i;
	
	fd = fopen("data/keyboard.dat", "w");

	if (fd == NULL)
	{
		puts("Impossivel salvar as configuracoes, saindo...");
		exit(1);
	}
	
	for (i = 0; i < NUM_TECLAS; i++)
	{
		tecla = config->teclas[i];
		fprintf(fd, "%d \n", tecla.val);
	}
	
	fclose(fd);
}
