#include "entidades.h"
#include "secundarias.h"
#include <stdio.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>                                                   //Biblioteca para usar fontes legais.
#include <allegro5/bitmap.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

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

int colisao_inimigo_boss(struct projetil_personagem *pjt, struct inimigo_boss *i, int *count_vidas_boss, bool sentido_positivo_boss) {
    if (!pjt->ativo)
        return -1;

    int largura_real;

    largura_real = abs(i->largura);

    int x_real = i->posicao_x;
    if (i->largura < 0) {
        x_real = i->posicao_x + i->largura; // largura negativa -> ajusta x
        largura_real = -i->largura;
    }

    bool colidiu;
    colidiu = (pjt->posicao_x < x_real + largura_real - 140) && (pjt->posicao_x + pjt->largura > x_real + 140) && (pjt->posicao_y < i->posicao_y + i->altura - 140) && (pjt->posicao_y + pjt->altura > i->posicao_y + 140);

    if (colidiu) {
        pjt->ativo = false;
        if (*count_vidas_boss > 0)
            (*count_vidas_boss)--;
        
        if (*count_vidas_boss == 1) {
            struct explosao *e;
            e = cria_explosao(896, 1024, i->posicao_x-120, i->posicao_y-350);
            coloca_explosao(e);
            destroi_inimigo_boss(i);
            destroi_explosao(e);
        }

        return *count_vidas_boss;

    }
    return -1;
}

