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

struct projetil_personagem *cria_projetil_personagem(int largura, int altura, int posicao_x, int posicao_y, int velocidade) {
    struct projetil_personagem *pjt = malloc(sizeof(struct projetil_personagem));
    if (!pjt)
        return NULL;

    pjt->largura = largura;
    pjt->altura = altura;
    pjt->posicao_x = posicao_x;
    pjt->posicao_y = posicao_y;
    pjt->velocidade = velocidade;

    pjt->sprite = al_load_bitmap("Sprites/hit_personagem.png");
    if (!pjt->sprite) {
        printf("erro ao carregar sprite do hit do personagem\n");
        return NULL;
    }

    return pjt;
}

void destroi_projetil_personagem(struct projetil_personagem *pjt) {
    if (pjt) {
        al_destroy_bitmap(pjt->sprite);
        free(pjt);
    }
}

void coloca_projetil_personagem(struct projetil_personagem *pjt) {
    al_draw_scaled_bitmap(pjt->sprite, 0,0,1024,1024, pjt->posicao_x, pjt->posicao_y, pjt->largura, pjt->altura, 0);
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
    if (i == NULL)
        return;
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

void colisao_inimigo(bool *morte_inimigo, struct projetil_personagem *pjt, struct inimigo *i, float movendo_mundo, int controle) {
    if (!(*morte_inimigo) && i != NULL) {
        bool colidiu;
        if (controle == 0)
            colidiu = (pjt->posicao_x < i->posicao_x + i->largura + movendo_mundo) && (pjt->posicao_x + pjt->largura > i->posicao_x + movendo_mundo) && (pjt->posicao_y < i->posicao_y + i->altura) && (pjt->posicao_y + pjt->altura > i->posicao_y);
        if (controle == 1 || controle == 2)
            colidiu = (pjt->posicao_x < i->posicao_x + (-i->largura) + movendo_mundo) && (pjt->posicao_x + pjt->largura > i->posicao_x + movendo_mundo) && (pjt->posicao_y < i->posicao_y + i->altura) && (pjt->posicao_y + pjt->altura > i->posicao_y);


        if (colidiu) {
            //criando explosão para morte do inimigo:
            struct explosao *e;
            if (controle == 0)
                e = cria_explosao(224, 256, i->posicao_x+movendo_mundo, 410);
            if (controle == 1)
                e = cria_explosao(224, 256, i->posicao_x+movendo_mundo-240, 400);
            if (controle == 2)
                e = cria_explosao(336, 384, i->posicao_x+movendo_mundo-320, 300);
            coloca_explosao(e);
            destroi_explosao(e);
            *morte_inimigo = true;
            //colocando velocidade para o projeto ser "destruído" logo após.
            pjt->velocidade = 100;
        }
    }
}

struct inimigo_bird *cria_inimigo_bird(int largura, int altura, int posicao_x, int posicao_y) {
    
    struct inimigo_bird *ib = malloc(sizeof(struct inimigo_bird));
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
    int temp;
    temp = frame_atual / 16;
    al_draw_scaled_bitmap(ib->sprites[temp], 0, 0, 32, 32, ib->posicao_x+movendo_mundo, ib->posicao_y,ib->largura, ib->altura, 0);
}

void colisao_inimigo_bird(bool *morte_inimigo, struct projetil_personagem *pjt, struct inimigo_bird *i, float movendo_mundo) {
    if (!(*morte_inimigo)) {
        bool colidiu;
        colidiu = (pjt->posicao_x < i->posicao_x + i->largura + movendo_mundo) && (pjt->posicao_x + pjt->largura > i->posicao_x + movendo_mundo) && (pjt->posicao_y < i->posicao_y + i->altura) && (pjt->posicao_y + pjt->altura > i->posicao_y);

        if (colidiu) {
            //criando explosão para morte do inimigo:
            struct explosao *e;
            e = cria_explosao(224, 256, i->posicao_x+movendo_mundo-30, 40);
            coloca_explosao(e);
            //destroi_inimigo_bird(i);
            destroi_explosao(e);
            *morte_inimigo = true;
            //colocando velocidade para o projeto ser "destruído" logo após.
            pjt->velocidade = 100;
        }
    }
}

void coloca_projetil_bird(struct projetil *pjt, float movendo_mundo, int adicao_y) {
    al_draw_scaled_bitmap(pjt->sprite, 0,0,16,16, pjt->posicao_x+movendo_mundo, pjt->posicao_y+adicao_y, pjt->largura, pjt->altura, 0);
}

void atira_bird(struct projetil *pjt_bird, float movendo_mundo, int salva) {
    pjt_bird->velocidade += 4;
    pjt_bird->posicao_y += pjt_bird->velocidade;
    coloca_projetil_bird(pjt_bird, movendo_mundo+40, 40);
    if (pjt_bird->velocidade >= 300) {
        pjt_bird->posicao_y = salva;
        pjt_bird->velocidade = 14;
    }
}

int colisao_personagem_com_bird(int *count_vida, struct projetil *pjt, struct personagem *p, float movendo_mundo) {
    // Ajustando a posição do projétil considerando o movimento do mundo e a posição do pjt_bird (+40 tanto no x quanto no y):
    if (pjt == NULL || p == NULL)
        return -1;
    
    // Se ele estiver no sentido esquerda para direita, muda largura para negativo:
    int p_largura_abs;
    if (p->largura < 0)
        p_largura_abs = -p->largura;
    else
        p_largura_abs = p->largura;

    // Definindo a posição X real do personagem:
    float p_x_efetivo;
    if (p->largura < 0)
        p_x_efetivo = p->posicao_x + p->largura;
    else
        p_x_efetivo = p->posicao_x;

    float proj_x = pjt->posicao_x + movendo_mundo + 40;
    float proj_y = pjt->posicao_y + 40;
    
     bool colidiu = (proj_x < p_x_efetivo + p_largura_abs) && (proj_x + pjt->largura > p_x_efetivo) && (proj_y < p->posicao_y + p->altura) && (proj_y + pjt->altura > p->posicao_y);

    if (colidiu && pjt->velocidade < 100) {
        if (*count_vida > 0) {
            (*count_vida)--;
            
            // "Destrói" o projétil
            pjt->velocidade = 100;
            
            // Retorna o novo valor de vida
            return *count_vida;
        }
    }
    return -1; // Retorna -1 quando não há colisão ou quando o personagem já está sem vida
}

int colisao_personagem_com_inimigo2(int *count_vida, struct inimigo *inimigo, struct personagem *p, float movendo_mundo, bool *morte_inimigo_2, int *invencibilidade_frames) {
    if (inimigo == NULL || p == NULL)
        return -1;
    
    // Se ele estiver no sentido esquerda para direita, muda largura para negativo:
    int p_largura_abs;
    if (p->largura < 0)
        p_largura_abs = -p->largura;
    else
        p_largura_abs = p->largura;

    // Definindo a posição X real do personagem:
    float p_x_efetivo;
    if (p->largura < 0)
        p_x_efetivo = p->posicao_x + p->largura;
    else
        p_x_efetivo = p->posicao_x;


    bool colidiu = (p_x_efetivo < inimigo->posicao_x + (-inimigo->largura) + movendo_mundo) && (p_x_efetivo + p_largura_abs > inimigo->posicao_x + movendo_mundo) && (p->posicao_y < inimigo->posicao_y + inimigo->altura) && (p->posicao_y + p->altura > inimigo->posicao_y);
    
    if (colidiu) {
        if (*count_vida > 0) {
            (*count_vida)--;
            *invencibilidade_frames = 30;
        }
        *morte_inimigo_2 = true;
        return *count_vida;
    }
    return -1;
}

void coloca_projetil_lobo(struct projetil *pjt, float movendo_mundo) {
    al_draw_scaled_bitmap(pjt->sprite, 0,0,16,16, pjt->posicao_x+movendo_mundo-310, pjt->posicao_y+180, pjt->largura, pjt->altura, 0);
}

void atira_lobo(struct projetil *pjt_lobo, float movendo_mundo, int salva) {
    pjt_lobo->posicao_x -= pjt_lobo->velocidade;
    coloca_projetil_lobo(pjt_lobo, movendo_mundo+40);
    if (pjt_lobo->posicao_x <= -300) {
        pjt_lobo->posicao_x = salva;
        pjt_lobo->velocidade = 15;
    }
}

int colisao_personagem_com_lobo(bool baixo_pressionado, int *count_vida, struct projetil *pjt, struct personagem *p, float movendo_mundo) {
    // Ajustando a posição do projétil considerando o movimento do mundo e a posição do pjt_bird (+40 tanto no x quanto no y):
    if (pjt == NULL || p == NULL)
        return -1;
    
    if (baixo_pressionado)
        return -1;

    // Se ele estiver no sentido esquerda para direita, muda largura para negativo:
    int p_largura_abs;
    if (p->largura < 0)
        p_largura_abs = -p->largura;
    else
        p_largura_abs = p->largura;

    // Definindo a posição X real do personagem:
    float p_x_efetivo;
    if (p->largura < 0)
        p_x_efetivo = p->posicao_x + p->largura;
    else
        p_x_efetivo = p->posicao_x;

    float proj_x = pjt->posicao_x + movendo_mundo - 310;
    float proj_y = pjt->posicao_y + 180;
    
    bool colidiu = (proj_x < p_x_efetivo + p_largura_abs) && (proj_x + pjt->largura > p_x_efetivo) && (proj_y < p->posicao_y + p->altura) && (proj_y + pjt->altura > p->posicao_y);

    if (colidiu && pjt->velocidade < 100) {
        if (*count_vida > 0) {
            (*count_vida)--;
            
            // "Destrói" o projétil
            pjt->velocidade = 100;
            
            // Retorna o novo valor de vida
            return *count_vida;
        }
    }
    return -1; // Retorna -1 quando não há colisão ou quando o personagem já está sem vida
}

struct inimigo_boss *cria_inimigo_boss(int largura, int altura, int posicao_x, int posicao_y) {
    
    struct inimigo_boss *boss = malloc(sizeof(struct inimigo_boss));
    if (!boss)
        return NULL; 
    
    boss->altura = altura;
    boss->largura = largura;
    boss->frame_atual = 0;
    boss->posicao_x = posicao_x;
    boss->posicao_y = posicao_y;

    boss->sprites[0] = al_load_bitmap("Sprites/theboss1.png");
    boss->sprites[1] = al_load_bitmap("Sprites/theboss2.png");
    boss->sprites[2] = al_load_bitmap("Sprites/theboss3.png");
    boss->sprites[3] = al_load_bitmap("Sprites/theboss4.png");
    boss->sprites[4] = al_load_bitmap("Sprites/theboss5.png");
    boss->sprites[5] = al_load_bitmap("Sprites/theboss6.png");

    //Loop para se não existir alguma dessas imagens, encerrar o programa:
    for (int i = 0; i < 6; i++) {
        if (!boss->sprites[i]) {
            printf("Erro ao carregar sprite %d\n", i);
            for (int j = 0; j <= i; j++) {
                if (boss->sprites[j])
                    al_destroy_bitmap(boss->sprites[j]);
            }
            free(boss);
            return NULL;
        }
    }

    return boss;
}

void destroi_inimigo_boss(struct inimigo_boss *boss) {
    if (boss) {
        for (int i = 0; i < 5; i++) {
            if (boss->sprites[i])
                al_destroy_bitmap(boss->sprites[i]);
        }
        free(boss);
    }
}

void coloca_inimigo_boss(struct inimigo_boss *boss, int frame_atual) {
    boss->frame_atual = frame_atual;
    int temp;
    temp = frame_atual / 36;
    if (temp >= 6)
        temp = 5;
    al_draw_scaled_bitmap(boss->sprites[temp], 0, 0, 256, 176, boss->posicao_x, boss->posicao_y,boss->largura, boss->altura, 0);
}