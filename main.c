#include <stdio.h>
#include <stdlib.h>

void perguntaDificuldade(int *ordemMatriz, int *quantidadeMinas){

    printf("Ola caro jogador, selecione uma dificuldade para iniciarmos o jogo!\n");
    printf("Aperte 'f' para facil, 'm' para medio ou 'd' para dificil:\n");

    char selecaoDificuldade;
    scanf("%c", &selecaoDificuldade);

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
    }
}

void imprimeCampoComX(){

}


int main(void){
    int ordemMatriz, quantidadeMinas;
    perguntaDificuldade(&ordemMatriz, &quantidadeMinas);

    printf("Tamanho do campo: %d\n", ordemMatriz);
    printf("Quantidade de minas: %d\n", quantidadeMinas);
    
    return 0;
}