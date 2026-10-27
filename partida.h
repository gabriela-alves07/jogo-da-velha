#ifndef PARTIDA_H
#define PARTIDA_H

#include "jogadorTeclado.h"

struct jogadorTeclado configuraJogadores(int tipo);
void inicia(int M[3][3], struct jogadorTeclado j1, struct jogadorTeclado j2);

#endif 