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

void sorteiaMinas(int tamanhoCampo, int quantidadeBombas, int **matrizCampo){
    int coordenadaX, coordenadaY;
    srand(time(NULL));
    for(int cont = 0; cont < quantidadeBombas; cont++){
        coordenadaX = rand() % tamanhoCampo;
        coordenadaY = rand() % tamanhoCampo;
        if(matrizCampo[coordenadaX][coordenadaY] == 0){
            matrizCampo[coordenadaX][coordenadaY] = -1;
        } else {
            cont--;
        }
    }
}

int verificaCoordenadaValida(int ordemMatriz, int quantidadeLinha, int quantidadeColuna){
    return quantidadeLinha >= 0 && quantidadeLinha < ordemMatriz && quantidadeColuna >= 0 && quantidadeColuna < ordemMatriz;
}

int quantidadeBombasVizinhanca(int linha, int coluna, int ordemMatriz, int **matrizBomba){
    int totalBombasVizinhaca = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Ignorar a célula central
            if (verificaCoordenadaValida(ordemMatriz, linha + i, coluna + j) && matrizBomba[linha + i][coluna + j] == -1) {
                totalBombasVizinhaca++;
            }
        }
    }
    return totalBombasVizinhaca;
}

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
        printf("%02d |", contL+1);
        for (int contC = 0; contC < ordemMatriz; contC++) {
            if (matrizVisivel[contL][contC] == 'O') {
                printf(" %c ", matrizVisivel[contL][contC]);
            } else {
                printf(" X ");
            }
        }
        printf("\n");
    }
}

void inicializaMatrizVisivel(int ordemMatriz, char **matriz) {
    for (int contL = 0; contL < ordemMatriz; contL++) {
        for (int contC = 0; contC < ordemMatriz; contC++) {
            matriz[contL][contC] = 'X'; // Inicializa todas as células como fechadas
        }
    }

}

//esta funcao ira "expandir" a coordenada!
void expandirCoordenada(int ordemMatriz, int linha, int coluna, char ** matrizVisivel, int **matrizBomba){
    if (verificaCoordenadaValida(ordemMatriz, linha, coluna) && matrizVisivel[linha][coluna] == 'X') {
        matrizVisivel[linha][coluna] = quantidadeBombasVizinhanca(linha, coluna, ordemMatriz, matrizBomba) + '0';
    }
}

//este metodo é responsavel por escanerar as coordenadas durante o jogo
void jogar(int ordemMatriz, int **matrizBomba, char **matrizVisivel){
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

    for(int cont = 0; cont < ordemMatriz; cont++){
        matrizBombas[cont] = (int*) calloc(ordemMatriz, sizeof(int));
        matrizVisivel[cont] = (char*) malloc(ordemMatriz * sizeof(char));
    }

    sorteiaMinas(ordemMatriz, quantidadeMinas, matrizBombas);
    inicializaMatrizVisivel(ordemMatriz, matrizVisivel);
    
    // Variáveis para a primeira jogada
    int primeiraJogada = 1;
    int coordenadaX, coordenadaY;

    while (1) {
        imprimeMatrizVisivel(ordemMatriz, matrizVisivel);
        if (matrizBombas[coordenadaX][coordenadaY] == -1) {
            printf("Você caiu em uma bomba! Fim de jogo.\n");
            break;
        } else {
            matrizVisivel[coordenadaX][coordenadaY] = 'O'; // Marcar a célula como aberta
            if (primeiraJogada) {
                // Na primeira jogada, revelar a quantidade de bombas vizinhas
                contarBombasVizinhas(ordemMatriz, matrizBombas, matrizVisivel);
                primeiraJogada = 0; // Atualiza para não ser mais a primeira jogada
            }
        }
    }

    for(int cont = 0; cont < ordemMatriz; cont++){
        free(matrizBombas[cont]);
        free(matrizVisivel[cont]);
    }
    free(matrizBombas);
    free(matrizVisivel);

    return 0;
}
