#include "matriz.h"
int main(void){
    int ordemMatriz, quantidadeMinas;
    perguntaDificuldade(&ordemMatriz, &quantidadeMinas);

    int **matrizBomba = (int**) calloc(ordemMatriz, sizeof(int*));
    char **matrizVisivel = (char**) malloc(ordemMatriz * sizeof(char*));

    if(matrizBomba == NULL || matrizVisivel == NULL){
        printf("Memoria insuficiente :( \n)");
        exit(1);
    }
    
    alocaMatrizes(ordemMatriz, matrizBomba, matrizVisivel);

    sorteiaMinas(ordemMatriz, quantidadeMinas, matrizBomba);

    inicializaMatrizVisivel(ordemMatriz, matrizVisivel);

    jogar(ordemMatriz, matrizVisivel, matrizBomba);

    imprimeMatrizBomba(ordemMatriz, matrizBomba);

    liberaMemoria(ordemMatriz, matrizBomba, matrizVisivel);

    return 0;
}