
#ifndef TABULEIRO_H
#define TABULEIRO_H

enum resultado{JOGADOR_X, JOGADOR_O, EMPATE, EM_JOGO};
void marcaJogada(int M[3][3], int x, int y, int tipo);
void desenha(int M[3][3]);
int temVencedor(int M[3][3]);

#endif
