#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.c"

/* 
   Solicita a escolha de dificuldade do jogador. Com base na dificuldade selecionada, define o tamanho do campo de jogo 
   e a quantidade de bombas. 'ordemMatriz' representa o número de linhas e colunas das matrizes, enquanto 'quantidadeMinas' 
   define o número de bombas que o campo de jogo terá.
*/
void perguntaDificuldade(int *ordemMatriz, int *quantidadeMinas);

/*
   Aloca dinamicamente duas matrizes (uma de inteiros e outra de caracteres) com dimensões definidas por 'ordemMatriz'. 
   'matrizBomba' será a matriz de inteiros para armazenar a posição das minas, e 'matrizVisivel' será a matriz de jogo 
   exibida no terminal.
*/
void alocaMatrizes(int ordemMatriz, int **matrizBomba, char **matrizVisivel);

/*
   Inicializa todos os elementos da matriz de caracteres (matrizVisivel) com o símbolo 'X', indicando células fechadas. 
   'ordemMatriz' define o número de linhas e colunas da matriz.
*/
void inicializaMatrizVisivel(int ordemMatriz, char **matrizVisivel);

/*
   Distribui aleatoriamente minas na 'matrizCampo' com base no número de bombas ('quantidadeBombas') definido pela função 
   'perguntaDificuldade'. 'ordemMatriz' define o tamanho da matriz, com -1 representando uma mina e 0 uma célula vazia. 
   Usa 'srand()', 'rand()' e 'time()' para garantir a aleatoriedade.
*/
void sorteiaMinas(int ordemMatriz, int quantidadeBombas, int **matrizCampo);

/*
   Verifica se uma coordenada especificada (linha e coluna) está dentro dos limites da matriz. 'ordemMatriz' define o 
   tamanho da matriz, 'linha' e 'coluna' representam as coordenadas que serão verificadas. Retorna 1 se a coordenada é válida e 
   0 caso seja inválida.
*/
int verificaCoordenadaValida(int ordemMatriz, int linha, int coluna);

/*
   Retorna o número de minas ao redor de uma célula específica na matriz. 'linha' e 'coluna' são as coordenadas da célula, 
   'ordemMatriz' define o tamanho da matriz, e 'matrizBomba' é a matriz de jogo onde -1 representa uma mina. Usa 
   'verificaCoordenadaValida' para garantir que as coordenadas ao redor estejam dentro dos limites.
*/
int quantidadeBombasVizinhanca(int linha, int coluna, int ordemMatriz, int **matrizBomba);

/*
   Imprime a matriz de jogo visível ('matrizVisivel') no terminal, exibindo o estado atual do campo de jogo para o jogador. 
   'ordemMatriz' define o número de linhas e colunas da matriz.
*/
void imprimeMatrizVisivel(int ordemMatriz, char **matrizVisivel);

/*
   Verifica se o jogador ganhou ou perdeu o jogo. Conta o número de células não abertas ('X') na 'matrizVisivel' e compara 
   com as células que contêm minas em 'matrizBomba'. Retorna o número de células fechadas.
*/
int verificaVitoriaDerrota(int ordemMatriz, char **matrizVisivel, int **matrizBomba);

/*
   Abre uma célula específica e, se não houver minas ao redor, expande automaticamente para abrir as células vizinhas, 
   recursivamente, até que a vizinhança tenha minas. 'linha' e 'coluna' são as coordenadas a abrir, 'matrizVisivel' é a 
   matriz exibida no jogo, e 'matrizBomba' é a matriz que contém as minas. Verifica as coordenadas vizinhas com 
   'verificaCoordenadaValida'.
*/
void expandirCoordenada(int linha, int coluna, int ordemMatriz, char **matrizVisivel, int **matrizBomba);

/*
   Controla o fluxo principal do jogo, processando as coordenadas de cada jogada, atualizando a matriz visível e verificando 
   a condição de vitória ou derrota. 'ordemMatriz' define o tamanho da matriz, 'matrizVisivel' é a matriz de jogo exibida, 
   e 'matrizBomba' contém as minas.
*/
void jogar(int ordemMatriz, char **matrizVisivel, int **matrizBomba);

/*
   Exibe a matriz de bombas no terminal, mostrando -1 para células com minas e o número de minas nas vizinhanças das células 
   sem minas. Essa função auxilia no debug ou no final do jogo.
*/
void imprimeMatrizBomba(int ordemMatriz, int **matrizBomba);

/*
   Libera a memória alocada para as matrizes 'matrizBomba' e 'matrizVisivel' após o término do jogo, prevenindo vazamentos de memória.
*/
void liberaMemoria(int ordemMatriz, int **matrizBomba, char **matrizVisivel);

