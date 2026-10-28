#ifndef PARTIDA_H
#define PARTIDA_H

#include "jogadorTeclado.h"
#include "jogadorIA.h"

enum modoJogador { HUMANO, COMPUTADOR };


struct jogador {
    int modo;                     
    struct jogadorTeclado teclado; 
    struct jogadorIA ia;           
};

struct jogador configuraJogadores(int modo, int tipo);
void inicia(int M[3][3], struct jogador j1, struct jogador j2);

#endif