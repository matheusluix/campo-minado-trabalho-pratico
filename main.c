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

    int coordenadaX, coordenadaY;

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
int quantidadeBombasVizinhanca(int linha, int coluna, int ordemMatriz, int **matrizBomba){

    int totalBombasVizinhaca = 0;

    if(verificaCoordenadaValida(ordemMatriz, linha - 1, coluna)){ //verifica se a coordenada superior é valida
        if(matrizBomba[linha-1][coluna] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna)){   //verifica se a coordenada inferior é valida
        if(matrizBomba[linha+1][coluna] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha, coluna-1)){   //verifica se a coordenada esquerda é valida
        if(matrizBomba[linha][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha, coluna+1)){   //verifica se a coordenada direita é valida
        if(matrizBomba[linha][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha-1, coluna-1)){ //verifica se a coordenada noroeste é valida
        if(matrizBomba[linha-1][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha-1, coluna+1)){ //verifica se a coordenada nordeste é valida
        if(matrizBomba[linha-1][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna-1)){ //verifica se a coordenada sudoeste é valida
        if(matrizBomba[linha+1][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna+1)){ //verifica se a coordenada sudeste é valida
        if(matrizBomba[linha+1][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }
    return totalBombasVizinhaca;
}

//funcao que conta as bombas vizinhas
void contarBombasVizinhas(int ordemMatriz, int **matrizBombas, char **matrizVisivel){
    for(int contL = 0; contL < ordemMatriz; contL++){
        for(int contC = 0; contC < ordemMatriz; contC++){
            if(matrizBombas[contL][contC] != -1){
                int bombasVizinhas = quantidadeBombasVizinhanca(contL, contC, ordemMatriz, matrizBombas);
                matrizVisivel[contL][contC] = '0' + bombasVizinhas;
            }
        }
    }
}
void imprimeMatrizVisivel(int ordemMatriz, char **matrizVisivel) {
    for (int contL = 0; contL < ordemMatriz; contL++) {
        for (int contC = 0; contC < ordemMatriz; contC++) {
            if (matrizVisivel[contL][contC] == 'X') {
                printf(" X "); // Célula ainda fechada
            } else {
                printf(" %c ", matrizVisivel[contL][contC]); // Imprime o número de bombas vizinhas
            }
        }
        printf("\n");
    }
}

char **inicializaMatrizVisivel(int ordemMatriz, char **matriz) {
    for (int contL = 0; contL < ordemMatriz; contL++) {
        for (int contC = 0; contC < ordemMatriz; contC++) {
            matriz[contL][contC] = 'X'; // Inicializa todas as células como fechadas
        }
    }
    return matriz;
}

void selecionarCoordenada(int *coordenadaX, int *coordenadaY) {
    printf("Escolha uma coordenada (linha coluna): ");
    scanf("%d %d", coordenadaX, coordenadaY);
}

int main(void){
    int ordemMatriz, quantidadeMinas;
    perguntaDificuldade(&ordemMatriz, &quantidadeMinas);

    int **matrizBombas = (int**) calloc(ordemMatriz, sizeof(int*));
    char **matrizVisivel = (char**) malloc(ordemMatriz * sizeof(char*));



    for(int cont = 0; cont < ordemMatriz; cont++){
        matrizBombas[cont] = calloc(ordemMatriz, sizeof(int));
        matrizVisivel[cont] = malloc(ordemMatriz * sizeof(char));
    }

    matrizBombas = sorteiaMinas(ordemMatriz, quantidadeMinas, matrizBombas);
    matrizVisivel = inicializaMatrizVisivel(ordemMatriz, matrizVisivel);
    contarBombasVizinhas(ordemMatriz, matrizBombas, matrizVisivel);

    imprimeMatrizVisivel(ordemMatriz, matrizVisivel);

    
    for(int cont = 0; cont < ordemMatriz; cont++){
        free(matrizBombas[cont]);
        free(matrizVisivel[cont]);
    }
    free(matrizBombas);
    free(matrizVisivel);

    return 0;
}