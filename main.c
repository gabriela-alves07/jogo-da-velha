
#include "partida.h"

int main(){

    int M[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    struct jogadorTeclado jogadorX = configuraJogadores(4);
    struct jogadorTeclado jogadorO = configuraJogadores(1);

    inicia(M, jogadorX, jogadorO);

    return 0;
}