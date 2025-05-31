#ifndef __PERSONAGEM__
#define __PERSONAGEM__

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


#endif
