#include "tela_pause.h"
#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h> //Biblioteca para usar fontes legais.
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

int tela_pause(ALLEGRO_DISPLAY* disp) {	                                                        

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 40.0);					
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							 

	al_register_event_source(queue, al_get_keyboard_event_source());				
	al_register_event_source(queue, al_get_display_event_source(disp));    
	al_register_event_source(queue, al_get_timer_event_source(timer));				

    ALLEGRO_EVENT event;															
	al_start_timer(timer);	

    ALLEGRO_FONT* font = al_load_ttf_font("Pictures/minha_fonte.ttf", 250, 0);
	ALLEGRO_FONT* font2 = al_load_ttf_font("Pictures/minha_fonte.ttf", 50, 0);

    struct estados estado_atual;
    estado_atual.MENU = 1;
    estado_atual.BACK = 0;

	bool controle = true;
    while(controle){																		
		al_wait_for_event(queue, &event);								

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				//SETA PARA CIMA ↑:
                case ALLEGRO_KEY_UP:
                    if (estado_atual.MENU == 1 && estado_atual.BACK == 0) {
                        estado_atual.MENU = 0;
                        estado_atual.BACK = 1;
                    }
                    else {
                        estado_atual.MENU = 1;
                        estado_atual.BACK = 0;
                    }
                    break;
                case ALLEGRO_KEY_DOWN:
                    if (estado_atual.MENU == 1 && estado_atual.BACK == 0) {
                        estado_atual.MENU = 0;
                        estado_atual.BACK = 1;
                    }
                    else {
                        estado_atual.MENU = 1;
                        estado_atual.BACK = 0;
                    }
                    break;
                //ENTER:
				case ALLEGRO_KEY_ENTER:
                    if (estado_atual.MENU == 1 && estado_atual.BACK == 0) {
                        al_destroy_timer(timer);														
	                    al_destroy_event_queue(queue);
	                    al_destroy_font(font);
                        return 1;
                    }
                    if (estado_atual.MENU == 0 && estado_atual.BACK == 1) {
                        al_destroy_timer(timer);														
	                    al_destroy_event_queue(queue);
	                    al_destroy_font(font);
                        return 2;
                    }
					break;
			}
		}

		if (event.type == ALLEGRO_EVENT_TIMER){
			//limpando a tela:
			al_clear_to_color(al_map_rgb(0, 0, 0));		

			al_draw_text(font, al_map_rgb(0, 0, 255), 560, 100, ALLEGRO_ALIGN_CENTER, "PAUSE");


            if (estado_atual.MENU == 1)
                al_draw_text(font2, al_map_rgb(0, 255, 0), 560, 400, ALLEGRO_ALIGN_CENTER, "MENU");
            else
                al_draw_text(font2, al_map_rgb(255, 255, 255), 560, 400, ALLEGRO_ALIGN_CENTER, "MENU");

            if (estado_atual.BACK == 1)
                al_draw_text(font2, al_map_rgb(0, 255, 0), 560, 450, ALLEGRO_ALIGN_CENTER, "BACK");
            else
                al_draw_text(font2, al_map_rgb(255, 255, 255), 560, 450, ALLEGRO_ALIGN_CENTER, "BACK");


			al_flip_display();														
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			break;											
		
	}
    al_destroy_timer(timer);														
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    al_destroy_font(font2);
    return 0;
}