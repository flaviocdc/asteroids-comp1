#ifndef INC_HUD_H
#define INC_HUD_H

#include <allegro.h>

#include "main.h"
#include "nave.h"

#define HUD_H 30
#define HUD_W RES_X

void desenhaHud(BITMAP* buffer, NAVE* nave, int tempo);

#endif
