#ifndef INC_RECORDS_H
#define INC_RECORDS_H

#define MAX_RECORDS 15
#define TAM_COLUNA_W 150
#define TAM_COLUNA_H 20
#define NAME_LEN 50

#include <allegro.h>

#include "stars.h"

typedef struct
{
	char name[NAME_LEN];
	int pontos;
} RECORDE;

void adicionarRecorde(BITMAP *buffer, RECORDE *records, int pts);
void lerNomeRecorde(BITMAP *buffer, char result[NAME_LEN]);
void mostrarRecordes(BITMAP *buffer, RECORDE *records, ESTRELA *estrelas);
void inicializaRecordes(RECORDE *records);
void salvarRecordes(RECORDE *records);
void desenhaRecordes(BITMAP *buffer, RECORDE *records);
#endif
