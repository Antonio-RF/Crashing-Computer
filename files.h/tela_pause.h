#ifndef __PAUSE__
#define __PAUSE__

#include<allegro5/allegro.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_image.h>

struct estados {
		int MENU;
		int BACK;
};

int tela_pause(ALLEGRO_DISPLAY* disp);

#endif