#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* criarLog() {
    FILE *arq = fopen("log.txt", "w");
    if(arq == NULL){
        printf("Nao foi possivel abrir o arquivo");
        exit(1);
    }

    time_t tempoAtual = time(NULL);
    fprintf(arq, "Data e hora do início do jogo: %s\n", ctime(&tempoAtual));
    
    fclose(arq);
    return arq;
}

FILE* abrirLog() {
    FILE *arq = fopen("log.txt", "a");

    if(arq == NULL){
        printf("Nao foi possivel abrir o arquivo");
        exit(1);
    }

    return arq;
}

void registraCoordenadasMatrizes(int ordemMatriz, int linha, int coluna, char **matrizVisivel) {

    FILE *log = abrirLog();

    fprintf(log, "   ");
    for (int cont = 1; cont <= ordemMatriz; cont++) {
        fprintf(log, "%02d |", cont); // Exibe o número da coluna com dois dígitos, ex: 01
    }
    fprintf(log, "\n   ");

    // Imprime uma linha de separação entre o cabeçalho e a matriz
    for (int cont = 0; cont < ordemMatriz; cont++) {
        fprintf(log, "----");
    }
    fprintf(log, "\n");

    for (int contL = 0; contL < ordemMatriz; contL++) {
        fprintf(log, "%02d| ", contL + 1); // Exibe o número da linha com dois dígitos, ex: 02
        for (int contC = 0; contC < ordemMatriz; contC++) {
                fprintf(log, "%c | ", matrizVisivel[contL][contC]); // Exibe o conteúdo de cada célula da matriz, 'X' para célula oculta, '1' para células reveladas com uma bomba na vizinhança
        }
        fprintf(log, "\n");
    }

    fprintf(log, "Digite a coordenada da linha e em seguida a coordenada da coluna, separadas por virgula, exemplo: 2,7. \n");

    if(linha < 1 || linha > ordemMatriz || coluna < 1 || coluna > ordemMatriz) {
        fprintf(log, "%d,%d\n", linha, coluna);
        fprintf(log, "Coordenada invalida! As coordenadas precisam estar entre o intervalo de 1 a %d ;) \n", ordemMatriz);
        fprintf(log, "Digite a coordenada da linha e em seguida a coordenada da coluna, separadas por virgula, exemplo: 2,7. \n");
    }
    else if (matrizVisivel[linha][coluna] != 'X') {
        fprintf(log, "%d,%d\n", linha, coluna);
        fprintf(log, "Essa coordenada ja foi digitada! Tente outro par de coordenadas ;) \n");
        fprintf(log, "Digite a coordenada da linha e em seguida a coordenada da coluna, separadas por virgula, exemplo: 2,7. \n");
    }
    else{
        fprintf(log, "%d,%d\n", linha, coluna);
    }

    fprintf(log, "\n");

    fclose(log);
}

void registraMatrizBomba(int ordemMatriz, int **matrizBomba) {

    FILE *arq = abrirLog();

    fprintf(arq, "Aqui esta a matriz original, -1 representa as bombas! \n");

    // Imprime o cabeçalho das colunas (números de 1 a ordemMatriz)
    fprintf(arq, "    ");
    for (int cont = 1; cont <= ordemMatriz; cont++) {
        fprintf(arq, "%02d |", cont); // Exibe o número da coluna com dois dígitos
    }
    fprintf(arq, "\n   ");

    // Imprime uma linha de separação
    for (int cont = 0; cont < ordemMatriz; cont++) {
        fprintf(arq, "----");
    }
    fprintf(arq, "\n");

    for (int contL = 0; contL < ordemMatriz; contL++) {
        fprintf(arq, "%02d| ", contL + 1); // Exibe o número da linha com dois dígitos
        for (int contC = 0; contC < ordemMatriz; contC++) {
            if(matrizBomba[contL][contC] != -1){ //se não for uma bomba
                //matrizBomba[contL][contC] = quantidadeBombasVizinhanca(contL, contC, ordemMatriz, matrizBomba);
                fprintf(arq, " %d |", matrizBomba[contL][contC]);
            }
            else{ //se for uma bomba
                fprintf(arq, "-1 |"); // Imprime 1 para representar que é uma bomba
            }
        }
        fprintf(arq, "\n");
    }
}
