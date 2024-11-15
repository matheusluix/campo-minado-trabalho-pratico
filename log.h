#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.c"


/* Essa função cria o arquivo de log e o abre para escrita. Retorna um ponteiro para o arquivo aberto. */
FILE* criarLog();

/* Essa função abre o arquivo de log existente para adicionar dados. Retorna um ponteiro para o arquivo aberto. */
FILE* abrirLog();

/* Função responsável pela impressão da matriz visível no arquivo de log. Recebe o ponteiro para o arquivo de log, o tamanho da matriz e a matriz visível. */
void imprimirMatriz(FILE *log, int ordemMatriz, char **matrizVisivel);

/*  Função que registra coordenadas inválidas no arquivo de log, como coordenadas negativas, extremamente grandes ou coordenadas nulas. 
    Recebe o ponteiro para o arquivo de log, as coordenadas e o tamanho da matriz. */
void registrarCoordenadaInvalida(FILE *log, int linha, int coluna, int ordemMatriz);

/* Função que registra a tentativa de coordenada já digitada no arquivo de log. Recebe o ponteiro para o arquivo de log e as coordenadas da tentativa. */
void registrarCoordenadaJaDigitada(FILE *log, int linha, int coluna);

/* Função que registra as coordenadas no arquivo de log e imprime a matriz detalhada. Recebe o tamanho da matriz, as coordenadas e a matriz visível. */
void registraCoordenadasMatrizes(int ordemMatriz, int linha, int coluna, char **matrizVisivel);

/*  Função que registra a matriz de bombas no arquivo de log, -1 representa as coordenadas com bombas, outras coordenadas mostram o número de bombas que há ao redor. 
    Recebe o tamanho da matriz e a matriz de bombas. */
void registraMatrizBomba(int ordemMatriz, int **matrizBomba);
