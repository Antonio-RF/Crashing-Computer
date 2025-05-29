#ifndef __DISPLAY__
#define __DISPLAY__

#include<allegro5/allegro.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_image.h>

struct display {
    int altura;
    int largura;
    ALLEGRO_DISPLAY *disp;
};


struct display *cria_display();


#endif



