#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void perguntaDificuldade(int *ordemMatriz, int *quantidadeMinas){

    printf("Ola caro jogador, selecione uma dificuldade para iniciarmos o jogo!\n");
    printf("Aperte 'f' para facil, 'm' para medio ou 'd' para dificil:\n");

    char selecaoDificuldade;
    scanf(" %c", &selecaoDificuldade);

    switch (selecaoDificuldade){
    case 'f':
        *ordemMatriz = 10;
        *quantidadeMinas = 3;
        break;
    case 'm':
        *ordemMatriz = 20;
        *quantidadeMinas = 6;
        break;
    case 'd':
        *ordemMatriz = 30;
        *quantidadeMinas = 9;
        break;
    default:
        *ordemMatriz = 20;
        *quantidadeMinas = 6;
        break;
    }
}
//função que retorna a matriz, mas com um numero N de bombas
int** sorteiaMinas(int tamanhoCampo, int quantidadeBombas, int **matrizCampo){

    int coordenadaX;
    int coordenadaY;

    srand(time(NULL)); //mudará o valor da semente a cada segundo
    for(int cont = 0; cont < quantidadeBombas; cont++){
        coordenadaX = rand() % tamanhoCampo; //aqui estamos sorteando uma coordenada randomica para x
        coordenadaY = rand() % tamanhoCampo; //aqui estamos sorteando uma coordenada aleatoria para y
        if(matrizCampo[coordenadaX][coordenadaY] == 0){
            matrizCampo[coordenadaX][coordenadaY] = -1;
        }
        else{
            cont--;
        }
    }

    return matrizCampo;
}

//funcao que verifica a validez de uma coordenada
int verificaCoordenadaValida(int ordemMatriz, int quantidadeLinha, int quantidadeColuna){
    int ehValido;
    if(quantidadeLinha >= 0 && quantidadeLinha < ordemMatriz && quantidadeColuna >= 0 && quantidadeColuna < ordemMatriz){
        ehValido = 1;
    }
    else{
        ehValido = 0;
    }
    return ehValido;
}

//funcao que retorna a quantidade de bombas ao redor da minha coordenada atual
int quantidadeBombasVizinhanca(int linha, int coluna, int ordemMatriz, int **matriz){

    int totalBombasVizinhaca = 0;

    if(verificaCoordenadaValida(ordemMatriz, linha - 1, coluna)){ //verifica se a coordenada superior é valida
        if(matriz[linha-1][coluna] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna)){   //verifica se a coordenada inferior é valida
        if(matriz[linha+1][coluna] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha, coluna-1)){   //verifica se a coordenada esquerda é valida
        if(matriz[linha][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha, coluna+1)){   //verifica se a coordenada direita é valida
        if(matriz[linha][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha-1, coluna-1)){ //verifica se a coordenada noroeste é valida
        if(matriz[linha-1][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha-1, coluna+1)){ //verifica se a coordenada nordeste é valida
        if(matriz[linha-1][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna-1)){ //verifica se a coordenada sudoeste é valida
        if(matriz[linha+1][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna+1)){ //verifica se a coordenada sudeste é valida
        if(matriz[linha+1][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }
    return totalBombasVizinhaca;
}

//funcao que conta as bombas vizinhas
void contarBombasVizinhas(int ordemMatriz, int **matrizOriginal, int **matrizContagem){
    for(int contL = 0; contL < ordemMatriz; contL++){
        for(int contC = 0; contC < ordemMatriz; contC++){
            if (matrizOriginal[contL][contC] != -1) {
                matrizContagem[contL][contC] = 1;
            }
            else{
                matrizContagem[contL][contC] = quantidadeBombasVizinhanca(contL, contC, ordemMatriz, matrizOriginal);
            }
        }
    }
}

//funcao que irá imprimir a matriz original, com 0 e -1
void imprimeMatrizOriginal(int ordemMatriz, int **matriz){
    printf("A matriz geradora original, (-1 representa uma bomba):\n");
    for(int contLinha = 0; contLinha < ordemMatriz; contLinha++){
        for(int contColuna = 0; contColuna < ordemMatriz; contColuna++){
            printf("%d ", matriz[contLinha][contColuna]);
        }
        printf("\n");
    }
}
void imprimeMatrizContadora(int ordemMatriz, int **matriz){

    for(int contL = 0; contL < ordemMatriz; contL++){
        for(int contC = 0; contC < ordemMatriz; contC++){
            printf("%d ", matriz[contL][contC]);
        }
        printf("\n");
    }


}

int main(void){
    int ordemMatriz, quantidadeMinas;
    perguntaDificuldade(&ordemMatriz, &quantidadeMinas);


    //alocando a matriz original que gerará o campo
    int **matrizCampoOriginal = (int**) calloc(ordemMatriz, sizeof(int*));
    if(matrizCampoOriginal == NULL){
        printf("memória insuficiente :(\n");
        exit(1);
    }
    for(int cont = 0; cont < ordemMatriz; cont++){
        matrizCampoOriginal[cont] = (int*) calloc (ordemMatriz, sizeof(int));
        if(matrizCampoOriginal[cont] == NULL){
            printf("memória insuficiente :(\n");
            exit(1);
        }
    }

    //alocando a matriz que tem a quantidade de bombas na vizinhaça
    int **matrizContagem = (int**) calloc(ordemMatriz, sizeof(int*));
    if(matrizContagem == NULL){
        printf("memória insuficiente :(\n");
        exit(1);
    }
    for(int cont = 0; cont < ordemMatriz; cont++){
        matrizContagem[cont] = (int*) calloc(ordemMatriz, sizeof(int));
        if(matrizContagem[cont] == NULL){
            printf("memória insuficiente :(\n");
            exit(1);
        }
    }

    //sorteando minas nos campos
    matrizCampoOriginal = sorteiaMinas(ordemMatriz, quantidadeMinas, matrizCampoOriginal);
    
    contarBombasVizinhas(ordemMatriz, matrizCampoOriginal, matrizContagem);

    imprimeMatrizOriginal(ordemMatriz, matrizCampoOriginal);
    imprimeMatrizContadora(ordemMatriz, matrizContagem);


    for(int contLinha = 0; contLinha < ordemMatriz; contLinha++){
        free(matrizCampoOriginal[contLinha]);
    }
    free(matrizContagem);
    for(int contLinha = 0; contLinha < ordemMatriz; contLinha++){
        free(matrizContagem[contLinha]);
    }
    free(matrizContagem);
    return 0;
}