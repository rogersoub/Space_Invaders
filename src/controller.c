#include "controller.h"//pega o controller
#include "view.h"//pega a view
#include "model.h"//pega o model
#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdbool.h> //tipos booleanos

/*
process_event => vai pegar o evento, nave e paying apontados. vao ser coloacdos no loop
*/
void process_event(ALLEGRO_EVENT ev, Nave *nave, int *playing){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		printf("\n DEBUG: ENTREI NO EVENTO CLOSE\n");
		*playing = 0;
	}else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)//se o tipo de evento for um pressionar de uma tecla 
	{
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
		   
		   	case ALLEGRO_KEY_D:
				nave->dir = 1;
			break;
		}
	}else if(ev.type == ALLEGRO_EVENT_KEY_UP){
		//imprime qual tecla foi
		printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_A:
				nave->esq = 0;
			break;
		   
		   	case ALLEGRO_KEY_D:
				nave->dir = 0;
			break;
		}
	}
}		


	/*
	game_loop => vai receber o dispaly, var de fila de eventos etimer, ambos como ponteiros
	*/
void game_loop(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer){
	Nave nave;//struct da nave
	Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS];//struct do alien

	initNave(&nave);//inicia nave
	initAlien(aliens);//inicia alien

	//tem que carregar a imagem de fundo ANTES do loop do jogo
    if (!load_fundo("Assets/images/fundo.bmp")) {
        fprintf(stderr, "Não foi possível carregar a imagem de fundo. O jogo continuará sem ela.\n");
        // Pode-se adicionar um al_show_native_message_box aqui para feedback ao usuário.
    }
		//tem que carregar a imagem da nave ANTES do loop do jogo
    if (!load_nave("Assets/images/navep.bmp")) {
        fprintf(stderr, "Não foi possível carregar a imagem da nave. O jogo continuará sem ela.\n");
        // Pode-se adicionar um al_show_native_message_box aqui para feedback ao usuário.
    }
		//tem que carregar a imagem dos aliens ANTES do loop do jogo
    if (!load_alien("Assets/images/alienp.bmp")) {
        fprintf(stderr, "Não foi possível carregar a imagem dos aliens. O jogo continuará sem ela.\n");
        // Pode-se adicionar um al_show_native_message_box aqui para feedback ao usuário.
    }
	



    int playing =1;//jogando comeca com 1
	bool redraw = false;

	//inicia o temporizador
	al_start_timer(timer);

	//enquanto playng for 1, vai pintar a tela de verde, se capturar um X, vai fazer putra coisa
 	while(playing){ 

        ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

        //eventos de entrada (teclado, mouse, fechar janela)
        process_event(ev, &nave, &playing);

        //saia do loop imediatamente.
        if (!playing) {
            break; 
        }

        //se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {

			update_nave(&nave);//atualiza local da nave antes dela ser desenhada

			update_alien(aliens);//atualiza local da nave

			playing = !colisao_alien_solo(aliens);

            //se o jogo parou por colisao, sai do loop
            if (!playing) {
                break;
            }

			redraw = true;

			//atualiza a tela (quando houver algo para mostrar)
			//al_flip_display();
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram mentira...", (int)(al_get_timer_count(timer)/FPS));
		}

		//redesenha a tela apenas quando necessario (aposum evento de timer)
        //se a fila de eventos estiver vazia para evitar "tearing"
        if (redraw && al_is_event_queue_empty(event_queue)) {
			draw_scenario();//desenhando o cenario

			draw_nave(nave);//funcao que desenha a nave, tem que ficar depois do cenário

			draw_alien(aliens);

            al_flip_display(); //atualiza a tela para mostraras coisa
            redraw = false; //reseta a flag
		}


	}
	//apaga a imagem da nave quando o jogo termina
	destroy_nave();
	//apaga a imagem do alienquando o jogo termina
	destroy_alien();
	//apaga a imagem de fundo quando o jogo termina
    destroy_fundo();
}
