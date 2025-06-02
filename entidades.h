#ifndef __ENTIDADES__
#define __ENTIDADES__

#include<allegro5/allegro.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_image.h>
#include <allegro5/bitmap.h>

//FRAME ATUAL:
// 0 - PÉ;
// 1 - ANDANDO;
// 2 - PULANDO;
// 3 - ABAIXANDO;
// 4 - ATIRANDO;
struct personagem {
    ALLEGRO_BITMAP *sprites[5];
    int largura;
    int altura;
    int frame_atual;
    float posicao_x;
    float posicao_y;
};

struct personagem *cria_personagem(int largura, int altura, int posicao_x, int posicao_y);

void destroi_personagem(struct personagem *p);

void coloca_personagem(struct personagem *p);

//CHAVE:
//0 - Personagem não está nos frames 1 ou 0;
//1 - Personagem está nos frames 1 ou 0;
struct arma {
    ALLEGRO_BITMAP *sprite;
    int largura;
    int altura;
    int posicao_x;
    int posicao_y;
    int chave;
};

struct arma *cria_arma(int largura, int altura, int posicao_x, int posicao_y, int chave);

void destroi_arma(struct arma *a);

void coloca_arma(struct arma *a);

struct projetil {
    ALLEGRO_BITMAP *sprite;
    int largura;
    int altura;
    int posicao_x;
    int posicao_y;
    int velocidade;
};

struct projetil *cria_projetil(int largura, int altura, int posicao_x, int posicao_y, int velocidade);

void destroi_projetil(struct projetil *pjt);

void coloca_projetil(struct projetil *pjt);

struct inimigo {
    ALLEGRO_BITMAP *sprite;
    int largura;
    int altura;
    int frame_atual;
    float posicao_x;
    float posicao_y;
};

struct inimigo *cria_inimigo(int largura, int altura, int posicao_x, int posicao_y);

void destroi_inimigo(struct inimigo *i);

void coloca_inimigo(struct inimigo *i, float movendo_mundo);

struct explosao {
    ALLEGRO_BITMAP *sprite;
    int largura;
    int altura;
    int frame_atual;
    float posicao_x;
    float posicao_y;
};

struct explosao *cria_explosao(int largura, int altura, int posicao_x, int posicao_y);

void destroi_explosao(struct explosao *e);

void coloca_explosao(struct explosao *e);


#endif
