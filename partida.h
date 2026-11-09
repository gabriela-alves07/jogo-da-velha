#ifndef PARTIDA_H
#define PARTIDA_H
 
#include "jogadorTeclado.h"
#include "jogadorIA.h"
#include "jogadorRemoto.h"
 
enum modoJogador { HUMANO, COMPUTADOR, REMOTO };
 
struct jogador {
    int modo;                       
    struct jogadorTeclado teclado;  
    struct jogadorIA ia;            
    struct jogadorRemoto remoto;   
};
 
struct jogador configuraJogadores(int modo, int tipo);
void inicia(int M[3][3], struct jogador j1, struct jogador j2);
 
#endif