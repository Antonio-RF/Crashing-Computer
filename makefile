# Nome do executável
EXEC = arf24

# Fontes
SRC = main.c cria_mundo.c cria_mundo2.c entidades.c tela_game_over.c tela_pause.c theboss.c secundarias.c tela_win.c

# Bibliotecas Allegro
ALLEGRO_FLAGS = $(shell pkg-config --libs --cflags allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_primitives-5)

# Compilador
CC = gcc

# Regras
all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(SRC) -o $(EXEC) $(ALLEGRO_FLAGS)

clean:
	rm -f $(EXEC)
