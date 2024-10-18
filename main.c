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

//essa função é responsável por mostrar a matriz que será impressa no terminal
void imprimeMatrizVisivel(int ordemMatriz, char **matrizVisivel, int **matrizBombas) {
    printf("    ");
    for (int cont = 1; cont <= ordemMatriz; cont++) {
        printf("%02d ", cont);
    }
    printf("\n    ");
    for (int cont = 0; cont < ordemMatriz; cont++) {
        printf("---");
    }
    printf("\n");

    for (int contL = 0; contL < ordemMatriz; contL++) {
        printf("%02d |", contL + 1); // Índice da linha
        for (int contC = 0; contC < ordemMatriz; contC++) {
            if (matrizVisivel[contL][contC] == 'A') {
                if (matrizBombas[contL][contC] == -1) {
                    printf(" * ");
                } else {
                    printf(" %c ", matrizVisivel[contL][contC]);
                }
            } else {
                printf(" X ");
            }
        }
        printf("\n");
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
//esta funcao vai mostrar quantas bombas tem ao redor da minha bomba atual
void mostraQuantasBombasTemAoRedor(int ordemMatriz, int linha, int coluna, char ** matrizVisivel, int **matrizBomba){
    if (verificaCoordenadaValida(ordemMatriz, linha, coluna) && matrizVisivel[linha][coluna] == 'X') {
        matrizVisivel[linha][coluna] = quantidadeBombasVizinhanca(linha, coluna, ordemMatriz, matrizBomba) + '0';
    }
}

//este metodo é responsavel por escanerar as coordenadas durante o jogo
void jogar(int ordemMatriz, char **matrizVisivel){
    int coordenadaLinha, coordenadaColuna;

    do{
        printf("Digite a coordenada da linha e em seguida a coordenada da coluna: \n");
        scanf("%d %d", &coordenadaLinha, &coordenadaColuna);
        coordenadaLinha--;
        coordenadaColuna--;
        if(verificaCoordenadaValida(ordemMatriz, coordenadaLinha, coordenadaColuna) == 0){
            printf("Coordenada invalida, as coordenadas precisam estar entre o intervalo de 1 a %d ;) \n", ordemMatriz);
        }
        else if (matrizVisivel[coordenadaLinha][coordenadaColuna] != 'X') { //verifica se a coordenada é diferente de 'X'
            printf("Essa coordenada já foi usada! Tente outra ;) \n");
        }
    } while (verificaCoordenadaValida(ordemMatriz, coordenadaLinha, coordenadaColuna) == 0 || matrizVisivel[coordenadaLinha][coordenadaColuna] != 'X'); //verifica se a coordenada é diferente de 'X'
    
}



int main(void){
    int ordemMatriz, quantidadeMinas;
    perguntaDificuldade(&ordemMatriz, &quantidadeMinas);

    int **matrizBombas = (int**) calloc(ordemMatriz, sizeof(int*));
    char **matrizVisivel = (char**) malloc(ordemMatriz * sizeof(char*));
    if(matrizBombas == NULL){
        printf("Memoria insuficiente :( \n)");
        exit(1);
    }
    if(matrizVisivel == NULL){
        printf("Memoria insuficiente :( \n)");
        exit(1);
    }

    for(int cont = 0; cont < ordemMatriz; cont++){
        matrizBombas[cont] = (int*) calloc(ordemMatriz, sizeof(int));
        matrizVisivel[cont] = (char*) malloc(ordemMatriz * sizeof(char));
    }

    sorteiaMinas(ordemMatriz, quantidadeMinas, matrizBombas);
    inicializaMatrizVisivel(ordemMatriz, matrizVisivel);
    contarBombasVizinhas(ordemMatriz, matrizBombas, matrizVisivel);

    imprimeMatrizVisivel(ordemMatriz, matrizVisivel, matrizBombas);

    for(int cont = 0; cont < ordemMatriz; cont++){
        free(matrizBombas[cont]);
        free(matrizVisivel[cont]);
    }
    free(matrizBombas);
    free(matrizVisivel);

    return 0;
}