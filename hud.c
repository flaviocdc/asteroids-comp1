#include <allegro.h>

#include "hud.h"
#include "main.h"
#include "nave.h"

void desenhaHud(BITMAP* buffer, NAVE* nave, int tempo)
{
	double pFuel, pEscudo;
	
	pFuel = ((double) (100 * nave->fuel)) / nave->maxFuel;
	pEscudo = ((double) (100 * nave->escudo)) / nave->maxEscudo;	
	
	rectfill(buffer, 0, 0, HUD_W, HUD_H, makecol(255,255,255));
	rectfill(buffer, 3, 3, HUD_W-3, HUD_H-3, makecol(0,0,0));
	
	textprintf_centre_ex(buffer, font, HUD_W/2, HUD_H/2, makecol(255,255,255), -1,
		"Tempo: %3d / Vidas: %2d / Combustível: %3.1f%% / Escudo: %3.1f%% / Pontos: %6d",
		tempo, nave->vidas, pFuel, pEscudo, nave->pontos);
}
