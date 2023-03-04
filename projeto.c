#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void main(){
    setlocale(LC_ALL, "Portuguese");

    int qtdVar, qtdRest;

    printf("CALCULO SIMPLEX - MÉTODO TABELADO");
    printf("\n\nZ = X1 + X2 + Xn...");
    printf("\n\nQuantas variáveis de decisão tem o Z? ");
    scanf("%d", &qtdVar);

    float vars[qtdVar];
    for(int i = 0; i < qtdVar; i++){
        printf("Insira um valor para X%d: ", i+1);
        scanf("%f",&vars[i]);
    }
    //Trocando sinai dos X's de Z
    for(int i = 0; i < qtdVar; i++){
        vars[i] = vars[i]*(-1);
    }

    printf("\nQuantas restrições tem o problema? ");
    scanf("%d", &qtdRest);

    //Definindo a linha 1. (Linha Z)
    int tamanhoColuna = qtdVar+qtdRest+2;
    float Z[tamanhoColuna];
    Z[0] = 1;
    int aux = 1;
    while(aux <= qtdVar){
        Z[aux] = vars[aux-1];
        aux++;
    }
    for(int i = qtdVar+2; i < tamanhoColuna; i++){
        Z[i] = 0;
    }
    printf("\nLinha Z = ");
    for(int i = 0; i < tamanhoColuna; i++){
        printf("%.2f ", Z[i]);
    }
    printf("\n\n");

    //Adicionando B ao numero de variaveis
    qtdVar += 1;
    float rest[qtdRest][tamanhoColuna];

    for(int linha = 0; linha < qtdRest; linha++){
        for(int coluna = 0; coluna < tamanhoColuna; coluna++){
            if(coluna == 0){
                rest[linha][coluna] = 0;
            }else{
                if(coluna < qtdVar){
                    printf("Insira um valor para X%d na restrição %d: ",(coluna),(linha+1));
                    scanf("%f",&rest[linha][coluna]);
                }else{
                    if(coluna == (tamanhoColuna-1)){
                        printf("Insira um valor para B na restrição %d: ",(linha+1));
                        scanf("%f",&rest[linha][coluna]);
                    }else{
                        rest[linha][coluna] = 0;
                    }
                }
            }
        }
        for(int i = 0; i < tamanhoColuna; i++){
            printf("%.2f ", rest[linha][i]);
        }
        printf("\n\n");
    }

    int aux3 = 0;
    for(int linha = 0; linha < qtdRest; linha++){
        for(int coluna = 0; coluna < tamanhoColuna; coluna++){
            if(coluna == aux3+qtdVar){
                rest[linha][coluna] = 1;
            }
        }
        aux3++;
    }

    //Adicionando a função Z a quantidade de linhas.
    qtdRest += 1;
    float matriz[qtdRest][tamanhoColuna];

    //Criando matriz com todos os valores inseridos
    for(int linha = 0; linha < qtdRest; linha++){
        for(int coluna = 0; coluna < tamanhoColuna; coluna++){
            if(linha == 0){
                matriz[linha][coluna] = Z[coluna];
            }else{
                matriz[linha][coluna] = rest[linha-1][coluna];
            }
        }
    }

    int continua = 1;
    while(continua){
        printf("\n--------------------- MATRIZ ---------------------\n\n");
        int contadorParaX = 1;
        int contadorParaF = 1;
        for(int coluna = 0; coluna < tamanhoColuna; coluna++){
            if(coluna == 0){
                printf(" Z\t");
            }else if(coluna == (tamanhoColuna-1)){
                printf(" B\t");
            }else{
                if(contadorParaX < qtdVar){
                    printf(" X%d\t",contadorParaX);
                    contadorParaX++;
                }else{
                    printf(" F%d\t",contadorParaF);
                    contadorParaF++;
                }
            }
        }
        printf("\n");
        for(int linha = 0; linha < qtdRest; linha++){
            for(int coluna = 0; coluna < tamanhoColuna; coluna++){
                printf("%.2f\t", matriz[linha][coluna]);
            }
            printf("\n\n");
        }
        system("pause");

        int colunaDoMenorNumero = 0;
        float menorNumeroDeZ = 9999999;
        for(int coluna = 0; coluna < tamanhoColuna; coluna++){
            if(matriz[0][coluna] < menorNumeroDeZ){
                menorNumeroDeZ = matriz[0][coluna];
                colunaDoMenorNumero = coluna;
            }
        }
        printf("Menor número de Z: %.2f", menorNumeroDeZ);

        for(int coluna = 0; coluna < tamanhoColuna; coluna++){
            if(matriz[0][coluna] < 0){
                continua = 1;
                break;
            }else{
                continua = 0;
            }
        }

        if(continua){
            float menorDivisaoPelaColunaEntra = 9999999;
            int linhaMenorValorDaDivisao = 0;
            float pivoMaster = 0;
            for(int linha = 0; linha < qtdRest; linha++){
                float resultado = matriz[linha][tamanhoColuna-1] / matriz[linha][colunaDoMenorNumero];
                if(resultado > 0){
                    if(resultado < menorDivisaoPelaColunaEntra){
                        pivoMaster =  matriz[linha][colunaDoMenorNumero];
                        menorDivisaoPelaColunaEntra = resultado;
                        linhaMenorValorDaDivisao = linha;
                    }
                }
            }
            printf("\nMenor divisao pela coluna entra: %.2f", menorDivisaoPelaColunaEntra);
            printf("\nPivo: %.2f", pivoMaster);

            float novaLinhaPivo[tamanhoColuna];
            for(int i = 0; i < tamanhoColuna; i++){
                novaLinhaPivo[i] = matriz[linhaMenorValorDaDivisao][i] / pivoMaster;
            }
            printf("\nNova Linha Pivo:\n");
            for(int i = 0; i < tamanhoColuna; i++){
                printf("%.2f ", novaLinhaPivo[i]);
            }

            for(int j = 0; j < qtdRest; j++){
                if(j != linhaMenorValorDaDivisao){
                    //Multiplicação da nova linha
                    float novaLinha[tamanhoColuna];
                    for(int i = 0; i < tamanhoColuna; i++){
                        novaLinha[i] = novaLinhaPivo[i] * (matriz[j][colunaDoMenorNumero] * -1);
                    }
                    //Exibição
                    /*printf("\nNova Linha:\n");
                    for(int i = 0; i < tamanhoColuna; i++){
                        printf("%.2f ", novaLinha[i]);
                    }*/

                    //Soma da nova linha
                    float novaLinhaSomada[tamanhoColuna];
                    for(int i = 0; i < tamanhoColuna; i++){
                        novaLinhaSomada[i] = matriz[j][i] + novaLinha[i];
                    }
                    //Exibição
                    printf("\nNova Linha %d:\n",j+1);
                    for(int i = 0; i < tamanhoColuna; i++){
                        printf("%.2f ", novaLinhaSomada[i]);
                    }
                    //Inserindo os novas linhas na matriz
                    for(int i = 0; i < tamanhoColuna; i++){
                        matriz[j][i] = novaLinhaSomada[i];
                    }
                }else{
                    //Inserindo a nova linha pivo na matriz
                    for(int i = 0; i < tamanhoColuna; i++){
                        matriz[j][i] = novaLinhaPivo[i];
                    }
                }
            }
        }else{
            printf("\n\n--------------- SOLUÇÃO ---------------\n\n");
            //Imprimindo valor de Z
            printf("\nA solução ótima é: Z = %.2f\n", matriz[0][tamanhoColuna-1]);

            //Encontrando as variáveis básicas e as não básicas
            int isVariavelBasica; //Variavel somente para determinar se a variável é básica ou não
            int linhaQuePossuiValorUm;
            contadorParaX = 1;
            contadorParaF = 1;

            for(int coluna = 1; coluna < (tamanhoColuna-1); coluna++){
                linhaQuePossuiValorUm = 0;
                for(int linha = 0; linha < qtdRest; linha++){
                    if(matriz[linha][coluna] != 0 && matriz[linha][coluna] != 1){
                        isVariavelBasica = 0;
                        break;
                    }else{
                        if(matriz[linha][coluna] == 1){
                            linhaQuePossuiValorUm = linha;
                        }
                        isVariavelBasica = 1;
                    }
                }
                if(isVariavelBasica){
                    if(contadorParaX < qtdVar){
                        printf("\nVariável Básica: X%d = %.2f", contadorParaX, matriz[linhaQuePossuiValorUm][tamanhoColuna-1]);
                        contadorParaX++;
                    }else{
                        printf("\nVariável Básica: F%d = %.2f", contadorParaF, matriz[linhaQuePossuiValorUm][tamanhoColuna-1]);
                        contadorParaF++;
                    }
                }else{
                    if(contadorParaX < (qtdVar)){
                        printf("\nVariável NÃO Básica: X%d = 0", contadorParaX);
                        contadorParaX++;
                    }else{
                        printf("\nVariável NÃO Básica: F%d = 0", contadorParaF);
                        contadorParaF++;
                    }
                }
            }
        }
        printf("\n\n");
        system("pause");
    }
}
