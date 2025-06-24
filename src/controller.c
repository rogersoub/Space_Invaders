#include "controller.h"//pega o controller
#include "view.h"//pega a view
#include "model.h"//pega o model
#include <stdio.h>
#include <stdbool.h> //tipos booleanos
#include <allegro5/allegro.h>

//----------------------- funcoes de CONTROLE (criacao e atualizacao) ---------------------------------------
/*
process_event => vai pegar o evento, nave tiro e stado do jogo. Ambos apontados. vao ser coloacdos no loop
*/
void process_event(ALLEGRO_EVENT ev, Nave *nave, Shot *shot, GameState *current_game_state){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		printf("\n DEBUG: ENTREI NO EVENTO CLOSE\n");
		*current_game_state = GAME_OVER; //altera o estado do jogo para GAME_OVER. foi pelo valor real
	}else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)//se o tipo de evento for um pressionar de uma tecla 
	{
		if (*current_game_state == GAME_RUNNING) {

			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
        	/*
        	al_clear_to_color(al_map_rgb(rand()%256,rand()%256,rand()%256));
        	al_flip_display();//atualiza tela, é preciso para gerar a imagem
     		*/
			switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_A:
					nave->esq = 1;
				break;
				case ALLEGRO_KEY_LEFT:
					nave->esq = 1;
				break;

		   		case ALLEGRO_KEY_D:
					nave->dir = 1;
				break;
				case ALLEGRO_KEY_RIGHT:
					nave->dir = 1;
				break;

				case ALLEGRO_KEY_SPACE: //tecla de espaco para atirar
                    fireShot(shot, *nave);
                break;
			}
			//else de baixo: se o jogo nao estiver rodando 
		}else{
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: // Permite sair da tela final com ESC
                    *current_game_state = GAME_OVER; // Força GAME_OVER para sair do loop do jogo
                break;
            }
		}

	}else if(ev.type == ALLEGRO_EVENT_KEY_UP){
		//imprime qual tecla foi
		printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		if (*current_game_state == GAME_RUNNING) {
			switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_A:
					nave->esq = 0;
				break;
				case ALLEGRO_KEY_LEFT:
					nave->esq = 0;
				break;
		   
		   		case ALLEGRO_KEY_D:
					nave->dir = 0;
				break;
				case ALLEGRO_KEY_RIGHT:
					nave->dir = 0;
				break;
			}
		}
	}
}		


	/*
	game_loop => vai receber o dispaly, var de fila de eventos etimer, ambos como ponteiros
	*/
void game_loop(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer){
	Nave nave;//struct da nave
	Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS];//struct do alien
	Shot shot;//struct de tiro

	GameState current_game_state = GAME_RUNNING; //estado inicial do jogo

	initNave(&nave);//inicia nave
	initAlien(aliens);//inicia alien
	initShot(&shot);//inicia os tiros

	//tem que carregar a imagem de fundo ANTES do loop do jogo
    if (!load_fundo("Assets/images/fundo.bmp")) {
        fprintf(stderr, "Nao foi possível carregar a imagem de fundo. O jogo continuara sem ela.\n");
        // Pode-se adicionar um al_show_native_message_box aqui para feedback ao usuario.
    }
		//tem que carregar a imagem da nave ANTES do loop do jogo
    if (!load_nave("Assets/images/navep.bmp")) {
        fprintf(stderr, "Nao foi possível carregar a imagem da nave. O jogo continuara sem ela.\n");
        // Pode-se adicionar um al_show_native_message_box aqui para feedback ao usuario.
    }
		//tem que carregar a imagem dos aliens ANTES do loop do jogo
    if (!load_alien("Assets/images/alienp.bmp")) {
        fprintf(stderr, "Nao foi possível carregar a imagem dos aliens. O jogo continuara sem ela.\n");
        // Pode-se adicionar um al_show_native_message_box aqui para feedback ao usuario.
    }
    //carrega o sprite do tiro
    if (!load_shot("Assets/images/navep.bmp")) { //recebe a imagemda nave pequena
        fprintf(stderr, "Nao foi possível carregar o sprite do tiro. O jogo continuara sem ele.\n");
    }
    // Carrega a fonte
    if (!load_game_font("Assets/font/arial.ttf", 24)) { //recebe arial.ttf
        fprintf(stderr, "Nao foi possível carregar a fonte do jogo. O texto pode nao aparecer.\n");
    }
	

	bool redraw = false;

	//inicia o temporizador
	al_start_timer(timer);

	//enquanto o estado for em jogo
 	while(current_game_state == GAME_RUNNING){ 

        ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

        //processando os eventos de entrada, como (teclado, mouse, fechar janela)
        process_event(ev, &nave, &shot, &current_game_state);

        //saia do loop imediatamente.
        if (current_game_state != GAME_RUNNING) {
            break; 
        }

        //se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {

			update_nave(&nave);//atualiza local da nave antes dela ser desenhada

			update_alien(aliens);//atualiza local da nave

			updateShot(&shot);//atualiza local do tiro

            //verificacoes de colisao e Fim de Jogo
            if (colisao_alien_solo(aliens)) { //aliens atingem o solo
                printf("DEBUG: Aliens atingiram o solo. GAME OVER!\n");
                current_game_state = GAME_OVER;
            } else if (check_ship_alien_collision(nave, aliens)) { //nave colide com alien
                printf("DEBUG: Nave colidiu com alien. GAME OVER!\n");
                current_game_state = GAME_OVER;
            } else if (check_shot_alien_collision(&shot, aliens)) { //tiro atinge alien
                printf("DEBUG: Tiro atingiu um alien.\n");
                //a funcao ja desativa o tiro e o alien, entao nao precisamos fazer nada aqui.
            }
            
            // Verifica se todos os aliens foram eliminados (condicao de vitória)
            if (all_aliens_eliminated(aliens)) {
                printf("DEBUG: Todos os aliens foram eliminados. VOCE VENCEU!\n");
                current_game_state = GAME_WON;
            }

			redraw = true;//ta podendo redesenhar a tela
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
		}

		//redesenha a tela apenas quando redraw for true
        //se a fila de eventos estiver vazia para evitar "tearing"
        if (redraw && al_is_event_queue_empty(event_queue)) {
			draw_scenario();//desenhando o cenario

			draw_nave(nave);//funcao que desenha a nave, tem que ficar depois do cenario

			draw_alien(aliens);

			draw_shot(shot);

            al_flip_display(); //atualiza a tela para mostraras coisa
            redraw = false; //reseta a flag
		}


	}//FIM DO LAÇO

	//----------------------- funcoes de CONTROLE, excluir ---------------------------------------

	    //se o jogo nao esta mais rodando, exibe a tela de Game Over/Vitoria
    if (current_game_state == GAME_OVER || current_game_state == GAME_WON) {
        draw_game_over_screen(current_game_state);
        //espera por eventos na tela final (como fechar a janela ou reiniciar)
        ALLEGRO_EVENT ev_final;
        bool waiting_for_exit = true;
        while (waiting_for_exit) {
            al_wait_for_event(event_queue, &ev_final);
            //processa eventos APENAS para sair ou fechar
            if (ev_final.type == ALLEGRO_EVENT_DISPLAY_CLOSE || 
                (ev_final.type == ALLEGRO_EVENT_KEY_DOWN && ev_final.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
                waiting_for_exit = false; //sai do loop para finalizar o jogo
            }
        }
    }

	//apaga a imagem da nave quando o jogo termina
	destroy_nave();
	//apaga a imagem do alienquando o jogo termina
	destroy_alien();
	//apaga a imagem do tiro
	destroy_shot();
	//destroi o 
	//apaga a imagem de fundo quando o jogo termina
    destroy_fundo();
}
