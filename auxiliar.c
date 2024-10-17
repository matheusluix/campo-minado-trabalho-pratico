void imprimeMatrizX(int ordemMatriz){
    for(int contLinha = 0; contLinha < ordemMatriz; contLinha++){
        if(contLinha == ordemMatriz - 1){
            printf("%d| ", ordemMatriz);
        }
        else{
            printf("%d | ", contLinha+1);
        }
        for(int contColuna = 0; contColuna < ordemMatriz; contColuna++){
            printf("X ");
        }
        printf("\n");
    }
    printf("    ");
    for(int contColuna = 0; contColuna < ordemMatriz; contColuna++){
        printf("- ");
    }
    printf("\n");
    printf("    ");
    for(int contColuna = 0; contColuna < ordemMatriz; contColuna++){
        printf("%d ", contColuna+1);
    }
}