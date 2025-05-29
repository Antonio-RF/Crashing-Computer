#include "display.h"
#include <allegro5/display.h>

struct display *cria_display() {

    //Obtendo informações da tela do usuário:
    ALLEGRO_DISPLAY_MODE *infos = malloc(sizeof(ALLEGRO_DISPLAY_MODE));
    if (!infos)
        exit(1);
    al_get_display_mode(0, infos);

    //Definindo que a janela que será criada será FULLSCREEN:
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    //criando novo display e inicializando ele:
    struct display *d = malloc(sizeof(struct display));
    d->disp = al_create_display(infos->width, infos->height);
    d->largura = infos->width;
    d->altura = infos->height;

    free(infos);

    return d;
}

