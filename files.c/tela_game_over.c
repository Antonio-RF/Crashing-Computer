#include "tela_game_over.h"
#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h> 													//Biblioteca para usar fontes legais.
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

void tela_game_over(ALLEGRO_DISPLAY* disp) {
	al_install_keyboard();	                                                       
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 40.0);					 
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							

	al_register_event_source(queue, al_get_keyboard_event_source());				
	al_register_event_source(queue, al_get_display_event_source(disp));     
	al_register_event_source(queue, al_get_timer_event_source(timer));				

    ALLEGRO_EVENT event;															
	al_start_timer(timer);	

    ALLEGRO_FONT* font = al_load_ttf_font("Pictures/minha_fonte.ttf", 120, 0);
	ALLEGRO_FONT* font2 = al_load_ttf_font("Pictures/minha_fonte.ttf", 50, 0);

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

			al_draw_text(font, al_map_rgb(255, 0, 0), 560, 200, ALLEGRO_ALIGN_CENTER, "SEGMENTATION FAULT");
			
			if (pingando >= 15 && pingando < 30) {
				al_draw_text(font2, al_map_rgb(255, 255, 0), 560, 500, ALLEGRO_ALIGN_CENTER, "Press ENTER to return to the menu");
				pingando++;
			}
			else if (pingando == 30)
				pingando = 0;
			else
				pingando++;

    		
			al_flip_display();														
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			break;											
		
	}

	al_destroy_timer(timer);														
	al_destroy_event_queue(queue);													
	al_destroy_font(font);
	al_destroy_font(font2);

}