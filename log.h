#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.c"

FILE* criarLog();
FILE* abrirLog();
void registraCoordenadasMatrizes(int ordemMatriz, int linha, int coluna, char **matrizVisivel);
void registraMatrizBomba(int ordemMatriz, int **matrizBomba);

