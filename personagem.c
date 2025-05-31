#include "personagem.h"
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