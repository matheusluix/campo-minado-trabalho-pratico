#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*essa funçao é responsável por perguntar ao jogador a dificuldade que ele quer escolher, a partir da dificuldade escolhida será determinada o tamanho do campo
e a quantidade de minas que terá no campo*/
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

void alocaMatrizes(int ordemMatriz, int **matrizBomba, char **matrizVisivel) {
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
}

//essa funcao inicializa a minha matriz de char com todos os elementos sendo iguais a 'X'
void inicializaMatrizVisivel(int ordemMatriz, char **matrizVisivel) {
    for (int contL = 0; contL < ordemMatriz; contL++) {
        for (int contC = 0; contC < ordemMatriz; contC++) {
            matrizVisivel[contL][contC] = 'X'; // Inicializa todas as células como se estivessem fechadas
        }
    }
}
//função que retorna a matrizBomba com um número N de bombas
void sorteiaMinas(int tamanhoCampo, int quantidadeBombas, int **matrizCampo){

    int coordenadaX, coordenadaY;

    srand(time(NULL)); // Inicializa a função rand() com uma semente baseada no tempo atual, para gerar números aleatórios diferentes em cada execução
    for(int cont = 0; cont < quantidadeBombas; cont++){
        coordenadaX = rand() % tamanhoCampo; //aqui estamos sorteando uma coordenada aleatória para x, dentro dos limites do campo
        coordenadaY = rand() % tamanhoCampo; //aqui estamos sorteando uma coordenada aleatoria para y, dentro dos limites do campo

        // Verifica se a célula sorteada ainda não tem uma bomba (valor -1)
        if(matrizCampo[coordenadaX][coordenadaY] == 0){ 
            matrizCampo[coordenadaX][coordenadaY] = -1;
        }
        // Se a célula já tiver uma bomba, decrementa o contador para sortear uma nova posição
        else{
            cont--; 
        }
    }
}

//funcao que verifica a validez de uma coordenada
int verificaCoordenadaValida(int ordemMatriz, int linha, int coluna){
    int ehValida;

    // Verifica se a coordenada (linha, coluna) está dentro dos limites da matriz
    if(linha >= 0 && linha < ordemMatriz && coluna >= 0 && coluna < ordemMatriz){
        ehValida = 1; //se a minha coordenada é valida, a variável 'ehValida' recebe '1', pois em C qualquer valor diferente de '0' é interpretado como verdadeiro
    }
    else{
        ehValida = 0; //se minha coordenada não for válida, 'ehValida' recebe 0, que é interpretado como falso
    }
    return ehValida;
}

//funcao que retorna a quantidade de bombas ao redor da minha coordenada atual
int quantidadeBombasVizinhanca(int linha, int coluna, int ordemMatriz, int **matrizBomba){

    int totalBombasVizinhaca = 0; // Inicializa a contagem de bombas ao redor com 0

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

    // Imprime o cabeçalho das colunas (números de 1 a ordemMatriz)
    printf("   ");
    for (int cont = 1; cont <= ordemMatriz; cont++) {
        printf("%02d |", cont); // Exibe o número da coluna com dois dígitos, ex: 01
    }
    printf("\n   ");

    // Imprime uma linha de separação entre o cabeçalho e a matriz
    for (int cont = 0; cont < ordemMatriz; cont++) {
        printf("----");
    }
    printf("\n");

    for (int contL = 0; contL < ordemMatriz; contL++) {
        printf("%02d| ", contL + 1); // Exibe o número da linha com dois dígitos, ex: 02
        for (int contC = 0; contC < ordemMatriz; contC++) {
                printf("%c | ", matrizVisivel[contL][contC]); // Exibe o conteúdo de cada célula da matriz, 'X' para célula oculta, '1' para células reveladas com uma bomba na vizinhança
        }
        printf("\n");
    }
}

//essa funcao eh responsavel por verificar se o user ganhou ou perdeu
int verificaVitoriaDerrota(int ordemMatriz, char **matrizVisivel, int **matrizBomba){
    int quantidadeX = 0; // quantidade de quantas coordenadas não reveladas ainda restam que não são bombas

    for(int contLinha = 0; contLinha < ordemMatriz; contLinha++){
        for(int contColuna = 0; contColuna < ordemMatriz; contColuna++){
            // Verifica se a célula visível contém 'X' (não foi selecionada) e se a mesma posição na matriz de bombas não contém bomba (valor 0)
            if(matrizVisivel[contLinha][contColuna] == 'X' && matrizBomba[contLinha][contColuna] == 0){
                quantidadeX++; // Incrementa o contador de células que ainda precisam ser reveladas
            }
        }
    }
    return quantidadeX;
}

//este metodo é responsavel por escanerar as coordenadas durante o jogo
void jogar(int ordemMatriz, char **matrizVisivel, int **matrizBomba) {
    int coordenadaLinha, coordenadaColuna;

    do {
        imprimeMatrizVisivel(ordemMatriz, matrizVisivel); // Exibe a matriz visível ao jogador para que ele possa escolher onde quer jogar

        // Solicita coordenadas ao jogador até que uma coordenada válida e que ainda não tenha sido selecionada seja escolhida
        do {
            printf("Digite a coordenada da linha e em seguida a coordenada da coluna: \n");
            scanf("%d %d", &coordenadaLinha, &coordenadaColuna);
            coordenadaLinha--;  // Ajusta para o índice da matriz bomba
            coordenadaColuna--; // Ajusta para o índice da matriz bomba

            // Verifica se as coordenadas estão dentro dos limites da matriz
            if (verificaCoordenadaValida(ordemMatriz, coordenadaLinha, coordenadaColuna) == 0) {
                printf("Coordenada invalida! As coordenadas precisam estar entre o intervalo de 1 a %d ;) \n", ordemMatriz);
            }

             // Verifica se a coordenada já foi revelada anteriormente
            if (matrizVisivel[coordenadaLinha][coordenadaColuna] != 'X') {
                printf("Essa coordenada ja foi digitada! Tente outro par de coordenadas ;) \n");
            }

        // Continua solicitando coordenadas até que sejam válidas e a célula ainda não tenha sido selecionada
        } while (verificaCoordenadaValida(ordemMatriz, coordenadaLinha, coordenadaColuna) == 0 || matrizVisivel[coordenadaLinha][coordenadaColuna] != 'X');

        // Atualiza a matriz visível com a quantidade de bombas vizinhas da célula selecionada
        matrizVisivel[coordenadaLinha][coordenadaColuna] = '0' + quantidadeBombasVizinhanca(coordenadaLinha, coordenadaColuna, ordemMatriz, matrizBomba);

    // Continua o jogo enquanto o jogador não venceu e não selecionou uma bomba
    } while (verificaVitoriaDerrota(ordemMatriz, matrizVisivel, matrizBomba) != 0 && matrizBomba[coordenadaLinha][coordenadaColuna] == 0);

    // Verifica se o jogador venceu ou perdeu
    if(matrizBomba[coordenadaLinha][coordenadaColuna] == 0){
        printf("parabens, vc eh fera\n");
    }
    else{
        printf("game over\n");
    }
}


/*muita atenção aqui, essa função irá imprimir a matriz original, só que ao invés de imprimir com '0' e '-1', ela irá imprimir com '0' e '1'.
Onde 1 representa uma bomba*/
void imprimeMatrizBomba(int ordemMatriz, int **matrizBomba){
    printf("Aqui esta a matriz original, 1 representa as bombas! \n");

    // Imprime o cabeçalho das colunas (números de 1 a ordemMatriz)
    printf("   ");
    for (int cont = 1; cont <= ordemMatriz; cont++) {
        printf("%02d |", cont); // Exibe o número da coluna com dois dígitos
    }
    printf("\n   ");

    // Imprime uma linha de separação
    for (int cont = 0; cont < ordemMatriz; cont++) {
        printf("----");
    }
    printf("\n");

    for (int contL = 0; contL < ordemMatriz; contL++) {
        printf("%02d| ", contL + 1); // Exibe o número da linha com dois dígitos
        for (int contC = 0; contC < ordemMatriz; contC++) {
            if(matrizBomba[contL][contC] == 0){ //se não for uma bomba
                printf("%d | ", matrizBomba[contL][contC]);  // Imprime 0
            }
            else{ //se for uma bomba
                printf("1 | "); // Imprime 1 para representar que é uma bomba
            }
        }
        printf("\n");
    }
}

void liberaMemoria(int ordemMatriz, int **matrizBomba, char **matrizVisivel) {
    for (int cont = 0; cont < ordemMatriz; cont++) {
        free(matrizBomba[cont]);
        free(matrizVisivel[cont]);
    }
    free(matrizBomba);
    free(matrizVisivel);
}


int main(void){
    int ordemMatriz, quantidadeMinas;
    perguntaDificuldade(&ordemMatriz, &quantidadeMinas);

    int **matrizBomba = (int**) calloc(ordemMatriz, sizeof(int*));
    char **matrizVisivel = (char**) malloc(ordemMatriz * sizeof(char*));
    
    sorteiaMinas(ordemMatriz, quantidadeMinas, matrizBomba);
    inicializaMatrizVisivel(ordemMatriz, matrizVisivel);

    jogar(ordemMatriz, matrizVisivel, matrizBomba);

    imprimeMatrizBomba(ordemMatriz, matrizBomba);

    liberaMemoria(ordemMatriz, matrizBomba, matrizVisivel);

    return 0;
}