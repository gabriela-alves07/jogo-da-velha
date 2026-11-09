#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

static int escolheModoLocal(void){
    int opcao, lido, c;

    while (1){
        printf("=== JOGO DA VELHA - SERVIDOR (X) ===\n");
        printf("1 - Jogar pelo teclado\n");
        printf("2 - Deixar o computador jogar\n");
        printf("Escolha: ");
        lido = scanf("%d", &opcao);

        if (lido == EOF){
            exit(0);
        }
        if (lido == 1 && (opcao == 1 || opcao == 2)){
            return (opcao == 1) ? HUMANO : COMPUTADOR;
        }
        if (lido != 1){
            while ((c = getchar()) != '\n' && c != EOF);
        }
        printf("Opcao invalida.\n\n");
    }
}

int main(int argc, char *argv[]){
    int M[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int porta = 8080;

    if (argc > 1){
        porta = atoi(argv[1]);
        if (porta < 1 || porta > 65535){
            printf("Porta invalida. Uso: %s [porta]\n", argv[0]);
            return 1;
        }
    }

    int modoLocal = escolheModoLocal();

    struct jogador local = configuraJogadores(modoLocal, 4);
    struct jogador remoto = configuraJogadores(REMOTO, 1);

    if (!aceita(&remoto.remoto, porta)){
        return 1;
    }
    printf("Adversario conectado!\n");

    inicia(M, local, remoto);

    fechaRemoto(&remoto.remoto);
    return 0;
}
