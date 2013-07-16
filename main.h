#ifndef INC_MAIN_H
#define INC_MAIN_H

/// Número de cores
#define CORES 32
/// Resolucao horizontal da tela
#define RES_X 1024
/// Resolucao vertical da tela
#define RES_Y 768

#define RAIO 32
#define PASSO 1
#define VELOCIDADE 4
/// Numero maximo de asteroides
#define NUM_CIRC 10
/// Numero maximo padrao de tiros
#define MAX_TIROS 4
/// Numero padrao de vidas
#define VIDAS 3

/// Numero de estrelas a serem desenhadas
#define NUM_ESTRELAS 100
/// Velocidade das estrelas
#define VEL_ESTRELAS 1

/// Qtde de pontos ganha por cada roid destruido
#define PONTOS_ROID 100
/// Qtde de pontos perdidos a cada morte
#define PONTOS_MORTE 200

/// Duracao de uma partida
#define DURACAO 45

/**
 * Estrutura que define um ponto.
 */
typedef struct
{
	int x, y;
} PONTO;

/**
 * Inicia o alegro
 */
void inicia (void);

/**
 * Carrega uma imagem encerrando o programa se houver um erro.
 * @param path caminho da imagem a ser carregada.
 */
BITMAP* carregaImagem(char* path);

/**
 * Funcao usada para carregar os sprites dos asteroides.
 */
BITMAP* grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame);

#endif
