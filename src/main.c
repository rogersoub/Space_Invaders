#include <stdio.h>
#include <time.h> //para srand e time
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include <allegro5/allegro_image.h> //local das imagens
#include <allegro5/allegro_font.h> //para usar al_init_font_addon
#include <allegro5/allegro_ttf.h>//para usar al_init_ttf_addon
#include <allegro5/allegro_audio.h> //para audio
#include <allegro5/allegro_acodec.h>//para audio codecs
#include "model.h"//pega o model
#include "controller.h"//pega o controller

int main(){

    //----------------------- variaveis apontadas (ja estao virando locais de memoria) ---------------------------------------

    //obj tela
	ALLEGRO_DISPLAY *display = NULL;//vai passar o endereço para várias fulções
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;//fila de eventos
    ALLEGRO_TIMER *timer = NULL;//estrutura de tempo

	//----------------------- rotina de inicializacao ---------------------------------------

    srand(time(NULL)); //inicializa o gerador de numeros aleatorios para uso geral

    //inicializa o Allegro
	if(!al_init())// reporta erro
    {
		fprintf(stderr, "failed to initialize allegro!\n");//stderr é a tela
		return -1;
	}

    //inicializa o modulo de primitivas do allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

	//inicializa o addon de imagem para carregar bitmaps
    if (!al_init_image_addon()) {
        fprintf(stderr, "Falha ao inicializar o addon de imagem!\n");
        return -1;
    }

	//inicializa o addon de fonte do allegro
    if (!al_init_font_addon()) {
        fprintf(stderr, "Falha ao inicializar o addon de fonte!\n");
        return -1;
    }

    //inicializa o addon TrueType Font (TTF) do dllegro
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Falha ao inicializar o addon TTF!\n");
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

    //inicializa o addon de audio
    if (!al_install_audio()) {
        fprintf(stderr, "falha ao inicializar o audio!\n");
        return -1;
    }

    //inicializa o addon de codecs de audio
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "falha ao inicializar os codecs de audio!\n");
        return -1;
    }

    //reserva um numero de samples para tocar ao mesmo tempo
    //pode mudar esse valor conforme a necessidade do jogo para sons simultaneos
    if (!al_reserve_samples(10)) {
        fprintf(stderr, "falha ao reservar samples de audio!\n");
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
		 al_destroy_timer(timer);//liberando o timer
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

    //----------------------- rotina de finalizacao do allegro,  liberacao de recursos ---------------------------------------

    al_destroy_display(display);      // destroi a tela
    al_destroy_timer(timer);          // destroi o temporizador
    al_destroy_event_queue(event_queue); // destroi a fila de eventos

    return 0;
}