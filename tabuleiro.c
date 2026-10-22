
#include <stdio.h>
#include "tabuleiro.h"

int M[3][3]={
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

void desenha(void){

    printf("\033[2J\033[H");

    for (int i = 0; i < 3; i++){

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
            printf("-----\n");
        }
    }
}

void marcaJogada(int x, int y, int tipo){

    M[x][y] = tipo;
}
int temVencedor(void){
    
}