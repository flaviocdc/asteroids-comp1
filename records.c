#include <allegro.h>
#include <stdio.h>
#include <string.h>

#include "records.h"
#include "main.h"
#include "stars.h"

void adicionarRecorde(BITMAP *buffer, RECORDE *records, int pts)
{	
	RECORDE *r, temp1, temp2;
	int i, add;
	char name[NAME_LEN];
	
	add = 0;
	memset(name, '\0', NAME_LEN);
	memset(temp1.name, '\0', NAME_LEN);
	memset(temp2.name, '\0', NAME_LEN);
	
	for (i = 0; i < MAX_RECORDS; i++)
	{
		r = (records + i);
		if (pts >= r->pontos)
		{
			// ok, adicionar o novo recorde na posicao 'i'
			add = 1;
			break;
		}
	}
	
	if (!add)
	{
		return;
	}

	strcpy(temp1.name, r->name);
	temp1.pontos = r->pontos;
	
	lerNomeRecorde(buffer, name);
	
	strcpy(r->name, name);
	r->pontos = pts;	

	// comecar de onde paramos			
	for (i += 1; i < MAX_RECORDS; i++)
	{
		r = (records + i);
		strcpy(temp2.name,r->name);
		temp2.pontos = r->pontos;
			
		strcpy(r->name,temp1.name);
		r->pontos = temp1.pontos;
		
		temp1 = temp2;
	}
	
	salvarRecordes(records);
}

void salvarRecordes(RECORDE *records)
{
	FILE *fd;
	RECORDE *r;	
	int i;
	
	fd = fopen("data/records.dat", "w");
	if (fd == NULL)
	{
		puts("Impossivel carregar os recordes, saindo...");
		exit(1);
	}
	
	for (i = 0; i < MAX_RECORDS; i++)
	{
		r = (records + i);
		fprintf(fd, "%s %d\n", r->name, r->pontos);
	}
	
	fclose(fd);
}

void mostrarRecordes(BITMAP *buffer, RECORDE *records, ESTRELA *estrelas)
{	
	while (!key[KEY_ESC])
	{
		clear(buffer);
		
		desenhaEstrelas(buffer, estrelas);
		desenhaRecordes(buffer, records);
		movimentaEstrelas(estrelas);	
		
		draw_sprite(screen, buffer, 0, 0);
		rest(10);
	}
}

void desenhaRecordes(BITMAP *buffer, RECORDE *records)
{
	RECORDE *r;
	
	int x, y, i;
	x = RES_X/2;
	y = RES_Y/2 -200;
	
	textprintf_centre_ex(buffer, font, x, y-40, makecol(255,255,255), -1, "M e l h o r e s  P o n t u a d o r e s");
	
	for (i = 0; i < MAX_RECORDS; i++)
	{
		r = (records + i);
		rect(buffer, x-TAM_COLUNA_W, y, x-TAM_COLUNA_W-35, y+TAM_COLUNA_H, makecol(255,0,0));
		rect(buffer, x, y, x-TAM_COLUNA_W, y+TAM_COLUNA_H, makecol(255,0,0));		
		rect(buffer, x, y, x+TAM_COLUNA_W, y+TAM_COLUNA_H, makecol(255,0,0));
		
		textprintf_centre_ex(buffer, font, x-TAM_COLUNA_W-17, y+(TAM_COLUNA_H/2), makecol(255,255,255), -1, "%d", i+1);
		textprintf_centre_ex(buffer, font, x-(TAM_COLUNA_W/2), y+(TAM_COLUNA_H/2), makecol(255,255,255), -1, "%s", r->name);
		textprintf_centre_ex(buffer, font, x+(TAM_COLUNA_W/2), y+(TAM_COLUNA_H/2), makecol(255,255,255), -1, "%d", r->pontos);
		
		y += TAM_COLUNA_H;
	}
	
	textprintf_centre_ex(buffer, font, x, y+40, makecol(255,255,255), -1, "P r e s s i o n e  E S C  p /  S a i r");
}

void inicializaRecordes(RECORDE *records)
{
	FILE *fd;
	RECORDE *r;
	char name[NAME_LEN];
	int pts, i;

	for (i = 0; i < MAX_RECORDS; i++)
	{
		r = (records + i);	
		memset(r->name, '\0', NAME_LEN);
	}

	i = 0;
	
	fd = fopen("data/records.dat", "r");
	
	if (fd == NULL)
	{
		puts("Impossivel carregar os recordes, saindo...");
		exit(1);
	}
	
	memset(name, '\0', NAME_LEN);
	fscanf(fd, "%s %d", name, &pts);
	while (!feof(fd) && i < MAX_RECORDS)
	{
		r = (records + i);
		strcpy(r->name, name);
		r->pontos = pts;
		
		memset(name, '\0', NAME_LEN);
		fscanf(fd, "%s %d", name, &pts);			
		i++;	
	}
	
	fclose(fd);
}

void lerNomeRecorde(BITMAP *buffer, char result[NAME_LEN])
{
	int val, scancode, i;
	char name[NAME_LEN], ascii;
	
	memset(name, '\0', NAME_LEN);	
	strcpy(name, "None");
	i = strlen(name)-1;
	
	clear_keybuf();

	do
	{
		clear(buffer);
		textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2, makecol(255,255,255), -1, "Entre com o nome do recordista:");
		
		if (keypressed() && i < NAME_LEN)
		{
			val = readkey();
			ascii = val & 0xff;
			scancode = val >> 8;
			
			if (scancode == KEY_BACKSPACE)
			{
				if (i > 0) i--;
				name[i] = '\0';
				continue;
			}
						
			if (ascii >= 33 && ascii <= 126)
			{
				name[i] = ascii;
				i++;				
			}			
		}
		
		textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2+30, makecol(0,0,200), -1, "%s", name);

		if (i == 50)
		{
			textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2+60, makecol(255,0,0), -1, 
				"Limite de caracteres atingido!");
		}

		textprintf_centre_ex(buffer, font, RES_X/2, RES_Y/2+90, makecol(255,255,255), -1, "Pressione ENTER para concluir...");
		draw_sprite(screen, buffer, 0, 0);
		
		rest(10);
	} while (!key[KEY_ENTER]);

	if (strlen(name) == 0)
	{	
		// jogador nao especificou o nome
		strcpy(name, "None");	
	}
	
	strcpy(result, name);
}
