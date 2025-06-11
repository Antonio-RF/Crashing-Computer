#include "theboss.h"
#include "entidades.h"
#include "tela_pause.h"
#include <allegro5/allegro5.h>														
#include <allegro5/allegro_font.h>													
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h> 													
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

    		
			al_flip_display();														
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			break;											
		
	}

	al_destroy_timer(timer);														
	al_destroy_event_queue(queue);													
	al_destroy_font(font);

}