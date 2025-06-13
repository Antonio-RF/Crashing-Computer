#ifndef __SECUNDARIAS__
#define __SECUNDARIAS__

#include "entidades.h"
#include<allegro5/allegro.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_image.h>
#include <allegro5/bitmap.h>

void colisao_inimigo(bool *morte_inimigo, struct projetil_personagem *pjt, struct inimigo *i, float movendo_mundo, int controle);

void colisao_inimigo_bird(bool *morte_inimigo, struct projetil_personagem *pjt, struct inimigo_bird *i, float movendo_mundo);

void atira_bird(struct projetil *pjt_bird, float movendo_mundo, int salva);

int colisao_personagem_com_bird(int *count_vida, struct projetil *pjt, struct personagem *p, float movendo_mundo);

int colisao_personagem_com_inimigo2(int *count_vida, struct inimigo *inimigo, struct personagem *p, float movendo_mundo, bool *morte_inimigo_2, int *invencibilidade_frames);

void atira_lobo(struct projetil *pjt_bird, float movendo_mundo, int salva);

int colisao_personagem_com_lobo(bool baixo_pressionado, int *count_vida, struct projetil *pjt, struct personagem *p, float movendo_mundo);

int colisao_inimigo_boss(struct projetil_personagem *pjt, struct inimigo_boss *i, int *count_vidas_boss, bool sentido_positivo_boss);




#endif