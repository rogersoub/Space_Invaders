#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include "model.h"//pega o model
#include "view.h"//pega a view

/*
process_event => vai pegar o evento, nave e paying apontados. vao ser coloacdos no loop
*/
void process_event(ALLEGRO_EVENT ev, Nave *nave, int *playing){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
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
		} 

		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
            /*
            al_clear_to_color(al_map_rgb(rand()%256,rand()%256,rand()%256));
            al_flip_display();//atualiza tela, é preciso para gerar a imagem
            */
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
	Alien alien;//struct do alien

	initNave(&nave);//inicia nave
	initAlien(&alien);//inicia alien

    int playing =1;//jogando comeca com 1

	//inicia o temporizador
	al_start_timer(timer);
	//inicia a imagem
	al_init_image_addon();


 	while(playing)//enquanto playng for 1, vai pintar a tela de verde, se capturar um X, vai fazer putra coisa
    { 

        ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

        //se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {

            draw_scenario();//desenhando o cenario

			update_nave(&nave);//atualiza local da nave antes dela ser desenhada

			update_alien(&alien);//atualiza local da nave

			draw_nave(nave);//funcao que desenha a nave, tem que ficar depois do cenário

			draw_alien(alien);

			playing = !colisao_alien_solo(alien);

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram EITA VAI APARECER, AMEM...", (int)(al_get_timer_count(timer)/FPS));
		}

        process_event(ev, &nave, &playing);	

	}

}
