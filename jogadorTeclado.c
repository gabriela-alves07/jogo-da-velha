
#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "jogadorTeclado.h"

void joga(int M[3][3], struct jogadorTeclado jogador){
    int lin, col, lido, c;

    while (1){
        printf("Jogador %c - informe linha e coluna (1 a 3): ", jogador.tipo == 4 ? 'X' : 'O');
        lido = scanf("%d %d", &lin, &col);

        if (lido == EOF){
            exit(0);
        }
        if (lido != 2){
            while ((c = getchar()) != '\n' && c != EOF);   
            printf("Entrada invalida.\n");
            continue;
        }
        if (lin < 1 || lin > 3 || col < 1 || col > 3){
            printf("Posicao fora do tabuleiro.\n");
            continue;
        }
        if (M[lin - 1][col - 1] != 0){
            printf("Casa ocupada. Escolha outra.\n");
            continue;
        }

        marcaJogada(M, lin - 1, col - 1, jogador.tipo);   
        return;
    }
}