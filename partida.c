#include <stdio.h>
#include "tabuleiro.h"
#include "jogadorTeclado.h"
#include "jogadorIA.h"
#include "partida.h"

struct jogador configuraJogadores(int modo, int tipo){
    struct jogador jogador;

    jogador.modo = modo;
    jogador.teclado.tipo = tipo;
    jogador.ia.tipo = tipo;
    return jogador;
}

static void jogaJogador(int M[3][3], struct jogador jogador){
    if (jogador.modo == COMPUTADOR){
        jogaIA(M, jogador.ia);
    }
    else{
        joga(M, jogador.teclado);
    }
}

void inicia(int M[3][3], struct jogador j1, struct jogador j2){
    int resultado = EM_JOGO;
    int vez = 1;

    desenha(M);

    while (resultado == EM_JOGO){
        if (vez == 1){
            jogaJogador(M, j1);
        }
        else{
            jogaJogador(M, j2);
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