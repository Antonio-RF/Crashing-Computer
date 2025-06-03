#include "entidades.h"
#include <allegro5/bitmap_draw.h>
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

struct inimigo *cria_inimigo(int largura, int altura, int posicao_x, int posicao_y, int tipo) {
    struct inimigo *i = malloc(sizeof(struct inimigo));
    if (!i)
        return NULL;

    i->largura = largura;
    i->altura = altura;
    i->posicao_x = posicao_x;
    i->posicao_y = posicao_y;

    if (tipo == 1)
        i->sprite = al_load_bitmap("Sprites/inimigo.png");
    else if (tipo == 2)
        i->sprite = al_load_bitmap("Sprites/inimigo2.png");
    else if (tipo == 3)
        i->sprite = al_load_bitmap("Sprites/inimigo3.png");
    else {
        printf("Imagem não processada ao criar o inimigo");
        return NULL;
    }

    return i;
}

void destroi_inimigo(struct inimigo *i) {
    if (i) {
        al_destroy_bitmap(i->sprite);
        free(i);
    }
}

void coloca_inimigo(struct inimigo *i, float movendo_mundo, int tipo) {
    if (tipo == 1)
        al_draw_scaled_bitmap(i->sprite, 0, 0, 57, 42, i->posicao_x+movendo_mundo, i->posicao_y, i->largura, i->altura, 0);
    else if (tipo == 2) 
        al_draw_scaled_bitmap(i->sprite, 0, 0, 80, 64, i->posicao_x+movendo_mundo, i->posicao_y, i->largura, i->altura, 0);
    else if (tipo == 3)
        al_draw_scaled_bitmap(i->sprite, 0, 0, 96, 76, i->posicao_x+movendo_mundo, i->posicao_y, i->largura, i->altura, 0);
    else {
        printf("erro ao colocar inimigo\n");
        return;
    }
}

struct explosao *cria_explosao(int largura, int altura, int posicao_x, int posicao_y) {
    struct explosao *e = malloc(sizeof(struct explosao));
    if (!e)
        return NULL;

    e->largura = largura;
    e->altura = altura;
    e->posicao_x = posicao_x;
    e->posicao_y = posicao_y;

    e->sprite = al_load_bitmap("Sprites/explosion.png");

    return e;
}

void destroi_explosao(struct explosao *e) {
    if (e) {
        al_destroy_bitmap(e->sprite);
        free(e);
    }
}

void coloca_explosao(struct explosao *e) {
    al_draw_scaled_bitmap(e->sprite, 0, 0, 112, 128, e->posicao_x, e->posicao_y, e->largura, e->altura, 0);
}

void colisao_inimigo(bool *morte_inimigo, struct projetil *pjt, struct inimigo *i, float movendo_mundo, int controle) {
    if (!(*morte_inimigo)) {
        bool colidiu;
        if (controle == 0)
            colidiu = (pjt->posicao_x < i->posicao_x + i->largura + movendo_mundo) && (pjt->posicao_x + pjt->largura > i->posicao_x + movendo_mundo) && (pjt->posicao_y < i->posicao_y + i->altura) && (pjt->posicao_y + pjt->altura > i->posicao_y);
        if (controle == 1)
            colidiu = (pjt->posicao_x < i->posicao_x + (-i->largura) + movendo_mundo) && (pjt->posicao_x + pjt->largura > i->posicao_x + movendo_mundo) && (pjt->posicao_y < i->posicao_y + i->altura) && (pjt->posicao_y + pjt->altura > i->posicao_y);


        if (colidiu) {
            //criando explosão para morte do inimigo:
            struct explosao *e;
            if (controle == 0)
                e = cria_explosao(224, 256, i->posicao_x+movendo_mundo, 410);
            if (controle == 1)
                e = cria_explosao(224, 256, i->posicao_x+movendo_mundo-240, 400);
            coloca_explosao(e);
            destroi_inimigo(i);
            destroi_explosao(e);
            *morte_inimigo = true;
            //colocando velocidade para o projeto ser "destruído" logo após.
            pjt->velocidade = 100;
        }
    }
}

struct inimigo_bird *cria_inimigo_bird(int largura, int altura, int posicao_x, int posicao_y) {
    
    struct inimigo_bird *ib = malloc(sizeof(struct personagem));
    if (!ib)
        return NULL; 
    
    ib->altura = altura;
    ib->largura = largura;
    ib->frame_atual = 0;
    ib->posicao_x = posicao_x;
    ib->posicao_y = posicao_y;

    ib->sprites[0] = al_load_bitmap("Sprites/inimigo4.1.png");
    ib->sprites[1] = al_load_bitmap("Sprites/inimigo4.2.png");
    ib->sprites[2] = al_load_bitmap("Sprites/inimigo4.3.png");
    ib->sprites[3] = al_load_bitmap("Sprites/inimigo4.4.png");
    ib->sprites[4] = al_load_bitmap("Sprites/inimigo4.5.png");

    //Loop para se não existir alguma dessas imagens, encerrar o programa:
    for (int i = 0; i < 5; i++) {
        if (!ib->sprites[i]) {
            printf("Erro ao carregar sprite %d\n", i);
            for (int j = 0; j <= i; j++) {
                if (ib->sprites[j])
                    al_destroy_bitmap(ib->sprites[j]);
            }
            free(ib);
            return NULL;
        }
    }

    return ib;
}

void destroi_inimigo_bird(struct inimigo_bird *ib) {
    if (ib) {
        for (int i = 0; i < 5; i++) {
            if (ib->sprites[i])
                al_destroy_bitmap(ib->sprites[i]);
        }
        free(ib);
    }
}

void coloca_inimigo_bird(struct inimigo_bird *ib, int frame_atual, float movendo_mundo) {
    ib->frame_atual = frame_atual;
    al_draw_scaled_bitmap(ib->sprites[ib->frame_atual], 0, 0, 32, 32, ib->posicao_x+movendo_mundo, ib->posicao_y,ib->largura, ib->altura, 0);
}

void colisao_inimigo_bird(bool *morte_inimigo, struct projetil *pjt, struct inimigo_bird *i, float movendo_mundo) {
    if (!(*morte_inimigo)) {
        bool colidiu;
        colidiu = (pjt->posicao_x < i->posicao_x + i->largura + movendo_mundo) && (pjt->posicao_x + pjt->largura > i->posicao_x + movendo_mundo) && (pjt->posicao_y < i->posicao_y + i->altura) && (pjt->posicao_y + pjt->altura > i->posicao_y);

        if (colidiu) {
            //criando explosão para morte do inimigo:
            struct explosao *e;
            e = cria_explosao(224, 256, i->posicao_x+movendo_mundo-30, 40);
            coloca_explosao(e);
            destroi_inimigo_bird(i);
            destroi_explosao(e);
            *morte_inimigo = true;
            //colocando velocidade para o projeto ser "destruído" logo após.
            pjt->velocidade = 100;
        }
    }
}