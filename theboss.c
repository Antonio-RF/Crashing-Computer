#include "theboss.h"
#include "entidades.h"
#include "tela_pause.h"
#include <allegro5/allegro5.h>														
#include <allegro5/allegro_font.h>													
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h> 													
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <stdbool.h>

void tela_the_boss(ALLEGRO_DISPLAY* disp) {
    al_install_keyboard();	                                                       
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 40.0);					 
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							

	al_register_event_source(queue, al_get_keyboard_event_source());				
	al_register_event_source(queue, al_get_timer_event_source(timer));			

    ALLEGRO_EVENT event;															
	al_start_timer(timer);	

    ALLEGRO_FONT* font = al_load_ttf_font("Pictures/minha_fonte.ttf", 120, 0);
	ALLEGRO_FONT* font2 = al_load_ttf_font("Pictures/minha_fonte.ttf", 50, 0);

    //background:
    ALLEGRO_BITMAP* background_jogo3 = al_load_bitmap("Pictures/background3.png");

    //criando o meu personagem:
	struct personagem *p = cria_personagem(160, 240, 400, 440);

	//criando projetil:
	struct projetil_personagem *pjt = cria_projetil_personagem(64, 64, 500, p->posicao_y+160, 14);

	//criando arma:
	struct arma *a = cria_arma(-64, 64, 570, p->posicao_y+160, 1);

	//criando boss:
	struct inimigo_boss *boss = cria_inimigo_boss(512, 352, 400, -10);

	//criando os corações que servirão de vida do personagem:
	ALLEGRO_BITMAP *sprite_coracao1 = al_load_bitmap("Sprites/coração.png");
	ALLEGRO_BITMAP *sprite_coracao2 = al_load_bitmap("Sprites/coração.png");
	ALLEGRO_BITMAP *sprite_coracao3 = al_load_bitmap("Sprites/coração.png");
	ALLEGRO_BITMAP *sprite_coracao_preto1 = al_load_bitmap("Sprites/coração_preto.png");
	ALLEGRO_BITMAP *sprite_coracao_preto2 = al_load_bitmap("Sprites/coração_preto.png");
	ALLEGRO_BITMAP *sprite_coracao_preto3 = al_load_bitmap("Sprites/coração_preto.png");

	//criando as barras de vida do inimigo boss:
	ALLEGRO_BITMAP *sprite_barra_coracao_boss = al_load_bitmap("Sprites/barra_coração_boss.png");
	ALLEGRO_BITMAP *sprite_barra_preta = al_load_bitmap("Sprites/barra_preta.png");


	//criando variáveis booleanas para andar:
	bool andando_direita = false;
	bool andando_esquerda = false;

	//criando variáveis para ajudar no pulo:
    float velocidade_y = 0;
    const float chao = 440;
	bool no_ar = false;

	int valor_funcao_pause;
	bool baixo_pressionado;

	//criando variáveis para ajudar no tiro:
	bool atirando = false;
	bool sentido_positivo = true;
	bool controle2 = false;
	int salva_pjt_y = pjt->posicao_y;
	bool atirando_nao_andar_tiro = true;

	//criando variáveis para o boss:
	bool morte_inimigo_boss = false;
	int count_frames_boss = 0;
	bool vida1 = true;
	bool vida2 = true;
	bool vida3 = true;
	bool vida4 = true;
	bool vida5 = true;
	bool vida6 = true;
	bool vida7 = true;
	bool vida8 = true;
	bool vida9 = true;
	bool vida10 = true;
	bool vida11 = true;
	bool vida12 = true;
	bool vida13 = true;
	bool sentido_positivo_boss = false;
	int salva_pos_sentido_boss = 0;


	//cirando variáveis para a vida do personagem:
	int count_vidas = 3;
	bool coracao1 = true;
	bool coracao2 = true;
	bool coracao3 = true;
	bool coracao_boss = true;

	bool controle = true;
    while(controle){																		
		al_wait_for_event(queue, &event);								

		//Evento de pressionar tecla:
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT:
					p->frame_atual = 1;
					a->chave = 1;
					andando_direita = true;
					//conferindo se está virado a esquerda,
					//se estiver, eu viro ele para a direita:
					if (p->largura < 0)
						p->largura *= -1;
					break;
				case ALLEGRO_KEY_LEFT:
					p->frame_atual = 1;
					a->chave = 1;
					//conferindo se está virado a direita,
					//se estiver, eu viro ele para a esquerda:
					if (p->largura > 0)
						p->largura *= -1;
					andando_esquerda = true;
					break;
				case ALLEGRO_KEY_DOWN:
					p->frame_atual = 3;
					a->chave = 0;
					baixo_pressionado = true;
					break;
				case ALLEGRO_KEY_UP:
					if (!no_ar) {
						velocidade_y = -35;
						no_ar = true;
						p->frame_atual = 2;
					}
					a->chave = 0;
					break;
				case ALLEGRO_KEY_SPACE:
					p->frame_atual = 4;
					a->chave = 1;
					if (p->largura < 0)
						sentido_positivo = false;
					if (!atirando) {
						atirando = true;
						if (p->largura > 0)
							pjt->posicao_x = 510;  
						else
							pjt->posicao_x = 210;

						pjt->velocidade = 14;
					}
					break;
				case ALLEGRO_KEY_ESCAPE:
					valor_funcao_pause = tela_pause(disp);
					break;
			}
		}
		//quebrando o loop principal se o valor do pause for MENU:
		if (valor_funcao_pause == 1)
			break;
		else
			al_flush_event_queue(queue);

		//Evento de soltar tecla:
		if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT:
					p->frame_atual = 0;
					andando_direita = false;
					break;
				case ALLEGRO_KEY_LEFT:
					p->frame_atual = 0;
					andando_esquerda = false;
					break;
				case ALLEGRO_KEY_DOWN:
					p->frame_atual = 0;
					a->chave = 1;
					baixo_pressionado = false;
					break;
				case ALLEGRO_KEY_UP:
					p->frame_atual = 0;
					a->chave = 1;
					break;
				case ALLEGRO_KEY_SPACE:
					p->frame_atual = 0;
					a->chave = 1;
					break;
			}
		}
		if (event.type == ALLEGRO_EVENT_TIMER){
			//limpando a tela:
			al_clear_to_color(al_map_rgb(0, 0, 0));		

            //colocando background:
            al_draw_scaled_bitmap(background_jogo3, 0, 0, 352, 224, 0, 0, 1080, 720, 0);

            //colocando meu personagem:
            coloca_personagem(p);

			//colocando the boss:
			if (!morte_inimigo_boss) {
				coloca_inimigo_boss(boss, count_frames_boss);
				count_frames_boss += 5;
				if (count_frames_boss >= 215)
					count_frames_boss = 0;
				
				if (!sentido_positivo_boss) {
					boss->posicao_x -= 4;
					if (boss->posicao_x < -180) {
						boss->largura *= -1;
						sentido_positivo_boss = true;
						boss->posicao_x += 600;
					}
				}
				if (sentido_positivo_boss) {
					boss->posicao_x += 4;
					if (boss->posicao_x > 1250) {
						boss->largura *= -1;
						sentido_positivo_boss = false;
						boss->posicao_x -= 600;
					}
				}
			}

			//Movimentando mundo:
			if (andando_direita && p->posicao_x < 910)
				p->posicao_x += 14;
			if (andando_esquerda && p->posicao_x > 160)
				p->posicao_x -= 14;

			//Aplicando a "gravidade" se o personagem estiver no ar:
			if (no_ar) {
                velocidade_y += 4;
                p->posicao_y += velocidade_y;

                if (p->posicao_y >= chao) {
                    p->posicao_y = chao;
                    velocidade_y = 0;
                    no_ar = false;
                    p->frame_atual = 0;
                }
            }

			//Colocando arma:
			if (a->chave == 1) {
				if (andando_esquerda) {
					if (a->largura > 0)
						a->largura *= -1;
					a->posicao_x = p->posicao_x-100;
					coloca_arma(a);
				}
				else if (andando_direita) {
					if (a->largura < 0)
						a->largura *= -1;
					a->posicao_x = p->posicao_x+100;
					coloca_arma(a);
				}
				else {
					coloca_arma(a);
				}
			}

			//colocando os novos valores das distâncias da arma (para ela andar junto com o personagem):
			if (p->largura > 0 && atirando_nao_andar_tiro)
				pjt->posicao_x = p->posicao_x + 100;
			if (p->largura < 0 && atirando_nao_andar_tiro) {
				pjt->posicao_x = p->posicao_x - 175;
			}

			//Colocando disparo:
			if (atirando) {
				atirando_nao_andar_tiro = false;
				if (sentido_positivo) 
					pjt->velocidade += 4;
				else
					pjt->velocidade -= 4;
				


				if (!controle2) {
					if (sentido_positivo)
						pjt->posicao_y -= pjt->velocidade;
					else
						pjt->posicao_y += pjt->velocidade;
					controle2 = true;
				}
				else if (controle2) {
					if (sentido_positivo)
						pjt->posicao_y -= pjt->velocidade;
					else
						pjt->posicao_y += pjt->velocidade;
				}
				else if (controle2) {
					if (sentido_positivo)
						pjt->posicao_y -= pjt->velocidade;
					else
						pjt->posicao_y += pjt->velocidade;
				}


				coloca_projetil_personagem(pjt);

				//impacto inimigo boss:
				//espaço para colocar <>

				if ((pjt->velocidade >= 100 || pjt->velocidade <= -72)) {
					atirando = false;
					sentido_positivo = true;
					controle2 = false;
					pjt->posicao_y = salva_pjt_y;
					atirando_nao_andar_tiro = true;
				}
			}

			//Colocando corações:
			if (coracao1)
				al_draw_scaled_bitmap(sprite_coracao1, 0,0,1024,1024, 20, 0, 80, 80, 0);
			else
				al_draw_scaled_bitmap(sprite_coracao_preto1, 0,0,1024,1024, 20, 0, 80, 80, 0);
			if (coracao2)
				al_draw_scaled_bitmap(sprite_coracao2, 0,0,1024,1024, 100, 0, 80, 80, 0);
			else 
				al_draw_scaled_bitmap(sprite_coracao_preto2, 0,0,1024,1024, 100, 0, 80, 80, 0);
			if (coracao3)
				al_draw_scaled_bitmap(sprite_coracao3, 0,0,1024,1024, 180, 0, 80, 80, 0);
			else 
				al_draw_scaled_bitmap(sprite_coracao_preto3, 0,0,1024,1024, 180, 0, 80, 80, 0);
			
			//Colocando corações do boss:
			if (sprite_barra_coracao_boss)
				al_draw_scaled_bitmap(sprite_barra_coracao_boss, 0,0,500,500, 740, -130, 350, 350, 0);
			
			//vidas perdidas do inimigo boss:
			//if (!vida1)
			al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 1020, 15, 40, 65, 0);
			if (!vida2)
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 1000, 15, 40, 65, 0);
			if (!vida3)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 980, 15, 40, 65, 0);
			if (!vida4)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 958, 15, 40, 65, 0);
			if (!vida5)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 938, 15, 40, 65, 0);
			if (!vida6)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 915, 15, 40, 65, 0);
			if (!vida7)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 895, 15, 40, 65, 0);
			if (!vida8)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 875, 15, 40, 65, 0);
			if (!vida9)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 853, 15, 40, 65, 0);
			if (!vida10)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 833, 15, 40, 65, 0);
			if (!vida11)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 813, 15, 40, 65, 0);
			if (!vida12)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 790, 15, 40, 65, 0);
			if (!vida13)	
				al_draw_scaled_bitmap(sprite_barra_preta, 0,0,500,500, 770, 15, 40, 65, 0);
    		
			al_flip_display();														
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			break;											
		
	}

	al_destroy_timer(timer);														
	al_destroy_event_queue(queue);													
	al_destroy_font(font);

}