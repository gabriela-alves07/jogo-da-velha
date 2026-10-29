
#include "tabuleiro.h"
#include "regras.h"
#include "jogadorIA.h"

void jogaIA(int tabuleiro[3][3], struct jogadorIA jogador){

    int linhaEscolhida, colunaEscolhida;
    int simboloAdversario = (jogador.tipo == 4) ? 1 : 4;

    for (int numeroRegra = 1; numeroRegra <= 7; numeroRegra++){

        if (regra(tabuleiro, jogador.tipo, simboloAdversario, numeroRegra,
                  &linhaEscolhida, &colunaEscolhida)){

            marcaJogada(tabuleiro, linhaEscolhida, colunaEscolhida, jogador.tipo);
            return;
        }
    }
}