#include <stdio.h>
#include "tabuleiro.h"
#include "jogadorTeclado.h"
#include "partida.h"

struct jogadorTeclado configuraJogadores(int tipo){
    struct jogadorTeclado jogador;

    jogador.tipo = tipo;
    return jogador;
}

void inicia(int M[3][3], struct jogadorTeclado j1, struct jogadorTeclado j2){
    int resultado = EM_JOGO;
    int vez = 1;

    desenha(M);

    while (resultado == EM_JOGO){
        if (vez == 1){
            joga(M, j1);
        }
        else{
            joga(M, j2);
        }

        desenha(M);
        resultado = temVencedor(M);
        vez = (vez == 1) ? 2 : 1;
    }

    if (resultado == JOGADOR_X){
        printf("Jogador X venceu!\n");
    }
    else if (resultado == JOGADOR_O){
        printf("Jogador O venceu!\n");
    }
    else{
        printf("Empate (deu velha)!\n");
    }
}