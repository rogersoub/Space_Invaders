#include "src/model/model.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include <allegro5/allegro_image.h>//local das imagens

//----------------------- colocando calores nas variaveis globais ---------------------------------------

const int SCREEN_W = 1024;//largura da tela em pixels ->
const int SCREEN_H = 1019;//altura da tela ^
const int GRASS_H = 60;//altura da grama

const int NAVE_W = 100;//LARGURA DA NAVE
const int NAVE_H = 50;//ALTURA DA NAVA

const int ALIEN_W = 50;//largura do alien
const int ALIEN_H = 25;//altura do alien

const float FPS = 100;

//----------------------- funcoes de inicialização---------------------------------------

//funcao dos valores da nave
void initNave(Nave *nave){
	nave->x = SCREEN_W/2;//posição da nave
	nave->vel=1;//velocidade
	nave -> dir = 0;
	nave -> esq = 0;
	nave->cor = al_map_rgb(0,0,255);//cor da nave

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
	/*
	
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){

				alien[i][j] -> x =0;
				alien[i][j] -> y =0;
				alien[i][j] -> x_vel =1;
				alien[i][j] ->y_vel = ALIEN_H;
				alien[i][j]->cor = al_map_rgb(rand()%256,rand()%256,rand()%256);
			
		}
		
	}
	*/
	//estava *alien e assim:  
	/**/
	alien -> x =0;
	alien -> y =0;
	alien -> x_vel =1;
	alien ->y_vel = ALIEN_H;
	alien->cor = al_map_rgb(rand()%256,rand()%256,rand()%256);
	

}
void update_alien(Alien *alien){

	/*
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
				//se a posicao dele + a lagura dele + a velocidade for maior que a tela
			if((alien[i][j] ->x + ALIEN_W + alien[][]->x_vel > SCREEN_W) || (alien ->x + alien->x_vel < 0) ){
				alien->y += alien->y_vel;//a posição vertival aumenta o tamanho dele
				printf("valor do x_alien: %f ",alien->x_vel);
				alien ->x_vel *= (-1);//macete para ficar invertando valor de x

			}
			alien->x += alien->x_vel;//se não nair no if, vai indo para a direita
			
		}
		
	}
	*/

	/**/
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