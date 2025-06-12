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

struct projetil_personagem {
    ALLEGRO_BITMAP *sprite;
    int largura;
    int altura;
    int posicao_x;
    int posicao_y;
    int velocidade;
};

struct projetil_personagem *cria_projetil_personagem(int largura, int altura, int posicao_x, int posicao_y, int velocidade);

void destroi_projetil_personagem(struct projetil_personagem *pjt);

void coloca_projetil_personagem(struct projetil_personagem *pjt);

struct inimigo {
    ALLEGRO_BITMAP *sprite;
    int largura;
    int altura;
    int frame_atual;
    float posicao_x;
    float posicao_y;
};

//TIPOS:
// 1 - inimigo 1;
// 2 - inimigo 2;
struct inimigo *cria_inimigo(int largura, int altura, int posicao_x, int posicao_y, int tipo);

void destroi_inimigo(struct inimigo *i);

void coloca_inimigo(struct inimigo *i, float movendo_mundo, int tipo);

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

void colisao_inimigo(bool *morte_inimigo, struct projetil_personagem *pjt, struct inimigo *i, float movendo_mundo, int controle);

struct inimigo_bird {
    ALLEGRO_BITMAP *sprites[5];
    int largura;
    int altura;
    int frame_atual;
    float posicao_x;
    float posicao_y;
};

struct inimigo_bird *cria_inimigo_bird(int largura, int altura, int posicao_x, int posicao_y);

void destroi_inimigo_bird(struct inimigo_bird *ib);

void coloca_inimigo_bird(struct inimigo_bird *ib, int frame_atual, float movendo_mundo);

void colisao_inimigo_bird(bool *morte_inimigo, struct projetil_personagem *pjt, struct inimigo_bird *i, float movendo_mundo);

void coloca_projetil_bird(struct projetil *pjt, float movendo_mundo, int adicao_y);

void atira_bird(struct projetil *pjt_bird, float movendo_mundo, int salva);

int colisao_personagem_com_bird(int *count_vida, struct projetil *pjt, struct personagem *p, float movendo_mundo);

int colisao_personagem_com_inimigo2(int *count_vida, struct inimigo *inimigo, struct personagem *p, float movendo_mundo, bool *morte_inimigo_2, int *invencibilidade_frames);

void coloca_projetil_lobo(struct projetil *pjt, float movendo_mundo);

void atira_lobo(struct projetil *pjt_bird, float movendo_mundo, int salva);

int colisao_personagem_com_lobo(bool baixo_pressionado, int *count_vida, struct projetil *pjt, struct personagem *p, float movendo_mundo);

struct inimigo_boss {
    ALLEGRO_BITMAP *sprites[6];
    int largura;
    int altura;
    int frame_atual;
    float posicao_x;
    float posicao_y;
};

struct inimigo_boss *cria_inimigo_boss(int largura, int altura, int posicao_x, int posicao_y);

void destroi_inimigo_boss(struct inimigo_boss *boss);

void coloca_inimigo_boss(struct inimigo_boss *boss, int frame_atual);

#endif
