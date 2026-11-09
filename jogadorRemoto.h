#ifndef JOGADORREMOTO_H
#define JOGADORREMOTO_H
 
struct jogadorRemoto {
    int tipo;            
    int socketConexao;   
    int socketServidor; 
};
 
int conecta(struct jogadorRemoto *jogador, const char *ip, int porta);
 
int aceita(struct jogadorRemoto *jogador, int porta);
 
int enviaJogada(struct jogadorRemoto *jogador, int linha, int coluna);
 
int jogaRemoto(int M[3][3], struct jogadorRemoto jogador);
 
void fechaRemoto(struct jogadorRemoto *jogador);
 
#endif
 