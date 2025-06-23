#include <stdio.h>
#include <stdlib.h>//origem do rand
#include <stdbool.h> //tipos booleanos
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include "model.h"

//----------------------- colocando calores nas variaveis globais ---------------------------------------

const int SCREEN_W = 800;//largura da tela em pixels ->
const int SCREEN_H = 700;//altura da tela ^
const int GRASS_H = 40;//altura da grama, vulgo terra

const int NAVE_W = 39;//LARGURA DA NAVE
const int NAVE_H = 28;//ALTURA DA NAVA

const int ALIEN_W = 21;//largura do alien
const int ALIEN_H = 19;//altura do alien
const int NUM_ALIEN_ROWS = 5; //numero de linhas de aliens na matriz
const int NUM_ALIEN_COLS = 10; //numero de colunas de aliens na matriz

const float FPS = 100;

//globais para controlar o movimento do grupo de aliens
static float global_alien_x_vel = 1.0; //velocidade horizontal do grupo
static float alien_drop_amount = 20.0; //wuantidade que os aliens descem quando atingem a bordia

//----------------------- funcoes dos valores ---------------------------------------

//funcao dos valores da nave
void initNave(Nave *nave){
	nave->x = SCREEN_W/2;//posição da nave
	nave->vel=3;//velocidade
	nave -> dir = 0;
	nave -> esq = 0;
	nave->cor = al_map_rgb(0,0,255);//cor da nave

}
//funcao que atualiza local da nave
void update_nave(Nave *nave){
	//se ele estiver indo para a direita, o x soma com a taxa de velocidade
	if(nave->dir && (nave->x + (float)NAVE_W / 2 + nave->vel <= SCREEN_W)){
		nave -> x += nave-> vel;
	}
	//se a nave estiver indo para a esquerda, o x diminui o valor (é o plano carteziano)
	if(nave->esq&& (nave->x - (float)NAVE_W /2 - nave->vel >= 0)){
		nave -> x -= nave-> vel;
	}
}



//funcao dos valores do alien
void initAlien(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]){
//espaco inicial para a grade de aliens
    const int start_x = 50;
    const int start_y = 50;
    const int spacing_x = ALIEN_W + 20; //largura do alien mais espaço
    const int spacing_y = ALIEN_H + 20; //altura do alien maos espaço

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            aliens[i][j].x = start_x + j * spacing_x;
            aliens[i][j].y = start_y + i * spacing_y;
            aliens[i][j].cor = al_map_rgb(rand() % 256, rand() % 256, rand() % 256); //cor reserva
            aliens[i][j].type = rand() % 2; //aleattoriedade futura, 0 ou 1 para diferentes tipos de alien (se sua spritesheet tiver)
            aliens[i][j].is_alive = true; //todos os aliens tem que comecar vivos
        }
    }
    global_alien_x_vel = 1.0; //reseta a velocidade global dos aliens
	

}

//funcao que atualiza a posição de todos os aliens na matriz
void update_alien(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]){
    bool hit_edge = false;//booleano do encosto
    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                //verifica se algum alien vai atingir a borda horizontal
                if ((aliens[i][j].x + ALIEN_W + global_alien_x_vel > SCREEN_W) ||
                    (aliens[i][j].x + global_alien_x_vel < 0)) {
                    hit_edge = true; //marca que uma borda foi atingida
                }
            }
        }
    }

    if (hit_edge) {
        global_alien_x_vel *= -1; //inverte a direcao horizontal do grupo
        for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
            for (int j = 0; j < NUM_ALIEN_COLS; j++) {
                if (aliens[i][j].is_alive) {
                    aliens[i][j].y += alien_drop_amount; //faz todos os aliens descerem
                }
            }
        }
    }

    //atualiza a posição horizontal de todos os aliens vivos
    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                aliens[i][j].x += global_alien_x_vel;
            }
        }
    }
}

//funcao de colisao
int colisao_alien_solo(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]){
	 for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                //se a parte inferior do alien atingir ou ultrapassar a linha da grama
                if (aliens[i][j].y + ALIEN_H >= SCREEN_H - GRASS_H)
                    return 1; //colisao detectada
            }
        }
    }
	return 0;
}