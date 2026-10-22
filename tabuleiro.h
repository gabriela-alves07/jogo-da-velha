
#ifndef TABULEIRO_H
#define TABULEIRO_H

enum resultado{JOGADOR_X, JOGADOR_O, EMPATE, NINGUEM_GANHOU};
void marcaJogada(int x, int y, int tipo);
void desenha(void);
int temVencedor(void);

#endif
