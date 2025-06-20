#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas

//----------------------- variaveis globais ---------------------------------------

const int SCREEN_W = 960/2;//largura da tela em pixels ->
const int SCREEN_H = 540/2;//altura da tela ^
const int GRASS_H = 60;//altura da grama

const int NAVE_W = 100;//LARGURA DA NAVE
const int NAVE_H = 50;//ALTURA DA NAVA

const int ALIEN_W = 50;//largura do alien
const int ALIEN_H = 25;//altura do alien

const float FPS = 100;

//----------------------- structs ---------------------------------------

typedef struct Nave{
	float x;//local
	int vel;//velocidade
	int dir, esq;
	ALLEGRO_COLOR cor;
} Nave;

typedef struct Alien{
	float x,y;
	float x_vel, y_vel;
	ALLEGRO_COLOR cor;
}Alien;

//----------------------- funcoes de visualização ---------------------------------------

//funcao dos valores da nave
void initNave(Nave *nave){
	nave->x = SCREEN_W/2;//posição da nave
	nave->vel=1;//velocidade
	nave -> dir = 0;
	nave -> esq = 0;
	nave->cor = al_map_rgb(0,0,255);//cor da nave

}
//funcao que gera a nave
void draw_nave(Nave nave){
	float y_base = SCREEN_H - GRASS_H/2;
	al_draw_filled_triangle(nave.x,  y_base-NAVE_H, nave.x - NAVE_W/2, y_base, nave.x + NAVE_W/2, y_base, nave.cor);

}
//funcao que atualiza local da nave
void update_nave(Nave *nave){
	//se ele estiver indo para a direita, o x soma com a taxa de velocidade
	if(nave->dir && (nave->x + nave->vel <= SCREEN_W)){
		nave -> x += nave-> vel;
	}
	//se a nave estiver indo para a esquerda, o x diminui o valor (é o plano carteziano)
	if(nave->esq&& (nave->x - nave->vel >= 0)){
		nave -> x -= nave-> vel;
	}
}


//funcao dos valores do alien
void initAlien(Alien *alien){
	alien -> x =0;
	alien -> y =0;
	alien -> x_vel =1;
	alien ->y_vel = ALIEN_H;
	alien->cor = al_map_rgb(rand()%256,rand()%256,rand()%256);

}
//fukcao que desenha o alien
void draw_alien(Alien alien){
	al_draw_filled_rectangle(alien.x, alien.y, alien.x + ALIEN_W ,alien.y + ALIEN_H, alien.cor);
}
//funcao que atualiza loca do alien
void update_alien(Alien *alien){
	//se a posicao dele + a lagura dele + a velocidade for maior que a tela
	if((alien ->x + ALIEN_W + alien->x_vel > SCREEN_W) || (alien ->x + alien->x_vel < 0) ){
		alien->y += alien->y_vel;//a posição vertival aumenta o tamanho dele
		printf("valor do x_alien: %f ",alien->x_vel);
		alien ->x_vel *= (-1);//macete para ficar invertando valor de x

	}
	alien->x += alien->x_vel;//se não nair no if, vai indo para a direita
}
//funcao de colisao
int colisao_alien_solo(Alien alien){
	if(alien.y + ALIEN_H >= SCREEN_H - GRASS_H) return 1;//se a vertical do alien for maior que a tela na parte da grama
	return 0;
}




//funcao que gera cenario
void draw_scenario(){

        //colore a tela com uma única cor, formato rgb: vermelho,verde,azul
        al_clear_to_color(al_map_rgb(0,0,0));//fica preto

        //desenhamdo a grama -> tem a allegro funtions primitives
        al_draw_filled_rectangle(0, SCREEN_H - GRASS_H, SCREEN_W, SCREEN_H, al_map_rgb(0,255,0));//cria um retangulo: topo esquerda,  baixo esquerda, topo direita, baixo direita

}



int main(){

	//----------------------- variaveis apontadas ---------------------------------------

    //obj tela
	ALLEGRO_DISPLAY *display = NULL;//vai passar o endereço para várias fulções
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;//fila de eventos
    ALLEGRO_TIMER *timer = NULL;//estrutura de tempo

	//----------------------- Variaveis do main e structs ---------------------------------------

	Nave nave;//struct da nave
	Alien alien;//struct do alien


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

    //colore a tela com uma única cor, formato rgb: vermelho,verde, azul
    al_clear_to_color(al_map_rgb(0,255,0));

    //atualiza a tela (quando houver algo para mostrar)
	//al_flip_display();//atualiza tela, é preciso para gerar a imagem

	initNave(&nave);//inicia nave
	initAlien(&alien);//inicia alien

    int playing =1;//jogando comeca com 1

	//inicia o temporizador
	al_start_timer(timer);

	//----------------------- lógica para criar uma tela ---------------------------------------

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
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
		}
        //se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
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
					nave.esq = 1;
				break;
		   
		   		case ALLEGRO_KEY_D:
					nave.dir = 1;
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
					nave.esq = 0;
				break;
		   
		   		case ALLEGRO_KEY_D:
					nave.dir = 0;
				break;
		   }
		}
    }

    //colore a tela com uma única cor, formato rgb: vermelho,verde, azul
    //al_clear_to_color(al_map_rgb(0,255,0));
    //atualiza a tela (quando houver algo para mostrar)
	//al_flip_display();//atualiza tela, é preciso para gerar a imagem
    //al_rest(5);//tempo de 5 segundos
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

    return 0;
}