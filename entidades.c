#include "entidades.h"
#include <allegro5/bitmap_io.h>
#include <stdio.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>                                                   //Biblioteca para usar fontes legais.
#include <allegro5/bitmap.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

//FRAME ATUAL:
// 0 - PÉ;
// 1 - ANDANDO;
// 2 - PULANDO;
// 3 - ABAIXANDO;
// 4 - ATIRANDO;
struct personagem *cria_personagem(int largura, int altura, int posicao_x, int posicao_y) {
    
    struct personagem *p = malloc(sizeof(struct personagem));
    if (!p)
        return NULL; 
    
    p->altura = altura;
    p->largura = largura;
    p->frame_atual = 0;
    p->posicao_x = posicao_x;
    p->posicao_y = posicao_y;

    p->sprites[0] = al_load_bitmap("Sprites/p_pé.png");
    p->sprites[1] = al_load_bitmap("Sprites/p_andando.png");
    p->sprites[2] = al_load_bitmap("Sprites/p_pulando.png");
    p->sprites[3] = al_load_bitmap("Sprites/p_abaixando.png");
    p->sprites[4] = al_load_bitmap("Sprites/p_atirando.png");

    //Loop para se não existir alguma dessas imagens, encerrar o programa:
    for (int i = 0; i < 5; i++) {
        if (!p->sprites[i]) {
            printf("Erro ao carregar sprite %d\n", i);
            for (int j = 0; j <= i; j++) {
                if (p->sprites[j])
                    al_destroy_bitmap(p->sprites[j]);
            }
            free(p);
            return NULL;
        }
    }

    return p;
}

void destroi_personagem(struct personagem *p) {
    if (p) {
        for (int i = 0; i < 5; i++) {
            if (p->sprites[i])
                al_destroy_bitmap(p->sprites[i]);
        }
        free(p);
    }
}


void coloca_personagem(struct personagem *p) {
    al_draw_scaled_bitmap(p->sprites[p->frame_atual], 0, 0, 32, 48, p->posicao_x, p->posicao_y,p->largura, p->altura, 0);
}

struct arma *cria_arma(int largura, int altura, int posicao_x, int posicao_y, int chave) {
    struct arma *a = malloc(sizeof(struct arma));
    if (!a) 
        return NULL;

    a->largura = largura;
    a->altura = altura;
    a->posicao_x = posicao_x;
    a->posicao_y = posicao_y;
    a->chave = chave;

    a->sprite = al_load_bitmap("Sprites/arma.png");

    return a;
}

void destroi_arma(struct arma *a) {
    if (a) {
        al_destroy_bitmap(a->sprite);
        free(a);
    }
}

void coloca_arma(struct arma *a) {
    al_draw_scaled_bitmap(a->sprite, 0,0,1024,1024, a->posicao_x, a->posicao_y, a->largura, a->altura, 0);
}

struct projetil *cria_projetil(int largura, int altura, int posicao_x, int posicao_y, int velocidade) {
    struct projetil *pjt = malloc(sizeof(struct projetil));
    if (!pjt)
        return NULL;

    pjt->largura = largura;
    pjt->altura = altura;
    pjt->posicao_x = posicao_x;
    pjt->posicao_y = posicao_y;
    pjt->velocidade = velocidade;

    pjt->sprite = al_load_bitmap("Sprites/hit_frame.png");
    if (!pjt->sprite) {
        printf("erro ao carregar sprite do hit\n");
        return NULL;
    }

    return pjt;
}

void destroi_projetil(struct projetil *pjt) {
    if (pjt) {
        al_destroy_bitmap(pjt->sprite);
        free(pjt);
    }
}

void coloca_projetil(struct projetil *pjt) {
    al_draw_scaled_bitmap(pjt->sprite, 0,0,16,16, pjt->posicao_x, pjt->posicao_y, pjt->largura, pjt->altura, 0);
}

