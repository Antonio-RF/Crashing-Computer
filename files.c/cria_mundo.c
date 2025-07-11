#include "cria_mundo.h"
#include "cria_mundo2.h"
#include "entidades.h"
#include "tela_game_over.h"
#include "tela_pause.h"
#include "cria_mundo2.h"
#include "secundarias.h"
#include <stdio.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>                                                   //Biblioteca para usar fontes legais.
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

void cria_mundo(ALLEGRO_DISPLAY* disp) {

    al_init_primitives_addon();
	al_install_keyboard();	                                                        //Habilita a entrada via teclado (eventos de teclado), no programa

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 40.0);					 //Cria o relógio do jogo; isso indica quantas atualizações serão realizadas por segundo (30, neste caso)
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							//Cria a fila de eventos; todos os eventos (programação orientada a eventos) 

	al_register_event_source(queue, al_get_keyboard_event_source());				//Indica que eventos de teclado serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_display_event_source(disp));     //Indica que eventos de tela serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_timer_event_source(timer));				//Indica que eventos de relógio serão inseridos na nossa fila de eventos

	ALLEGRO_EVENT event;
	//Função que inicializa o relógio do programa:															
	al_start_timer(timer);
	//Inicializando o addon de imagens:
	al_init_image_addon();
	//Inificaçizando o addon de fontes:
	al_init_ttf_addon();

	//Carregando a fonte:
	ALLEGRO_FONT* font = al_load_ttf_font("Pictures/minha_fonte3.ttf", 80, 0);

	//Carregando a imagem e salvando ela como "background":
	ALLEGRO_BITMAP* background_jogo = al_load_bitmap("Pictures/bulkhead-wallsx3.png"); 	
	//criando o meu personagem:
	struct personagem *p = cria_personagem(160, 240, 400, 340);

	//criando arma:
	struct arma *a = cria_arma(-64, 64, 570, 500, 1);

	//criando projetil:
	struct projetil_personagem *pjt = cria_projetil_personagem(64, 64, 500, p->posicao_y+160, 14);

	//inimigos lobos:
	struct inimigo *inimigo3 = cria_inimigo(-432, 342, 11400, 250, 3);
	struct inimigo *inimigo8 = cria_inimigo(-432, 342, 5000, 250, 3);

	//criando inimigos "lesmas":
	struct inimigo *inimigo2 = cria_inimigo(-160, 128, 4000, 460, 2);
	struct inimigo *inimigo4 = cria_inimigo(-160, 128, 7000, 460, 2);
	struct inimigo *inimigo5 = cria_inimigo(-160, 128, 9000, 460, 2);
	struct inimigo *inimigo6 = cria_inimigo(-160, 128, 11000, 460, 2);
	struct inimigo *inimigo7 = cria_inimigo(-160, 128, 11200, 460, 2);

	//criando inimigos "birds":
	struct inimigo_bird *inimigo_bird = cria_inimigo_bird(128, 128, 1000, 100);
	struct inimigo_bird *inimigo_bird2 = cria_inimigo_bird(128, 128, 10000, 100);
	struct inimigo_bird *inimigo_bird3 = cria_inimigo_bird(128, 128, 6000, 100);

	//criando projetil dos birds:
	struct projetil *pjt_bird = cria_projetil(64, 64, 1000, 100, 14, 0);
	struct projetil *pjt_bird2 = cria_projetil(64, 64, 10000, 100, 14, 0);
	struct projetil *pjt_bird3 = cria_projetil(64, 64, 6000, 100, 14, 0);

	//criando projeteis dos inimigos lobos:
	struct projetil *pjt_lobo = cria_projetil(64, 64, 11400, 250, 15, 0);
	struct projetil *pjt_lobo2 = cria_projetil(64, 64, 5000, 250, 15, 0);

	//criando os corações que servirão de vida:
	ALLEGRO_BITMAP *sprite_coracao1 = al_load_bitmap("Sprites/coração.png");
	ALLEGRO_BITMAP *sprite_coracao2 = al_load_bitmap("Sprites/coração.png");
	ALLEGRO_BITMAP *sprite_coracao3 = al_load_bitmap("Sprites/coração.png");
	ALLEGRO_BITMAP *sprite_coracao_preto1 = al_load_bitmap("Sprites/coração_preto.png");
	ALLEGRO_BITMAP *sprite_coracao_preto2 = al_load_bitmap("Sprites/coração_preto.png");
	ALLEGRO_BITMAP *sprite_coracao_preto3 = al_load_bitmap("Sprites/coração_preto.png");

	//criando portal de final:
	ALLEGRO_BITMAP *sprite_portal = al_load_bitmap("Sprites/portal.png");

	//criando variáveis booleanas para andar:
	bool andando_direita = false;
	bool andando_esquerda = false;

	//criando variável para mover o mundo:
	float movendo_mundo = 0;

	//criando variáveis para ajudar no pulo:
    float velocidade_y = 0;
    const float chao = 340;
	bool no_ar = false;
	bool pulando = false;

	//criando variáveis para ajudar no tiro:
	bool atirando = false;
	bool sentido_positivo = true;
	bool cima = false;
	bool controle2 = false;
	int salva_pjt_y = pjt->posicao_y;

	//criando variáveis para ajudar no impacto:
	int pos_inimigo2 = inimigo2->posicao_x;
	bool morte_inimigo_2 = false;
	int pos_inimigo3 = inimigo3->posicao_x;
	bool morte_inimigo_3 = false;
	int pos_inimigo4 = inimigo4->posicao_x;
	bool morte_inimigo_4 = false;
	int pos_inimigo5 = inimigo5->posicao_x;
	bool morte_inimigo_5 = false;
	int pos_inimigo6 = inimigo6->posicao_x;
	bool morte_inimigo_6 = false;
	int pos_inimigo7 = inimigo7->posicao_x;
	bool morte_inimigo_7 = false;
	int pos_inimigo_bird = inimigo_bird->posicao_x;
	bool morte_inimigo_bird = false;
	int pos_inimigo_bird2 = inimigo_bird2->posicao_x;
	bool morte_inimigo_bird2 = false;
	int pos_inimigo_bird3 = inimigo_bird3->posicao_x;
	bool morte_inimigo_bird3 = false;
	int pos_inimigo8 = inimigo8->posicao_x;
	bool morte_inimigo_8 = false;

	//criando variáveis para o inimigo_bird:
	int count_frames_bird = 0;
	int count_frames_bird2 = 0;
	int count_frames_bird3 = 0;
	int count_projetil_bird = 0;
	int salva_arg2_bird = pjt_bird->posicao_y+40;
	bool controle_destroi_projetil_bird = false;
	int salva_arg2_bird2 = pjt_bird2->posicao_y+40;
	bool controle_destroi_projetil_bird2 = false;
	int salva_arg2_bird3 = pjt_bird2->posicao_y+40;
	bool controle_destroi_projetil_bird3 = false;

	//criando variáveis para o inimigo_lobo:
	int salva_arg3_lobo = pjt_lobo->posicao_x;
	int salva_arg3_lobo2 = pjt_lobo2->posicao_x;
	bool baixo_pressionado = false;

	//cirando variáveis para a vida do personagem:
	int count_vidas = 3;
	bool coracao1 = true;
	bool coracao2 = true;
	bool coracao3 = true;
	int recebe = -1;
	int recebe2 = -1;
	int recebe3 = -1;
	int recebe4 = -1;
	int recebe5 = -1;
	int recebe6 = -1;
	int recebe7 = -1;
	int recebe8 = -1;
	int recebelobo = -1;
	int recebelobo2 = -1;
	int invencibilidade_frames = 0;

	//criando variáveis para controle do game-over:
	bool acabou_mundo = false;

	//criando variáveis para controle do pause:
	int valor_funcao_pause;
//-----------------------------------------------------------------------------------------------------------------------------------------------------//
//LOOP PRINCIPAL:
	bool controle = true;
	//Laço principal do programa:
    while(controle){
		al_wait_for_event(queue, &event);

		//Evento de pressionar tecla:
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && !acabou_mundo) {
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT:
					p->frame_atual = 1;
					a->chave = 1;
					andando_direita = true;
					//conferindo se está virado a esquerda,
					//se estiver, eu viro ele para a direita:
					if (p->largura < 0)
						p->largura *= -1;
					break;
				case ALLEGRO_KEY_LEFT:
					p->frame_atual = 1;
					a->chave = 1;
					//conferindo se está virado a direita,
					//se estiver, eu viro ele para a esquerda:
					if (p->largura > 0)
						p->largura *= -1;
					andando_esquerda = true;
					break;
				case ALLEGRO_KEY_DOWN:
					p->frame_atual = 3;
					a->chave = 0;
					baixo_pressionado = true;
					break;
				case ALLEGRO_KEY_UP:
					if (!no_ar) {
						velocidade_y = -35;
						no_ar = true;
						p->frame_atual = 2;
					}
					a->chave = 0;
					pulando = true;
					break;
				case ALLEGRO_KEY_SPACE:
					p->frame_atual = 4;
					if (!pulando)
						a->chave = 1;
					if (p->largura < 0)
						sentido_positivo = false;
					if (!atirando && !pulando) {
						atirando = true;
						if (p->largura > 0)
							pjt->posicao_x = 510;  
						else
							pjt->posicao_x = 210;

						pjt->velocidade = 14;
					}
					break;
				case ALLEGRO_KEY_W:
					cima = true;
					break;
				case ALLEGRO_KEY_ESCAPE:
					valor_funcao_pause = tela_pause(disp);
					break;
			}
		}
		//quebrando o loop principal se o valor do pause for MENU:
		if (valor_funcao_pause == 1)
			break;
		else
			al_flush_event_queue(queue);

		//Evento de soltar tecla:
		if (event.type == ALLEGRO_EVENT_KEY_UP && !acabou_mundo) {
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT:
					p->frame_atual = 0;
					andando_direita = false;
					break;
				case ALLEGRO_KEY_LEFT:
					p->frame_atual = 0;
					andando_esquerda = false;
					break;
				case ALLEGRO_KEY_DOWN:
					p->frame_atual = 0;
					a->chave = 1;
					baixo_pressionado = false;
					break;
				case ALLEGRO_KEY_UP:
					p->frame_atual = 0;
					a->chave = 1;
					pulando = false;
					break;
				case ALLEGRO_KEY_SPACE:
					p->frame_atual = 0;
					a->chave = 1;
					break;
				case ALLEGRO_KEY_W:
					cima = false;
					break;
			}
		}
        //Evento que captura eventos da fila, inserindo os mesmos na variável de eventos:
        if (event.type == ALLEGRO_EVENT_TIMER){
			//limpando a tela:
			al_clear_to_color(al_map_rgb(0, 0, 0));	

			//Movimentando mundo:
			if (andando_direita)
				movendo_mundo -= 14;
			if (andando_esquerda && (-movendo_mundo > 0))
				movendo_mundo += 14;

			//Aplicando a "gravidade" se o personagem estiver no ar:
			if (no_ar) {
                velocidade_y += 4;
                p->posicao_y += velocidade_y;

                if (p->posicao_y >= chao) {
                    p->posicao_y = chao;
                    velocidade_y = 0;
                    no_ar = false;
                    p->frame_atual = 0;
                }
            }
            
			//Desenhando tela de fundo multuplicada por 6:
			double posicao;
			for (int i = 0; i < 12; i++) {
				posicao = movendo_mundo + i * 1080;
				al_draw_scaled_bitmap(background_jogo, 0, 0, 1056, 672, posicao, 0, 1080, 720, 0);
			}

			//Colando variável que representa minha kilometragem:
			char texto_posicao[50];
			sprintf(texto_posicao, "M: %.0f", -movendo_mundo);
			al_draw_text(font, al_map_rgb(255, 255, 0), 950, 20, ALLEGRO_ALIGN_CENTER, texto_posicao);

			//colocando portal:
			al_draw_scaled_bitmap(sprite_portal, 0,0,1024,1024, 12200+movendo_mundo, 340, 256, 256, 0);	

			//Colocando personagem:
			coloca_personagem(p, 1);

			//Colocando arma:
			if (a->chave == 1) {
				if (andando_esquerda) {
					a->posicao_x = 300;
					coloca_arma(a);
				}
				else if (andando_direita) {
					a->posicao_x = 570;
					coloca_arma(a);
				}
				else {
					coloca_arma(a);
				}
			}
			

			//Colocando inimigo2:
			if (!morte_inimigo_2) {
				coloca_inimigo(inimigo2, movendo_mundo, 2);
				inimigo2->posicao_x -= 7;
			}
			//Colocando inimigo3 (lobo):
			if (!morte_inimigo_3) {
				coloca_inimigo(inimigo3, movendo_mundo, 3);
			}
			//Colocando inimigo4:
			if (!morte_inimigo_4) {
				coloca_inimigo(inimigo4, movendo_mundo, 2);
				inimigo4->posicao_x -= 7;
			}
			//Colocando inimigo5:
			if (!morte_inimigo_5) {
				coloca_inimigo(inimigo5, movendo_mundo, 2);
				inimigo5->posicao_x -= 7;
			}
			//Colocando inimigo6:
			if (!morte_inimigo_6) {
				coloca_inimigo(inimigo6, movendo_mundo, 2);
				inimigo6->posicao_x -= 7;
			}
			//Colocando inimigo7:
			if (!morte_inimigo_7) {
				coloca_inimigo(inimigo7, movendo_mundo, 2);
				inimigo7->posicao_x -= 7;
			}
			//Colocando inimigo_bird:
			if (!morte_inimigo_bird) {
				coloca_inimigo_bird(inimigo_bird, count_frames_bird, movendo_mundo);
				count_frames_bird++;
				if (count_frames_bird == 64)
					count_frames_bird = 0;
			}
			//Colocando inimigo_bird2:
			if (!morte_inimigo_bird2) {
				coloca_inimigo_bird(inimigo_bird2, count_frames_bird2, movendo_mundo);
				count_frames_bird2++;
				if (count_frames_bird2 == 64)
					count_frames_bird2 = 0;
			}
			//Colocando inimigo_bird3:
			if (!morte_inimigo_bird3) {
				coloca_inimigo_bird(inimigo_bird3, count_frames_bird3, movendo_mundo);
				count_frames_bird3++;
				if (count_frames_bird3 == 64)
					count_frames_bird3 = 0;
			}
			//Colocando inimigo8 (lobo):
			if (!morte_inimigo_8) {
				coloca_inimigo(inimigo8, movendo_mundo, 3);
			}


			//Colocando disparo:
			if (atirando) {
				if (sentido_positivo) 
					pjt->velocidade += 4;
				else
					pjt->velocidade -= 4;
				

				if (!cima && !controle2) {
					pjt->posicao_x += pjt->velocidade;
				}
				else if (cima && !controle2) {
					if (sentido_positivo)
						pjt->posicao_y -= pjt->velocidade;
					else
						pjt->posicao_y += pjt->velocidade;
					controle2 = true;
				}
				else if (!cima && controle2) {
					if (sentido_positivo)
						pjt->posicao_y -= pjt->velocidade;
					else
						pjt->posicao_y += pjt->velocidade;
				}
				else if (cima && controle2) {
					if (sentido_positivo)
						pjt->posicao_y -= pjt->velocidade;
					else
						pjt->posicao_y += pjt->velocidade;
				}


				coloca_projetil_personagem(pjt);

				//impacto inimigo 2:
				colisao_inimigo(&morte_inimigo_2, pjt, inimigo2, movendo_mundo, 1);
				//impacto inimigo 3:
				colisao_inimigo(&morte_inimigo_3, pjt, inimigo3, movendo_mundo, 2);
				//impacto inimigo 4:
				colisao_inimigo(&morte_inimigo_4, pjt, inimigo4, movendo_mundo, 1);
				//impacto inimigo 5:
				colisao_inimigo(&morte_inimigo_5, pjt, inimigo5, movendo_mundo, 1);
				//impacto inimigo 6:
				colisao_inimigo(&morte_inimigo_6, pjt, inimigo6, movendo_mundo, 1);
				//impacto inimigo 7:
				colisao_inimigo(&morte_inimigo_7, pjt, inimigo7, movendo_mundo, 1);
				//impacto inimigo bird:
				colisao_inimigo_bird(&morte_inimigo_bird, pjt, inimigo_bird, movendo_mundo);
				//impacto inimigo bird2:
				colisao_inimigo_bird(&morte_inimigo_bird2, pjt, inimigo_bird2, movendo_mundo);
				//impacto inimigo bird3:
				colisao_inimigo_bird(&morte_inimigo_bird3, pjt, inimigo_bird3, movendo_mundo);
				//impacto inimigo 8:
				colisao_inimigo(&morte_inimigo_8, pjt, inimigo8, movendo_mundo, 2);

				if ((pjt->velocidade >= 100 || pjt->velocidade <= -72)) {
					atirando = false;
					sentido_positivo = true;
					controle2 = false;
					pjt->posicao_y = salva_pjt_y;
				}
			}


			//Colocando projeteis dos birds:
			if (!morte_inimigo_bird) {
				atira_bird(pjt_bird, movendo_mundo, salva_arg2_bird);
			}
			if (morte_inimigo_bird && !controle_destroi_projetil_bird) {
				destroi_projetil(pjt_bird);
				controle_destroi_projetil_bird = true;
			}
			if (!morte_inimigo_bird2) {
				atira_bird(pjt_bird2, movendo_mundo, salva_arg2_bird2);
			}
			if (morte_inimigo_bird2 && !controle_destroi_projetil_bird2) {
				destroi_projetil(pjt_bird2);
				controle_destroi_projetil_bird2 = true;
			}
			if (!morte_inimigo_bird3) {
				atira_bird(pjt_bird3, movendo_mundo, salva_arg2_bird3);
			}
			if (morte_inimigo_bird3 && !controle_destroi_projetil_bird3) {
				destroi_projetil(pjt_bird3);
				controle_destroi_projetil_bird3 = true;
			}

			//colocando projeteis dos lobos:
			if (!morte_inimigo_3) {
				atira_lobo(pjt_lobo, movendo_mundo, salva_arg3_lobo);
			}
			if (!morte_inimigo_8) {
				atira_lobo(pjt_lobo2, movendo_mundo, salva_arg3_lobo2);
			}



			//Colocando corações:
			if (coracao1)
				al_draw_scaled_bitmap(sprite_coracao1, 0,0,1024,1024, 20, 20, 80, 80, 0);
			else
				al_draw_scaled_bitmap(sprite_coracao_preto1, 0,0,1024,1024, 20, 20, 80, 80, 0);
			if (coracao2)
				al_draw_scaled_bitmap(sprite_coracao2, 0,0,1024,1024, 100, 20, 80, 80, 0);
			else 
				al_draw_scaled_bitmap(sprite_coracao_preto2, 0,0,1024,1024, 100, 20, 80, 80, 0);
			if (coracao3)
				al_draw_scaled_bitmap(sprite_coracao3, 0,0,1024,1024, 180, 20, 80, 80, 0);
			else 
				al_draw_scaled_bitmap(sprite_coracao_preto3, 0,0,1024,1024, 180, 20, 80, 80, 0);
			
			//Colisão entre personagem e pássaros:
			recebe = colisao_personagem_com_bird(&count_vidas, pjt_bird, p, movendo_mundo);
			recebe2 = colisao_personagem_com_bird(&count_vidas, pjt_bird2, p, movendo_mundo);
			recebe8 = colisao_personagem_com_bird(&count_vidas, pjt_bird3, p, movendo_mundo);

			//Colisão entre personagem e lobo:
			recebelobo = colisao_personagem_com_lobo(baixo_pressionado, &count_vidas, pjt_lobo, p, movendo_mundo);
			recebelobo2 = colisao_personagem_com_lobo(baixo_pressionado, &count_vidas, pjt_lobo2, p, movendo_mundo);

			if (invencibilidade_frames > 0)
    			invencibilidade_frames--;
			if (invencibilidade_frames <= 0) {
				if (inimigo2 != NULL && !morte_inimigo_2)
					recebe3 = colisao_personagem_com_inimigo2(&count_vidas, inimigo2, p, movendo_mundo, &morte_inimigo_2, &invencibilidade_frames);
				if (inimigo4 != NULL && !morte_inimigo_4)
					recebe4 = colisao_personagem_com_inimigo2(&count_vidas, inimigo4, p, movendo_mundo, &morte_inimigo_4, &invencibilidade_frames);
				if (inimigo5 != NULL && !morte_inimigo_5)
					recebe5 = colisao_personagem_com_inimigo2(&count_vidas, inimigo5, p, movendo_mundo, &morte_inimigo_5, &invencibilidade_frames);
				if (inimigo6 != NULL && !morte_inimigo_6)
					recebe6 = colisao_personagem_com_inimigo2(&count_vidas, inimigo6, p, movendo_mundo, &morte_inimigo_6, &invencibilidade_frames);
				if (inimigo7 != NULL && !morte_inimigo_7)
					recebe7 = colisao_personagem_com_inimigo2(&count_vidas, inimigo7, p, movendo_mundo, &morte_inimigo_7, &invencibilidade_frames);
			}
			if ((recebelobo == 2 && coracao1) || (recebelobo2 == 2 && coracao1) || (recebe == 2 && coracao1) || (recebe2 == 2 && coracao1) || (recebe3 == 2 && coracao1) || (recebe4 == 2 && coracao1) || (recebe5 == 2 && coracao1) || (recebe6 == 2 && coracao1) || (recebe7 == 2 && coracao1) || (recebe8 == 2 && coracao1))
				coracao1 = false;
			if ((recebelobo == 1 && coracao2) || (recebelobo2 == 1 && coracao2) ||(recebe == 1 && coracao2) || (recebe2 == 1 && coracao2) || (recebe3 == 1 && coracao2) || (recebe4 == 1 && coracao2) || (recebe5 == 1 && coracao2) || (recebe6 == 1 && coracao2) || (recebe7 == 1 && coracao2) || (recebe8 == 1 && coracao2))
				coracao2 = false;
			if ((recebelobo == 0 && coracao3) || (recebelobo2 == 0 && coracao3) || (recebe == 0 && coracao3) || (recebe2 == 0 && coracao3) || (recebe3 == 0 && coracao3) || (recebe4 == 0 && coracao3) || (recebe5 == 0 && coracao3) || (recebe6 == 0 && coracao3) || (recebe7 == 0 && coracao3) || (recebe8 == 0 && coracao3)) 
				coracao3 = false;
			
			// Atualiza a tela:
            al_flip_display();

			//condição de parada do meu jogo:
			if (-movendo_mundo > 11850) {
				acabou_mundo = true;
				//chamando a função the_boss se ele passar pelo cenário:
				cria_mundo2(disp);
				break;
			}
			if (coracao1 == false && coracao2 == false && coracao3 == false) {
				acabou_mundo = true;
				tela_game_over(disp);
				break;
			}
        }																																																				//Indica o evento correspondente no controle do segundo jogador (botão de movimentação para baixo) (!)
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			controle = false;
    }
//-----------------------------------------------------------------------------------------------------------------------------------------------------//
	
	if (p)
		destroi_personagem(p);
	if (a)
		destroi_arma(a);
	if(pjt)
		destroi_projetil_personagem(pjt);
	if (inimigo2)
		destroi_inimigo(inimigo2);
	if (inimigo3)
		destroi_inimigo(inimigo3);
	if (inimigo4)
		destroi_inimigo(inimigo4);
	if (inimigo5)
		destroi_inimigo(inimigo5);
	if (inimigo6)
		destroi_inimigo(inimigo6);
	if (inimigo7)
		destroi_inimigo(inimigo7);
	if (inimigo8)
		destroi_inimigo(inimigo8);
	if (inimigo_bird)
		destroi_inimigo_bird(inimigo_bird);
	if (inimigo_bird2)
		destroi_inimigo_bird(inimigo_bird2);
	if (inimigo_bird3)
		destroi_inimigo_bird(inimigo_bird3);
	if (sprite_coracao1)
		al_destroy_bitmap(sprite_coracao1);
	
	//Com o intuito de não travar muito, deixando todos esses free como comentário:
	
	/*if (pjt_bird)
		destroi_projetil(pjt_bird);
	if (pjt_bird2)
		destroi_projetil(pjt_bird2);
	if (pjt_bird3)
		destroi_projetil(pjt_bird3);
	if (pjt_lobo)
		destroi_projetil(pjt_lobo);
	if (pjt_lobo2)
		destroi_projetil(pjt_lobo2);*/

	/*if (sprite_coracao1)
		al_destroy_bitmap(sprite_coracao1);
	if (sprite_coracao2)
		al_destroy_bitmap(sprite_coracao2);
	if (sprite_coracao3)
		al_destroy_bitmap(sprite_coracao3);
	if (sprite_coracao_preto1)
		al_destroy_bitmap(sprite_coracao_preto1);
	if (sprite_coracao_preto2)
		al_destroy_bitmap(sprite_coracao_preto2);
	if (sprite_coracao_preto3)
		al_destroy_bitmap(sprite_coracao_preto3);
	if (background_jogo)
		al_destroy_bitmap(background_jogo);
	if (sprite_portal)
		al_destroy_bitmap(sprite_portal);*/

	al_destroy_timer(timer);														//Destrutor do relógio
	al_destroy_event_queue(queue);													//Destrutor da fila
	al_destroy_font(font);
}