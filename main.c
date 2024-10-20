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

//essa funcao inicializa a minha matriz de char com 'X'
void inicializaMatrizVisivel(int ordemMatriz, char **matrizVisivel) {
    for (int contL = 0; contL < ordemMatriz; contL++) {
        for (int contC = 0; contC < ordemMatriz; contC++) {
            matrizVisivel[contL][contC] = 'X'; // Inicializa todas as células como se estivessem fechadas
        }
    }
}
//função que retorna a matriz, mas com um numero N de bombas
void sorteiaMinas(int tamanhoCampo, int quantidadeBombas, int **matrizCampo){

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
}

//funcao que verifica a validez de uma coordenada
int verificaCoordenadaValida(int ordemMatriz, int linha, int coluna){
    int ehValido;
    if(linha >= 0 && linha < ordemMatriz && coluna >= 0 && coluna < ordemMatriz){
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

//essa função é responsável por mostrar a matriz que será impressa no terminal
void imprimeMatrizVisivel(int ordemMatriz, char **matrizVisivel) {

    printf("   ");
    for (int cont = 1; cont <= ordemMatriz; cont++) {
        printf("%02d |", cont);
    }
    printf("\n   ");

    for (int cont = 0; cont < ordemMatriz; cont++) {
        printf("----");
    }
    printf("\n");

    for (int contL = 0; contL < ordemMatriz; contL++) {
        printf("%02d| ", contL + 1); // Índice da linha
        for (int contC = 0; contC < ordemMatriz; contC++) {
                printf("%c | ", matrizVisivel[contL][contC]);
        }
        printf("\n");
    }
}

//essa funcao eh responsavel por verificar se o user ganhou ou perdeu
int verificaVitoriaDerrota(int ordemMatriz, char **matrizVisivel, int **matrizBomba){
    int quantidadeX = 0; //quantidade de "nao bombas" que ainda nao foram selecionadas

    for(int contLinha = 0; contLinha < ordemMatriz; contLinha++){
        for(int contColuna = 0; contColuna < ordemMatriz; contColuna++){
            if(matrizVisivel[contLinha][contColuna] == 'X' && matrizBomba[contLinha][contColuna] == 0){
                quantidadeX++;
            }
        }
    }
    return quantidadeX;
}

//este metodo é responsavel por escanerar as coordenadas durante o jogo
void jogar(int ordemMatriz, char **matrizVisivel, int **matrizBomba) {
    int coordenadaLinha, coordenadaColuna;

    do {
        imprimeMatrizVisivel(ordemMatriz, matrizVisivel);

        do {
            printf("Digite a coordenada da linha e em seguida a coordenada da coluna: \n");
            scanf("%d %d", &coordenadaLinha, &coordenadaColuna);
            coordenadaLinha--;  // Ajusta para o índice da matriz bomba
            coordenadaColuna--; // Ajusta para o índice da matriz bomba

            if (verificaCoordenadaValida(ordemMatriz, coordenadaLinha, coordenadaColuna) == 0) {
                printf("Coordenada invalida! As coordenadas precisam estar entre o intervalo de 1 a %d ;) \n", ordemMatriz);
            }

            if (matrizVisivel[coordenadaLinha][coordenadaColuna] != 'X') { // Se a coordenada já foi revelada
                printf("Essa coordenada ja foi digitada! Tente outro par de coordenadas ;) \n");
            }

        } while (verificaCoordenadaValida(ordemMatriz, coordenadaLinha, coordenadaColuna) == 0 && matrizVisivel[coordenadaLinha][coordenadaColuna] != 'X');

        matrizVisivel[coordenadaLinha][coordenadaColuna] = '0' + quantidadeBombasVizinhanca(coordenadaLinha, coordenadaColuna, ordemMatriz, matrizBomba);

    } while (verificaVitoriaDerrota(ordemMatriz, matrizVisivel, matrizBomba) != 0 && matrizBomba[coordenadaLinha][coordenadaColuna] == 0);

    if(matrizBomba[coordenadaLinha][coordenadaColuna] == 0){
        printf("parabens, vc eh fera\n");
    }
    else{
        printf("game over");
    }
}

void imprimeMatrizBomba(int ordemMatriz, int **matrizBomba){
    printf("Aqui esta a matriz original, -1 representa as bombas! \n");

    printf("   ");
    for (int cont = 1; cont <= ordemMatriz; cont++) {
        printf("%02d |", cont);
    }
    printf("\n   ");

    for (int cont = 0; cont < ordemMatriz; cont++) {
        printf("----");
    }
    printf("\n");

    for (int contL = 0; contL < ordemMatriz; contL++) {
        printf("%02d| ", contL + 1); // Índice da linha
        for (int contC = 0; contC < ordemMatriz; contC++) {
                printf("%d | ", matrizBomba[contL][contC]);
        }
        printf("\n");
    }
}

int main(void){
    int ordemMatriz, quantidadeMinas;
    perguntaDificuldade(&ordemMatriz, &quantidadeMinas);

    int **matrizBomba = (int**) calloc(ordemMatriz, sizeof(int*));
    char **matrizVisivel = (char**) malloc(ordemMatriz * sizeof(char*));
    if(matrizBomba == NULL){
        printf("Memoria insuficiente :( \n)");
        exit(1);
    }
    if(matrizVisivel == NULL){
        printf("Memoria insuficiente :( \n)");
        exit(1);
    }

    for(int cont = 0; cont < ordemMatriz; cont++){
        matrizBomba[cont] = (int*) calloc(ordemMatriz, sizeof(int));
        matrizVisivel[cont] = (char*) malloc(ordemMatriz * sizeof(char));
    }

    sorteiaMinas(ordemMatriz, quantidadeMinas, matrizBomba);
    inicializaMatrizVisivel(ordemMatriz, matrizVisivel);

    jogar(ordemMatriz, matrizVisivel, matrizBomba);

    imprimeMatrizBomba(ordemMatriz, matrizBomba);

    for(int cont = 0; cont < ordemMatriz; cont++){
        free(matrizBomba[cont]);
        free(matrizVisivel[cont]);
    }
    free(matrizBomba);
    free(matrizVisivel);

    return 0;
}