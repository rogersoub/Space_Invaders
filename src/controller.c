#include "controller.h"//pega o controller
#include "view.h"//pega a view
#include "model.h"//pega o model
#include <stdio.h>
#include <stdlib.h>//origem do rand
#include <time.h> //para srand e time
#include <stdbool.h> //tipos booleanos
#include <allegro5/allegro.h>

//----------------------- variaveis globais de controle de jogo ---------------------------------------
int score = 0;
int lives = 3;
int high_score = 0;
int current_alien_animation_frame = 0; //0 ou 1 para animacao
static int alien_shot_timer = 2; //temporizador para o tiro dos aliens
static const int ALIEN_SHOT_INTERVAL_MIN = 100; //intervalo minimo para tiro de alien (ticks)
static const int ALIEN_SHOT_INTERVAL_MAX = 300; //intervalo maximo para tiro de alien (ticks)


//funcao para resetar o estado do jogo
void reset_game(Nave *nave, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], Shot *shot, AlienShot alien_shots[], int num_alien_shots) {
    initNave(nave);
    initAlien(aliens); //corrigido: passando o array aliens corretamente
    initShot(shot);
    initAlienShots(alien_shots, num_alien_shots);
    score = 0;
    lives = 3;
    current_alien_animation_frame = 0;
    alien_shot_timer = 0; //reseta o timer do tiro do alien
    high_score = load_high_score(); //carrega o ultimo recorde
}


//----------------------- funcoes de CONTROLE (criacao e atualizacao) ---------------------------------------
/*
process_event => vai pegar o evento, nave tiro e stado do jogo. Ambos apontados. vao ser coloacdos no loop
*/
void process_event(ALLEGRO_EVENT ev, Nave *nave, Shot *shot, AlienShot alien_shots[], int num_alien_shots, GameState *current_game_state){
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
					al_play_sample(hit_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //som de tiro da nave

                break;
			}
			//else de baixo: se o jogo nao estiver rodando 
		}else{
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE: // Permite sair da tela final com ESC
                    *current_game_state = GAME_OVER; //forca GAME_OVER para sair do loop do jogo
                break;
				case ALLEGRO_KEY_R: //reinicia o jogo
                        *current_game_state = GAME_RUNNING;
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
    AlienShot alien_shots[3]; //multiplos tiros de alien

	GameState current_game_state = GAME_RUNNING; //estado inicial do jogo

	high_score = load_high_score(); //carrega o recorde ao iniciar o jogo
    reset_game(&nave, aliens, &shot, alien_shots, sizeof(alien_shots) / sizeof(AlienShot));

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
	if (!load_score_font("Assets/font/arial.ttf", 18)) {
        fprintf(stderr, "Nao foi possível carregar a fonte da pontuacao. O texto pode nao aparecer.\n");
    }
    // carrega os sons
    if (!load_sounds()) {
        fprintf(stderr, "falha ao carregar um ou mais sons. o jogo continuara sem eles.\n");
    }
	

	bool redraw = false;
    int ticks_since_last_alien_sound = 0; //para o som dos passos dos aliens
    const int ALIEN_SOUND_INTERVAL = 40; //tocar som a cada 40 ticks

	//inicia o temporizador
	al_start_timer(timer);

	//enquanto o estado for qualquer um
 	while(current_game_state == GAME_RUNNING || current_game_state == GAME_OVER || current_game_state == GAME_WON){ 

        ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

        //processando os eventos de entrada, como (teclado, mouse, fechar janela)
        process_event(ev, &nave, &shot, alien_shots, sizeof(alien_shots) / sizeof(AlienShot), &current_game_state);

        //saia do loop imediatamente.
        if (current_game_state != GAME_RUNNING) {
            break; 
        }
		//se o jogo ta rodando
		if (current_game_state == GAME_RUNNING) {
			//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
			if(ev.type == ALLEGRO_EVENT_TIMER) {

				update_nave(&nave);//atualiza local da nave antes dela ser desenhada

				update_alien(aliens, &current_alien_animation_frame);//atualiza local e animacao do alien

				updateShot(&shot);//atualiza local do tiro

			    //atualiza tiros dos aliens
            	for (int i = 0; i < sizeof(alien_shots) / sizeof(AlienShot); i++) {
                	updateAlienShot(&alien_shots[i]);
            	}

				//logica de tiro dos aliens
            	alien_shot_timer++;
            	if (alien_shot_timer >= (rand() % (ALIEN_SHOT_INTERVAL_MAX - ALIEN_SHOT_INTERVAL_MIN + 1) + ALIEN_SHOT_INTERVAL_MIN)) {
                	fireAlienShot(aliens, alien_shots, sizeof(alien_shots) / sizeof(AlienShot));
                	al_play_sample(tiro_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //som de tiro do alien
                	alien_shot_timer = 0; //reseta o timer
            	}

            	//som dos passos dos aliens
            	ticks_since_last_alien_sound++;
            	if (ticks_since_last_alien_sound >= ALIEN_SOUND_INTERVAL) {
                	al_play_sample(fase_sound, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //som de passo dos aliens
                	ticks_since_last_alien_sound = 0;
            	}


            	//verificacoes de colisao e Fim de Jogo
            	if (colisao_alien_solo(aliens)) { //aliens atingem o solo
                	printf("DEBUG: Aliens atingiram o solo. GAME OVER!\n");
                	current_game_state = GAME_OVER;
            	} else if (check_ship_alien_collision(nave, aliens)) { //nave colide com alien
                	printf("DEBUG: Nave colidiu com alien. GAME OVER!\n");
                	current_game_state = GAME_OVER;
            	} else if (check_shot_alien_collision(&shot, aliens)) { //tiro atinge alien
            		printf("DEBUG: Tiro atingiu um alien.\n");
					al_play_sample(morto_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //som de alien morto
                	printf("debug: tiro atingiu um alien. pontuacao: %d\n", score);
                	//a funcao ja desativa o tiro e o alien, entao nao precisamos fazer nada aqui.
                	//a funcao ja desativa o tiro e o alien, entao nao precisamos fazer nada aqui.
            	}

				//verifica colisao do tiro do alien com a nave
            	for (int i = 0; i < sizeof(alien_shots) / sizeof(AlienShot); i++) {
                	if (check_alien_shot_nave_collision(&alien_shots[i], nave, &lives)) {
                    	printf("debug: tiro do alien atingiu a nave. vidas restantes: %d\n", lives);
                    	if (lives <= 0) {
                        	current_game_state = GAME_OVER;
                    	}
                    	break; //um tiro por vez
                	}
            	}
            
            	// Verifica se todos os aliens foram eliminados (condicao de vitória)
            	if (all_aliens_eliminated(aliens)) {
                	printf("DEBUG: Todos os aliens foram eliminados. VOCE VENCEU!\n");
                	current_game_state = GAME_WON;
            	}

				redraw = true;//ta podendo redesenhar a tela
			
				/*
				if(al_get_timer_count(timer)%(int)FPS == 0)
				p	rintf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS))
				*/
			
			}

		}//FIM IF current_game_state == game_running

        
		//redesenha a tela apenas quando redraw for true
        //se a fila de eventos estiver vazia para evitar "tearing"
        if (redraw && al_is_event_queue_empty(event_queue) && current_game_state == GAME_RUNNING) {
			draw_scenario();//desenhando o cenario

			draw_nave(nave);//funcao que desenha a nave, tem que ficar depois do cenario

			draw_alien(aliens, current_alien_animation_frame);

			draw_shot(shot);

			for (int i = 0; i < sizeof(alien_shots) / sizeof(AlienShot); i++) { //desenha tiros dos aliens
            	draw_alien_shot(alien_shots[i]);
            }
            draw_score_lives(score, lives, high_score); //desenha pontuacao e vidas

            al_flip_display(); //atualiza a tela para mostraras coisa
            redraw = false; //reseta a flag
		}else if (current_game_state == GAME_OVER || current_game_state == GAME_WON) {
            //atualiza high score se necessario
            if (score > high_score) {
                high_score = score;
                save_high_score(high_score);
            }
            draw_game_over_screen(current_game_state, score, high_score); //passa a pontuacao final e recorde
            //o loop continuara aqui ate que o usuario pressione esc ou r
        }


	}//FIM DO LAÇO

	//----------------------- funcoes de CONTROLE, excluir ---------------------------------------

	//apaga a imagem da nave quando o jogo termina
	destroy_nave();
	//apaga a imagem do alienquando o jogo termina
	destroy_alien();
	//apaga a imagem do tiro
	destroy_shot();
	//apaga a imagem de fundo quando o jogo termina
    destroy_fundo();
	//apaga tiro do alien
	destroy_alien_shot();
	//apaga contes
	destroy_game_font();
    destroy_score_font();
	//apaga sons
	destroy_sounds();
}
