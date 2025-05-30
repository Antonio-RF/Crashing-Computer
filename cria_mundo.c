#include "cria_mundo.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>                                                   //Biblioteca para usar fontes legais.
#include <allegro5/events.h>
#include <allegro5/keycodes.h>



void cria_mundo(ALLEGRO_DISPLAY* disp) {

    al_init();																		//Faz a preparação de requisitos da biblioteca Allegro
    al_init_primitives_addon();
	al_install_keyboard();	                                                        //Habilita a entrada via teclado (eventos de teclado), no programa

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);					 //Cria o relógio do jogo; isso indica quantas atualizações serão realizadas por segundo (30, neste caso)
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							//Cria a fila de eventos; todos os eventos (programação orientada a eventos) 

	al_register_event_source(queue, al_get_keyboard_event_source());				//Indica que eventos de teclado serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_display_event_source(disp));     //Indica que eventos de tela serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_timer_event_source(timer));				//Indica que eventos de relógio serão inseridos na nossa fila de eventos

	ALLEGRO_EVENT event;															//Variável que guarda um evento capturado, sua estrutura é definida em: https://www.allegro.cc/manual/5/ALLEGRO_EVENT
	al_start_timer(timer);															//Função que inicializa o relógio do programa

	//Inicializando o addon de imagens:
	al_init_image_addon();
	//Inificaçizando o addon de fontes:
	al_init_ttf_addon();

	//Carregando a imagem e salvando ela como "background":
	ALLEGRO_BITMAP* background_jogo = al_load_bitmap("Pictures/bulkhead-wallsx3.png"); 

    bool moving_right = false;
    bool moving_left = false;

    while(1){																		//Laço principal do programa
		al_wait_for_event(queue, &event);

        //Função que captura eventos da fila, inserindo os mesmos na variável de eventos
        if (event.type == ALLEGRO_EVENT_TIMER){
			//limpando a tela:
			al_clear_to_color(al_map_rgb(0, 0, 0));		
            al_draw_scaled_bitmap(background_jogo, 0, 0, 1056, 672, 0, 0, 1080, 720,0);
            al_flip_display();	

            // Atualiza a tela
            al_flip_display();
        }																																																				//Indica o evento correspondente no controle do segundo jogador (botão de movimentação para baixo) (!)
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			break;
    }

    al_destroy_display(disp);												 //Destrutor da tela
	al_destroy_timer(timer);														//Destrutor do relógio
	al_destroy_event_queue(queue);													//Destrutor da fila
	al_destroy_bitmap(background_jogo);


}