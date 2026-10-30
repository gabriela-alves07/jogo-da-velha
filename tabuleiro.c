
#include <stdio.h>
#include "tabuleiro.h"

void desenha(int M[3][3]){

    printf("\033[2J\033[H");
    printf("\n");

    printf("  1 2 3\n");
    for (int i = 0; i < 3; i++){
        printf("%d ", i + 1);

        for (int j = 0; j < 3; j++){

            if (j > 0){
                printf("|");
            }
            if (M[i][j] == 0){
                printf(" ");
            }
            else if(M[i][j] == 4){
                printf("X");
            }
            else{
                printf("O");
            }
        }
        printf("\n");

        if (i < 2){
            printf("  -----\n");
        }
    }
}

void marcaJogada(int M[3][3], int x, int y, int tipo){
    M[x][y] = tipo;
}
int temVencedor(int M[3][3]){

    for (int i = 0; i < 3; i++){
        int somaL = 0, somaC = 0;

        for (int j = 0; j < 3; j++){
            somaL += M[i][j];
            somaC += M[j][i];
        }
        if (somaL == 12 || somaC == 12){
            return JOGADOR_X;
        }
        else if (somaL == 3 || somaC == 3){
            return JOGADOR_O ;   
        }
    }
    int somaD1 = M[0][0] + M[1][1] + M[2][2];
    int somaD2 = M[0][2] + M[1][1] + M[2][0];

    if (somaD1 == 12 || somaD2 == 12){
        return JOGADOR_X;
    }
    if (somaD1 == 3 || somaD2 == 3){
        return JOGADOR_O;
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (M[i][j] == 0){
                return EM_JOGO;
            }
        }
    }
    return EMPATE;
}