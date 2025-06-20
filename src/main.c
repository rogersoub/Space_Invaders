#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include "src/model/model.h"//pega o model
#include "src/controller/controller.h"//pega o controller

int main(){

    //----------------------- variaveis apontadas (ja estao virando locais de memoria) ---------------------------------------

    //obj tela
	ALLEGRO_DISPLAY *display = NULL;//vai passar o endereço para várias fulções
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;//fila de eventos
    ALLEGRO_TIMER *timer = NULL;//estrutura de tempo

	//----------------------- rotina de inicializacao ---------------------------------------

    //inicializa o Allegro
	if(!al_init())// reporta erro
    {
		fprintf(stderr, "failed to initialize allegro!\n");//stderr é a tela
		return -1;
	}

    //inicializa o modulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

	//----------------------- criacoes dinamicas dos elementos ---------------------------------------

    //CRIAR TELA com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);//função que colocar a tela com as medidas
	if(!display)//recebe endereço que 
    {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	

    //cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

    //cria a fila de eventos
	event_queue = al_create_event_queue();//event_queue recebe as informações da fila criada
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	//----------------------- fila de eventos ---------------------------------------

    //registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source());  
	//registra na fila os eventos de tempo: quando o tem po altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));	


     game_loop(display, event_queue, timer);//instanciacao do gameloop. as var ja sao locais de memoria


    return 0;
}