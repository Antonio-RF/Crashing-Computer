#include "theboss.h"
#include "entidades.h"
#include <allegro5/allegro5.h>														
#include <allegro5/allegro_font.h>													
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h> 													
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

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

	bool controle = true;
	int pingando = 0;
    while(controle){																		
		al_wait_for_event(queue, &event);								

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				//ENTER:
				case ALLEGRO_KEY_ENTER:
					controle = false;
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

    		
			al_flip_display();														
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			break;											
		
	}

	al_destroy_timer(timer);														
	al_destroy_event_queue(queue);													
	al_destroy_font(font);

}