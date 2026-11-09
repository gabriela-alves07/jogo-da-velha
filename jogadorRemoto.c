#include <stdio.h>
#include "tabuleiro.h"
#include "jogadorRemoto.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #define FECHA(s) closesocket(s)
#else
    #include <signal.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #define FECHA(s) close(s)
#endif

static void iniciaSockets(void){
#ifdef _WIN32
    WSADATA dados;
    WSAStartup(MAKEWORD(2, 2), &dados);  
#else
    signal(SIGPIPE, SIG_IGN); 
#endif
}

int conecta(struct jogadorRemoto *jogador, const char *ip, int porta){
    int sock;
    struct sockaddr_in servidor;

    iniciaSockets();

    sock = (int) socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        printf("Erro ao criar socket.\n");
        return 0;
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(porta);

    servidor.sin_addr.s_addr = inet_addr(ip);  
    if (servidor.sin_addr.s_addr == INADDR_NONE){
        printf("Endereco IP invalido: %s\n", ip);
        FECHA(sock);
        return 0;
    }

    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0){
        printf("Erro ao conectar em %s:%d (o servidor esta rodando?)\n", ip, porta);
        FECHA(sock);
        return 0;
    }

    jogador->socketConexao = sock;
    return 1;
}

int aceita(struct jogadorRemoto *jogador, int porta){
    int servidor, cliente;
    struct sockaddr_in endereco;

    iniciaSockets();

    servidor = (int) socket(AF_INET, SOCK_STREAM, 0);
    if (servidor < 0){
        printf("Erro ao criar socket.\n");
        return 0;
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(porta);

    if (bind(servidor, (struct sockaddr *)&endereco, sizeof(endereco)) < 0){
        printf("Erro no bind (a porta %d ja esta em uso?)\n", porta);
        FECHA(servidor);
        return 0;
    }

    if (listen(servidor, 1) < 0){
        printf("Erro no listen.\n");
        FECHA(servidor);
        return 0;
    }

    printf("Aguardando adversario na porta %d...\n", porta);

    cliente = (int) accept(servidor, NULL, NULL);
    if (cliente < 0){
        printf("Erro no accept.\n");
        FECHA(servidor);
        return 0;
    }

    jogador->socketServidor = servidor;
    jogador->socketConexao = cliente;
    return 1;
}

int enviaJogada(struct jogadorRemoto *jogador, int linha, int coluna){
    char jogada = linha * 3 + coluna;

    return send(jogador->socketConexao, &jogada, 1, 0) == 1;
}

int jogaRemoto(int M[3][3], struct jogadorRemoto jogador){
    char jogada;

    printf("Aguardando jogada do adversario (%c)...\n", jogador.tipo == 4 ? 'X' : 'O');

    if (recv(jogador.socketConexao, &jogada, 1, 0) <= 0){
        printf("O adversario desconectou.\n");
        return 0;
    }
    if (jogada < 0 || jogada > 8 || M[jogada / 3][jogada % 3] != 0){
        printf("Jogada invalida recebida do adversario.\n");
        return 0;
    }

    marcaJogada(M, jogada / 3, jogada % 3, jogador.tipo);
    return 1;
}

void fechaRemoto(struct jogadorRemoto *jogador){
    if (jogador->socketConexao >= 0){
        FECHA(jogador->socketConexao);
        jogador->socketConexao = -1;
    }
    if (jogador->socketServidor >= 0){
        FECHA(jogador->socketServidor);
        jogador->socketServidor = -1;
    }
}