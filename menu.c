#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>

#include "menu.h"
#include "main.h"

void inicializaMenu(OPCOES *menu)
{
	int i, h;
	
	PONTO p1, p2;

	menu->itens[0].text = "I n i c i a r";
	menu->itens[1].text = "C o n f i g u r a ç ã o";
	menu->itens[2].text = "R e c o r d e s";
	menu->itens[3].text = "S a i r";
		
	menu->w = RES_X/4;
	menu->h = RES_Y/20; 
	
	menu->x = RES_X/2;
	menu->y = RES_Y/2 -200;
		
	p1.x = menu->x - menu->w/2;
	p2.x = menu->x + menu->w/2;
	h = menu->y;
		
	for (i = 0; i < NUM_ITENS; i++)
	{
		h += menu->h;
		p1.y = h;
		p2.y = h + menu->h;
		h += OPCOES_GAP;
				
		menu->itens[i].p1 = p1;
		menu->itens[i].p2 = p2;
		menu->itens[i].code = i;
	}
}

void desenhaMenu(BITMAP *buffer, OPCOES *menu, int selected)
{	
	int i, ym, cor;
	PONTO p1, p2;
	OPCAO op;
		
	for (i = 0; i < NUM_ITENS; i++)
	{
		op = menu->itens[i];
		p1 = op.p1; p2 = op.p2;
	
		if (selected == i)
			cor = makecol(255,0,0);
		else
			cor = makecol(255,255,255);
			
	
		rectfill(buffer, p1.x, p1.y, p2.x, p2.y, cor);
		rectfill(buffer, p1.x+5, p1.y+5, p2.x-5, p2.y-5, makecol(0,0,0));
		
		ym = (p1.y + p2.y) / 2;
				
		textprintf_centre_ex(buffer, font, menu->x, ym, makecol(255,255,255), -1, "%s", menu->itens[i].text);
	}
}

int abrirMenu(BITMAP *buffer, OPCOES *menu, ESTRELA *estrelas)
{
	int selected, code, keyCount;
	selected = 0, code = -1;
		
	inicializaMenu(menu);
	
	while(code == -1)
	{
		clear(buffer);		
		
		desenhaEstrelas(buffer, estrelas);
		desenhaMenu(buffer, menu, selected);
		movimentaEstrelas(estrelas);
		
		code = selecionarItemTeclado(menu, &selected, &keyCount);
	
		draw_sprite(screen, buffer, 0, 0);	
		rest(10);	
	}
	
	return code;
}

int selecionarItemTeclado(OPCOES *menu, int *selected, int *keyCount)
{
	clear_keybuf();

	if (key[KEY_UP] && *keyCount == 0 && *selected != 0)
	{	
		*keyCount += 1;
		*selected -= 1;
	}	
	if (key[KEY_DOWN] && *keyCount == 0 && *selected < NUM_ITENS-1)
	{
		*keyCount += 1;
		*selected += 1;
	}
	
	if (!key[KEY_UP] && !key[KEY_DOWN])
		*keyCount = 0;
		
	if (key[KEY_ENTER])
	{
		return menu->itens[*selected].code;
	}
		
	return -1;
}
