//Compilação: gcc main.c -o AS $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_ttf-5 --libs --cflags)

#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h> //Biblioteca para usar fontes legais.
#include <allegro5/events.h>
#include <allegro5/keycodes.h>


int main(){
	al_init();																		//Faz a preparação de requisitos da biblioteca Allegro
	al_install_keyboard();															//Habilita a entrada via teclado (eventos de teclado), no programa

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);					 //Cria o relógio do jogo; isso indica quantas atualizações serão realizadas por segundo (30, neste caso)
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							//Cria a fila de eventos; todos os eventos (programação orientada a eventos) 
	ALLEGRO_DISPLAY* disp = al_create_display(1080, 720);						 //Cria uma janela para o programa, define a largura (x) e a altura (y) da tela em píxeis (320x320, neste caso)

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
	ALLEGRO_BITMAP* background = al_load_bitmap("Pictures/back.png"); 
	//Carregando a fonte que eu desejo e salvando como "font":
	ALLEGRO_FONT* font = al_load_ttf_font("Pictures/minha_fonte.ttf", 110, 0);


	//criando struct que guarda as opções de menu:
	struct estados {
		int MENU;
		int START;
		int SAIR;
	};
	struct estados estado_atual;
	estado_atual.MENU = 1;
	estado_atual.START = 0;
	estado_atual.SAIR = 0;




	while(1){																		//Laço principal do programa
		al_wait_for_event(queue, &event);								//Função que captura eventos da fila, inserindo os mesmos na variável de eventos
		
		//evento de tecla pressionada
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					if (estado_atual.MENU == 1 && estado_atual.START == 0 && estado_atual.SAIR == 0) {
						estado_atual.MENU = 0;
						estado_atual.SAIR = 1;
					}
					else if (estado_atual.MENU == 0 && estado_atual.START == 0 && estado_atual.SAIR == 1) {
						estado_atual.SAIR = 0;
						estado_atual.START = 1;
					}
					else if (estado_atual.MENU == 0 && estado_atual.START == 1 && estado_atual.SAIR == 0) {
						estado_atual.START = 0;
						estado_atual.MENU = 1;
					}
					break;
				case ALLEGRO_KEY_DOWN:
					if (estado_atual.MENU == 1 && estado_atual.START == 0 && estado_atual.SAIR == 0) {
						estado_atual.MENU = 0;
						estado_atual.START = 1;
					}
					else if (estado_atual.MENU == 0 && estado_atual.START == 0 && estado_atual.SAIR == 1) {
						estado_atual.SAIR = 0;
						estado_atual.MENU = 1;
					}
					else if (estado_atual.MENU == 0 && estado_atual.START == 1 && estado_atual.SAIR == 0) {
						estado_atual.START = 0;
						estado_atual.SAIR = 1;
					}
					break;
			}
		}


		//O evento tipo 30 indica um evento de relógio, ou seja, verificação se a tela deve ser atualizada (conceito de FPS)
		if (event.type == ALLEGRO_EVENT_TIMER){		
			//al_draw_bitmap(imagem, x, y, flags);
			al_draw_bitmap(background, 0, 0, 0);
			al_draw_text(font, al_map_rgb(255, 255, 255), 540, 190, ALLEGRO_ALIGN_CENTRE, "START");
			al_draw_text(font, al_map_rgb(0, 255, 255), 540, 290, ALLEGRO_ALIGN_CENTRE, "MENU");
			al_draw_text(font, al_map_rgb(0, 255, 255), 540, 390, ALLEGRO_ALIGN_CENTER, "EXIT");
    		al_flip_display();														//Insere as modificações realizadas nos buffers de tela
		}
		else if (event.type == 42) break;											//Evento de clique no "X" de fechamento da tela. Encerra o programa graciosamente.

		// Exibindo o estado atual
		if (estado_atual.START == 1) {
			al_draw_text(font, al_map_rgb(0, 255, 255), 540, 190, ALLEGRO_ALIGN_CENTRE, "START");
		} 
		else if (estado_atual.MENU == 1) {
			al_draw_text(font, al_map_rgb(0, 255, 255), 540, 290, ALLEGRO_ALIGN_CENTRE, "MENU");
		}
		else if (estado_atual.MENU == 1) {
			al_draw_text(font, al_map_rgb(0, 255, 255), 540, 390, ALLEGRO_ALIGN_CENTER, "EXIT");
		}
		
	}

	al_destroy_font(font);														 //Destrutor da fonte padrão
	al_destroy_display(disp);												 //Destrutor da tela
	al_destroy_timer(timer);														//Destrutor do relógio
	al_destroy_event_queue(queue);													//Destrutor da fila
	al_destroy_bitmap(background);
	al_destroy_font(font);

	return 0;
}