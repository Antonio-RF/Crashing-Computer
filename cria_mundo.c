#include "cria_mundo.h"
#include "personagem.h"
#include <stdio.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>                                                   //Biblioteca para usar fontes legais.
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

void cria_mundo(ALLEGRO_DISPLAY* disp) {

    al_init_primitives_addon();
	al_install_keyboard();	                                                        //Habilita a entrada via teclado (eventos de teclado), no programa

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 40.0);					 //Cria o relógio do jogo; isso indica quantas atualizações serão realizadas por segundo (30, neste caso)
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							//Cria a fila de eventos; todos os eventos (programação orientada a eventos) 

	al_register_event_source(queue, al_get_keyboard_event_source());				//Indica que eventos de teclado serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_display_event_source(disp));     //Indica que eventos de tela serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_timer_event_source(timer));				//Indica que eventos de relógio serão inseridos na nossa fila de eventos

	ALLEGRO_EVENT event;
	//Função que inicializa o relógio do programa:															
	al_start_timer(timer);
	//Inicializando o addon de imagens:
	al_init_image_addon();
	//Inificaçizando o addon de fontes:
	al_init_ttf_addon();

	//Carregando a fonte:
	ALLEGRO_FONT* font = al_load_ttf_font("Pictures/minha_fonte3.ttf", 80, 0);

	//Carregando a imagem e salvando ela como "background":
	ALLEGRO_BITMAP* background_jogo = al_load_bitmap("Pictures/bulkhead-wallsx3.png"); 
	ALLEGRO_BITMAP* background_jogo2 = al_load_bitmap("Pictures/lava-background-preview.png");


	//criando o meu personagem:
	struct personagem *p = cria_personagem(160, 240, 400, 340);


	//criando variáveis booleanas para andar:
	bool andando_direita = false;
	bool andando_esquerda = false;

	//criando variável para mover o mundo:
	float movendo_mundo = 0;

	//criando variáveis para ajudar no pulo:
    float velocidade_y = 0;
    const float chao = 340;
	bool no_ar = false;

//-----------------------------------------------------------------------------------------------------------------------------------------------------//
//LOOP PRINCIPAL:
	bool controle = true;
	//Laço principal do programa:
    while(controle){
		al_wait_for_event(queue, &event);

		//Evento de pressionar tecla:
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT:
					p->frame_atual = 1;
					andando_direita = true;
					//conferindo se está virado a esquerda,
					//se estiver, eu viro ele para a direita:
					if (p->largura < 0)
						p->largura *= -1;
					break;
				case ALLEGRO_KEY_LEFT:
					p->frame_atual = 1;
					//conferindo se está virado a direita,
					//se estiver, eu viro ele para a esquerda:
					if (p->largura > 0)
						p->largura *= -1;
					andando_esquerda = true;
					break;
				case ALLEGRO_KEY_DOWN:
					p->frame_atual = 3;
					break;
				case ALLEGRO_KEY_UP:
					if (!no_ar) {
						velocidade_y = -35;
						no_ar = true;
						p->frame_atual = 2;
					}
					break;
			}
		}
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
					break;
				case ALLEGRO_KEY_UP:
					p->frame_atual = 0;
					break;
			}
		}
        //Evento que captura eventos da fila, inserindo os mesmos na variável de eventos:
        if (event.type == ALLEGRO_EVENT_TIMER){
			//limpando a tela:
			al_clear_to_color(al_map_rgb(0, 0, 0));		

			//Movimentando mundo:
			if (andando_direita)
				movendo_mundo -= 14;
			if (andando_esquerda)
				movendo_mundo += 14;

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
            
			//Desenhando tela de fundo multuplicada por 6:
			double posicao;
			for (int i = 0; i < 6; i++) {
				posicao = movendo_mundo + i * 1080;
				al_draw_scaled_bitmap(background_jogo, 0, 0, 1056, 672, posicao, 0, 1080, 720, 0);
			}
			for (int i = 0; i < 6; i++) {
				posicao = movendo_mundo + (i+6) * 1080;
				al_draw_scaled_bitmap(background_jogo2, 0, 0, 432, 240, posicao, 0, 1080, 720, 0);
			}

			//Colando variável que representa minha kilometragem:
			char texto_posicao[50];
			sprintf(texto_posicao, "KM: %.0f", -movendo_mundo);
			al_draw_text(font, al_map_rgb(255, 255, 0), 150, 20, ALLEGRO_ALIGN_CENTER, texto_posicao);
			
			//condição de parada do meu jogo:
			//if (-movendo_mundo > 5000)
			//	break;

			//Colocando personagem:
			coloca_personagem(p);

            // Atualiza a tela:
            al_flip_display();
        }																																																				//Indica o evento correspondente no controle do segundo jogador (botão de movimentação para baixo) (!)
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			controle = false;
    }
//-----------------------------------------------------------------------------------------------------------------------------------------------------//

	destroi_personagem(p);
	al_destroy_timer(timer);														//Destrutor do relógio
	al_destroy_event_queue(queue);													//Destrutor da fila
	al_destroy_bitmap(background_jogo);
	al_destroy_bitmap(background_jogo2);
	al_destroy_font(font);
}