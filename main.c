#include <stdio.h>
#include "tabuleiro.h"
#include "partida.h"

int main(){
    int M[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int opcao, lido, c;

    while (1){
        printf("=== JOGO DA VELHA ===\n");
        printf("1 - Humano x Humano\n");
        printf("2 - Humano x Computador\n");
        printf("Escolha o modo de jogo: ");
        lido = scanf("%d", &opcao);

        if (lido == EOF){
            return 0;
        }
        if (lido == 1 && (opcao == 1 || opcao == 2)){
            break;
        }
        if (lido != 1){
            while ((c = getchar()) != '\n' && c != EOF);
        }
        printf("Opcao invalida.\n\n");
    }

    struct jogador j1 = configuraJogadores(HUMANO, 4);
    struct jogador j2 = configuraJogadores(opcao == 1 ? HUMANO : COMPUTADOR, 1);

    inicia(M, j1, j2);

    return 0;
}