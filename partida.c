#include <stdio.h>
#include "tabuleiro.h"
#include "jogadorTeclado.h"
#include "jogadorIA.h"
#include "jogadorRemoto.h"
#include "partida.h"

struct jogador configuraJogadores(int modo, int tipo){
    struct jogador jogador;

    jogador.modo = modo;
    jogador.teclado.tipo = tipo;
    jogador.ia.tipo = tipo;
    jogador.remoto.tipo = tipo;
    jogador.remoto.socketConexao = -1;
    jogador.remoto.socketServidor = -1;
    return jogador;
}
static int jogaJogador(int M[3][3], struct jogador jogador){
    if (jogador.modo == COMPUTADOR){
        jogaIA(M, jogador.ia);
        return 1;
    }
    if (jogador.modo == REMOTO){
        return jogaRemoto(M, jogador.remoto);
    }
    joga(M, jogador.teclado);
    return 1;
}

static void copiaTabuleiro(int destino[3][3], int origem[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            destino[i][j] = origem[i][j];
        }
    }
}
static int enviaJogadaLocal(int antes[3][3], int depois[3][3], struct jogadorRemoto *remoto){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (antes[i][j] != depois[i][j]){
                return enviaJogada(remoto, i, j);
            }
        }
    }
    return 0;
}

void inicia(int M[3][3], struct jogador j1, struct jogador j2){
    int resultado = EM_JOGO;
    int vez = 1;
    int antes[3][3];

    desenha(M);

    while (resultado == EM_JOGO){
        struct jogador *atual = (vez == 1) ? &j1 : &j2;
        struct jogador *outro = (vez == 1) ? &j2 : &j1;

        copiaTabuleiro(antes, M);

        if (!jogaJogador(M, *atual)){
            printf("Partida encerrada.\n");
            return;
        }

        desenha(M);

        if (atual->modo != REMOTO && outro->modo == REMOTO){
            if (!enviaJogadaLocal(antes, M, &outro->remoto)){
                printf("Nao foi possivel enviar a jogada ao adversario.\n");
                return;
            }
        }

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