# Nome do executável
EXEC = arf24

# Fontes
SRC = files.c/main.c files.c/cria_mundo.c files.c/cria_mundo2.c files.c/entidades.c files.c/tela_game_over.c files.c/tela_pause.c files.c/theboss.c files.c/secundarias.c files.c/tela_win.c

# Bibliotecas Allegro
ALLEGRO_FLAGS = $(shell pkg-config --libs --cflags allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_primitives-5)

# Compilador
CC = gcc

# Regras
all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(SRC) -Ifiles.h -o $(EXEC) $(ALLEGRO_FLAGS)

clean:
	rm -f $(EXEC)
