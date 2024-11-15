#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

/*Essa funçao é responsável por perguntar ao jogador a dificuldade que ele quer escolher, a partir da dificuldade escolhida será determinada o tamanho do campo
e a quantidade de minas que terá no campo.*/
void perguntaDificuldade(int *ordemMatriz, int *quantidadeMinas) {

    printf("Ola caro jogador, selecione uma dificuldade para iniciarmos o jogo!\n");
    printf("Aperte '1' para facil, '2' para medio ou '3' para dificil:\n");

    int selecaoDificuldade;
    scanf(" %d", &selecaoDificuldade);

    switch (selecaoDificuldade){
    case 1:
        *ordemMatriz = 10;
        *quantidadeMinas = 15;
        break;
    case 2:
        *ordemMatriz = 20;
        *quantidadeMinas = 60;
        break;
    case 3:
        *ordemMatriz = 30;
        *quantidadeMinas = 135;
        break;
    default:
        *ordemMatriz = 20;
        *quantidadeMinas = 60;
        break;
    }
}

void alocaMatrizes(int ordemMatriz, int **matrizBomba, char **matrizVisivel) {
    // Loop que percorre todas as linhas das matrizes.
    for(int cont = 0; cont < ordemMatriz; cont++){
        // Aloca memória para cada linha da matriz matrizBomba, usando "calloc" para inicializar as células com zero.
        matrizBomba[cont] = (int*) calloc(ordemMatriz, sizeof(int));
        
        // Aloca memória para cada linha da matriz matrizVisivel, usando "malloc".
        matrizVisivel[cont] = (char*) malloc(ordemMatriz * sizeof(char));

        // Verifica se a alocação de memória para qualquer uma das matrizes falhou.
        if(matrizBomba[cont] == NULL || matrizVisivel[cont] == NULL){
            // Caso a alocação falhe, exibe uma mensagem de erro e encerra o programa.
            printf("Memória insuficiente :( \n)");
            exit(1); // Encerra o programa com falha.S
        }
    }
}

//Essa função inicializa a matriz de char com todos os elementos sendo iguais a 'X'.
void inicializaMatrizVisivel(int ordemMatriz, char **matrizVisivel) {
    for (int contL = 0; contL < ordemMatriz; contL++) {
        for (int contC = 0; contC < ordemMatriz; contC++) {
            matrizVisivel[contL][contC] = 'X'; // Inicializa todas as coordenadas como se estivessem fechadas.
        }
    }
}
//Função que retorna a matrizBomba com um número 'N' de bombas.
void sorteiaMinas(int ordemMatriz, int quantidadeBombas, int **matrizCampo) {

    int coordenadaX, coordenadaY;

    srand(time(NULL)); // Inicializa a função rand() com uma semente baseada no tempo atual, para gerar números aleatórios diferentes em cada execução.
    for(int cont = 0; cont < quantidadeBombas; cont++){
        coordenadaX = rand() % ordemMatriz; //Aqui estamos sorteando uma coordenada aleatória para x, dentro dos limites do campo.
        coordenadaY = rand() % ordemMatriz; //aqui estamos sorteando uma coordenada aleatoria para y, dentro dos limites do campo.

        // Verifica se a célula sorteada ainda não tem uma bomba (valor -1).
        if(matrizCampo[coordenadaX][coordenadaY] == 0){ 
            matrizCampo[coordenadaX][coordenadaY] = -1;
        }
        // Se a célula já tiver uma bomba, decrementa o contador para sortear uma nova posição.
        else{
            cont--; 
        }
    }
}

//Função que verifica a validez de uma coordenada, se ela está, ou não, dentro dos limites da matriz.
int verificaCoordenadaValida(int ordemMatriz, int linha, int coluna) {
    int ehValida;

    // Verifica se a coordenada (linha, coluna) está dentro dos limites da matriz.
    if(linha >= 0 && linha < ordemMatriz && coluna >= 0 && coluna < ordemMatriz){
        ehValida = 1; //Se a coordenada é valida, a variável 'ehValida' recebe '1', pois em C qualquer valor diferente de '0' é interpretado como verdadeiro.
    }
    else{
        ehValida = 0; //Se minha coordenada não for válida, 'ehValida' recebe 0, que é interpretado como falso.
    }
    return ehValida;
}

//Função que retorna a quantidade de bombas ao redor da minha coordenada atual.
int quantidadeBombasVizinhanca(int linha, int coluna, int ordemMatriz, int **matrizBomba) {

    int totalBombasVizinhaca = 0; // Inicializa a contagem de bombas ao redor com 0.

    if(verificaCoordenadaValida(ordemMatriz, linha - 1, coluna)){ //Verifica se a coordenada superior é valida.
        if(matrizBomba[linha-1][coluna] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna)){   //Verifica se a coordenada inferior é valida.
        if(matrizBomba[linha+1][coluna] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha, coluna-1)){   //Verifica se a coordenada esquerda é valida.
        if(matrizBomba[linha][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha, coluna+1)){   //Verifica se a coordenada direita é valida.
        if(matrizBomba[linha][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha-1, coluna-1)){ //Verifica se a coordenada noroeste é valida.
        if(matrizBomba[linha-1][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha-1, coluna+1)){ //Verifica se a coordenada nordeste é valida.
        if(matrizBomba[linha-1][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna-1)){ //Verifica se a coordenada sudoeste é valida.
        if(matrizBomba[linha+1][coluna-1] == -1){
            totalBombasVizinhaca++;
        }
    }

    if(verificaCoordenadaValida(ordemMatriz, linha+1, coluna+1)){ //Verifica se a coordenada sudeste é valida.
        if(matrizBomba[linha+1][coluna+1] == -1){
            totalBombasVizinhaca++;
        }
    }
    return totalBombasVizinhaca;
}

//Essa função é responsável por mostrar a matriz que será impressa no terminal
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
                printf("%c | ", matrizVisivel[contL][contC]); // Exibe o conteúdo de cada célula da matriz, 'X' para célula que ainda estão fechadas.
        }
        printf("\n");
    }
}

//Essa funcao é responsável por verificar se o jogador ganhou ou perdeu.
int verificaVitoriaDerrota(int ordemMatriz, char **matrizVisivel, int **matrizBomba) {
    int quantidadeX = 0; // Quantidade de quantas coordenadas não reveladas ainda restam.

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

//Esta função é responsável por mostrar a quantidade de bombas que há na vizinhaça de cada coordenada.
void expandirCoordenada(int linha, int coluna, int ordemMatriz, char **matrizVisivel, int **matrizBomba) { 

    /*Este "if" mais externo verifica se a coordenada atual é valida,ou seja, se está dentro da minha matriz, pois em muitos casos
    do algoritimo "flood fill" a coordenada atual será inválida*/
    if(verificaCoordenadaValida(ordemMatriz, linha, coluna) && matrizVisivel[linha][coluna] == 'X'){
        matrizVisivel[linha][coluna] = '0' + quantidadeBombasVizinhanca(linha, coluna, ordemMatriz, matrizBomba);
        if(quantidadeBombasVizinhanca(linha, coluna, ordemMatriz, matrizBomba) == 0){ //Se a quantidade de bombas na vizinhaça for igual a 0, então será implementado algoritimo "o flood fill"

            expandirCoordenada(linha - 1, coluna, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada superior
            expandirCoordenada(linha + 1, coluna, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada inferior
            expandirCoordenada(linha, coluna - 1, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada esquerda
            expandirCoordenada(linha, coluna + 1, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada direita
            expandirCoordenada(linha - 1, coluna - 1, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada noroeste
            expandirCoordenada(linha - 1, coluna + 1, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada nordeste
            expandirCoordenada(linha + 1, coluna - 1, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada sudoeste
            expandirCoordenada(linha + 1, coluna + 1, ordemMatriz, matrizVisivel, matrizBomba); //"flood fill" na coordenada sudeste

        }
    }
}

//Este metodo é responsavel por escanear as coordenadas durante o jogo, além de atualizar a matriz visível.
void jogar(int ordemMatriz, char **matrizVisivel, int **matrizBomba) {
    int coordenadaLinha, coordenadaColuna;

    FILE *log = criarLog();  // Verifique a implementação de criarLog
    if (log == NULL) { 
        printf("Erro ao criar o arquivo de log.\n");
        exit(1);;
    }

    log = abrirLog();

    do {
        imprimeMatrizVisivel(ordemMatriz, matrizVisivel); // Exibe a matriz visível ao jogador para que ele possa escolher onde quer jogar

        // Solicita coordenadas ao jogador até que uma coordenada válida e que ainda não tenha sido selecionada seja escolhida
        int coordenadaValida = 0;  // Variável de controle para coordenada válida

        do {
            printf("Digite a coordenada da linha e em seguida a coordenada da coluna, separadas por virgula, exemplo: 2,7. \n");
            
            scanf("%d,%d", &coordenadaLinha, &coordenadaColuna);
            
            registraCoordenadasMatrizes(ordemMatriz, coordenadaLinha, coordenadaColuna, matrizVisivel);

            coordenadaLinha--;  // Ajusta para o índice da 'matrizBomba'.
            coordenadaColuna--; // Ajusta para o índice da 'matrizBomba'.

            // Verifica se as coordenadas estão dentro dos limites da matriz.
            if (!verificaCoordenadaValida(ordemMatriz, coordenadaLinha, coordenadaColuna)) {
                printf("Coordenada invalida! As coordenadas precisam estar entre o intervalo de 1 a %d ;) \n", ordemMatriz);
            }
             // Verifica se a coordenada já foi revelada anteriormente.
            else if (matrizVisivel[coordenadaLinha][coordenadaColuna] != 'X') {
                printf("Essa coordenada ja foi digitada! Tente outro par de coordenadas ;) \n");
            }
            else{
                coordenadaValida = 1;
            }

        // Continua solicitando coordenadas até que sejam válidas e a célula ainda não tenha sido selecionada.
        } while (!coordenadaValida);

        // Atualiza a matriz visível com a quantidade de bombas vizinhas da célula selecionada.
        expandirCoordenada(coordenadaLinha, coordenadaColuna, ordemMatriz, matrizVisivel, matrizBomba);

    // Continua o jogo enquanto o jogador não venceu e não selecionou uma bomba.
    } while (verificaVitoriaDerrota(ordemMatriz, matrizVisivel, matrizBomba) != 0 && matrizBomba[coordenadaLinha][coordenadaColuna] == 0);

    // Verifica se o jogador venceu ou perdeu
    if(matrizBomba[coordenadaLinha][coordenadaColuna] == 0){
        printf("parabens, vc eh fera\n");
        fprintf(log, "parabens, vc eh fera\n"); //Imprime no "log.txt" a mensagem que aparecerá ao jogador caso ele ganhe.
    }
    else{
        printf("game over\n");
        fprintf(log, "game over\n"); //Imprime no "log.txt" a mensagem que aparecerá ao jogador caso ele perca.
    }

    fclose(log); //Fechando o arquivo que havia sido aberto anteriormente.
}

/*Essa função irá imprimir a matriz original, imprimindo -1 para a coordenada que tem bomba e a quantidade de bombas na vizinhança nas coordenadas que não são bomba*/
void imprimeMatrizBomba(int ordemMatriz, int **matrizBomba){

    printf("Aqui esta a matriz original, -1 representa as bombas! \n");

    // Imprime o cabeçalho das colunas (números de 1 a ordemMatriz)
    printf("    ");
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
            if(matrizBomba[contL][contC] != -1){ //Se não for uma bomba
                matrizBomba[contL][contC] = quantidadeBombasVizinhanca(contL, contC, ordemMatriz, matrizBomba);
                printf(" %d |", matrizBomba[contL][contC]);
            }
            else{ //se for uma bomba
                printf("-1 |"); // Imprime -1 para representar que é uma bomba
            }
        }
        printf("\n");
    }

    FILE *arq = abrirLog();// Abrindo novamente o arquivo de registros.

    registraMatrizBomba(ordemMatriz, matrizBomba); //Registrando a 'matrizBombas'.

    fclose(arq); //Fechando o arquivo.
}

void liberaMemoria(int ordemMatriz, int **matrizBomba, char **matrizVisivel) {
    // Loop que percorre todas as linhas das matrizes
    for (int cont = 0; cont < ordemMatriz; cont++) {
        // Libera a memória alocada para cada linha da matrizBomba
        free(matrizBomba[cont]);
        
        // Libera a memória alocada para cada linha da matrizVisivel
        free(matrizVisivel[cont]);
    }
    
    // Libera a memória alocada para os ponteiros das matrizes
    free(matrizBomba);
    free(matrizVisivel);
}