#include "regras.h"

int regra(int tabuleiro[3][3], int meuSimbolo, int simboloAdversario,
          int numeroRegra, int *linhaEscolhida, int *colunaEscolhida){

  
    const int linhasDeVitoria[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    const int casasDeCanto[4] = {0, 2, 6, 8};

    if (numeroRegra == 1 || numeroRegra == 2){
        int simboloAnalisado = (numeroRegra == 1) ? meuSimbolo : simboloAdversario;

        for (int linhaAtual = 0; linhaAtual < 8; linhaAtual++){
            int qtdMarcacoes = 0;
            int qtdCasasVazias = 0;
            int casaVazia = -1;

            for (int posicao = 0; posicao < 3; posicao++){
                int casa = linhasDeVitoria[linhaAtual][posicao];
                int valorCasa = tabuleiro[casa / 3][casa % 3];

                if (valorCasa == simboloAnalisado){
                    qtdMarcacoes++;
                }
                else if (valorCasa == 0){
                    qtdCasasVazias++;
                    casaVazia = casa;
                }
            }
            if (qtdMarcacoes == 2 && qtdCasasVazias == 1){
                *linhaEscolhida = casaVazia / 3;
                *colunaEscolhida = casaVazia % 3;
                return 1;
            }
        }
        return 0;
    }

    if (numeroRegra == 3){
        for (int casaTestada = 0; casaTestada < 9; casaTestada++){
            if (tabuleiro[casaTestada / 3][casaTestada % 3] != 0){
                continue;
            }

            tabuleiro[casaTestada / 3][casaTestada % 3] = meuSimbolo;

            int qtdAmeacas = 0;
            for (int linhaAtual = 0; linhaAtual < 8; linhaAtual++){
                int qtdMarcacoes = 0;
                int qtdCasasVazias = 0;

                for (int posicao = 0; posicao < 3; posicao++){
                    int casa = linhasDeVitoria[linhaAtual][posicao];
                    int valorCasa = tabuleiro[casa / 3][casa % 3];

                    if (valorCasa == meuSimbolo){
                        qtdMarcacoes++;
                    }
                    else if (valorCasa == 0){
                        qtdCasasVazias++;
                    }
                }
                if (qtdMarcacoes == 2 && qtdCasasVazias == 1){
                    qtdAmeacas++;
                }
            }

            tabuleiro[casaTestada / 3][casaTestada % 3] = 0;

            if (qtdAmeacas >= 2){
                *linhaEscolhida = casaTestada / 3;
                *colunaEscolhida = casaTestada % 3;
                return 1;
            }
        }
        return 0;
    }

    if (numeroRegra == 4){
        if (tabuleiro[1][1] == 0){
            *linhaEscolhida = 1;
            *colunaEscolhida = 1;
            return 1;
        }
        return 0;
    }

    if (numeroRegra == 5){
        for (int i = 0; i < 4; i++){
            int cantoAdversario = casasDeCanto[i];
            int cantoOposto = casasDeCanto[3 - i];

            if (tabuleiro[cantoAdversario / 3][cantoAdversario % 3] == simboloAdversario
                && tabuleiro[cantoOposto / 3][cantoOposto % 3] == 0){
                *linhaEscolhida = cantoOposto / 3;
                *colunaEscolhida = cantoOposto % 3;
                return 1;
            }
        }
        return 0;
    }

    if (numeroRegra == 6){
        for (int i = 0; i < 4; i++){
            int canto = casasDeCanto[i];

            if (tabuleiro[canto / 3][canto % 3] == 0){
                *linhaEscolhida = canto / 3;
                *colunaEscolhida = canto % 3;
                return 1;
            }
        }
        return 0;
    }

    if (numeroRegra == 7){
        for (int casa = 0; casa < 9; casa++){
            if (tabuleiro[casa / 3][casa % 3] == 0){
                *linhaEscolhida = casa / 3;
                *colunaEscolhida = casa % 3;
                return 1;
            }
        }
    }

    return 0;
}