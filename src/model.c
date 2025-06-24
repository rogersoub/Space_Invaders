#include <stdio.h>
#include <stdlib.h>//origem do rand
#include <stdbool.h> //tipos booleanos
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include "model.h"

//----------------------- colocando calores nas variaveis globais ---------------------------------------

const int SCREEN_W = 800;//largura da tela em pixels ->
const int SCREEN_H = 700;//altura da tela ^
const int GRASS_H = 54;//altura da grama, vulgo terra

const int NAVE_W = 39;//LARGURA DA NAVE
const int NAVE_H = 28;//ALTURA DA NAVA

const int ALIEN_W = 21;//largura do alien
const int ALIEN_H = 19;//altura do alien
const int ALIEN_MOVE_INTERVAL = 30;//itervalo para o movimento dos aliens (em ticks do timer)
const int NUM_ALIEN_ROWS = 6; //numero de linhas de aliens na matriz
const int NUM_ALIEN_COLS = 10; //numero de colunas de aliens na matriz
const int ALIEN_MARGIN_LEFT = 30;//margens, valores estao em pixel
const int ALIEN_MARGIN_RIGHT = 30;

//globais para controlar o movimento do grupo de aliens
static float global_alien_x_vel = 1.0; //velocidade horizontal do grupo
static float alien_drop_amount = 20.0; //wuantidade que os aliens descem quando atingem a bordia
static int alien_move_timer = 0; //temporizador para controlar o movimento passo a passo


const int SHOT_W = 5; //largura do tiro
const int SHOT_H = 15; //altura do tiro


const float FPS = 100;



//----------------------- funcoes dos valores ---------------------------------------

//funcao dos valores da nave
void initNave(Nave *nave){
	nave->x = SCREEN_W/2;//posicao da nave
	nave->vel=3;//velocidade
	nave -> dir = 0;
	nave -> esq = 0;
	nave->cor = al_map_rgb(0,0,255);//cor da nave

}
//funcao que atualiza local da nave
void update_nave(Nave *nave){
	//se ele estiver indo para a direita, o x soma com a taxa de velocidade
	if(nave->dir && (nave->x + (float)NAVE_W /2 + nave->vel <= SCREEN_W)){
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
    const int spacing_x = ALIEN_W + 30; //largura do alien mais espaço
    const int spacing_y = ALIEN_H + 30; //altura do alien maos espaço

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            aliens[i][j].x = start_x + j * spacing_x;
            aliens[i][j].y = start_y + i * spacing_y;
            aliens[i][j].cor = al_map_rgb(rand() % 256, rand() % 256, rand() % 256); //cor reserva
            aliens[i][j].type = rand() % 2; //aleattoriedade futura, 0 ou 1 para diferentes tipos de alien (se sua spritesheet tiver)
            aliens[i][j].is_alive = true; //todos os aliens tem que comecar vivos
        }
    }
    global_alien_x_vel = 15.0; //reseta a velocidade global dos aliens
	alien_move_timer = 0; //tem que resetar o temporizador de movimento do alien

}

//----------------------- funcao de alien ---------------------------------------

//funcao que atualiza a posicao de todos os aliens na matriz
void update_alien(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]){
    //incrementa o temporizador de movimento. Se nao for hora de mover, apenas retorna.
    alien_move_timer++;
    if (alien_move_timer < ALIEN_MOVE_INTERVAL) {
        return;
    }
    alien_move_timer = 0; //reseta o temporizador apos o movimento

    bool hit_edge = false;//booleano do encosto
    float most_left_alien_x = SCREEN_W; //inicializa com um valor maximo
    float most_right_alien_x = 0; //inicializa com um valor mínimo

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                if (aliens[i][j].x < most_left_alien_x) {
                    most_left_alien_x = aliens[i][j].x;
                }
                if (aliens[i][j].x + ALIEN_W > most_right_alien_x) {
                    most_right_alien_x = aliens[i][j].x + ALIEN_W;
                }
            }
        }
    }

    //e nao houver aliens vivos, nao tem movimento
    if (all_aliens_eliminated(aliens)) {
        return;
    }

    //verifica se o grupo de aliens vai atingir a borda com margem
    if (global_alien_x_vel > 0) { //Movendo para a direita
        if (most_right_alien_x + global_alien_x_vel > (SCREEN_W - ALIEN_MARGIN_RIGHT)) {
            hit_edge = true;
        }
    }else{ //Movendo para a esquerda
        if (most_left_alien_x + global_alien_x_vel < ALIEN_MARGIN_LEFT) {
            hit_edge = true;
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

    //atualiza a posicao horizontal de todos os aliens vivos
    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                aliens[i][j].x += global_alien_x_vel;
            }
        }
    }
}


//funcao para verificar se todos os aliens foram eliminados
bool all_aliens_eliminated(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]) {
    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                return false; //encontrou pelo menos um alien vivo
            }
        }
    }
    return true; //todos os aliens foram eliminados
}


//funcao para inicializar o tiro
void initShot(Shot *shot) {
    shot->x = 0;
    shot->y = 0;
    shot->vel = 5.0; //velocidade do tiro
    shot->is_active = false; //tiro nao esta ativo inicialmente
    shot->cor = al_map_rgb(255, 255, 0); //cor de fallback (amarelo)
}

//funcao para atualizar a posicao do tiro
void updateShot(Shot *shot) {
    if (shot->is_active) {
        shot->y -= shot->vel; //move o tiro para cima
        //se o tiro sair da tela, desativa-o
        if (shot->y < 0) {
            shot->is_active = false;
        }
    }
}

//funcao para disparar um tiro (se nao houver um ativo)
void fireShot(Shot *shot, Nave nave) {
    if (!shot->is_active) {
        //posiciona o tiro no centro da nave, na ponta do canhao
        shot->x = nave.x;
        shot->y = SCREEN_H - GRASS_H - NAVE_H; //base da nave SE FICAR MAIOR, É AQUI
        shot->is_active = true;
    }
}


//----------------------- funcoes de colizao ---------------------------------------

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
	return 0;//nada, continua
}


//funcao para verificar colisao entre a nave e qualquer alien
bool check_ship_alien_collision(Nave nave, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]) {
    //bounding box da nave
    float nave_left = nave.x - (float)NAVE_W /2;
    float nave_right = nave.x + (float)NAVE_W /2;
    float nave_top = SCREEN_H - GRASS_H - NAVE_H;
    float nave_bottom = SCREEN_H - GRASS_H;

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                //bounding box do alien
                float alien_left = aliens[i][j].x;
                float alien_right = aliens[i][j].x + ALIEN_W;
                float alien_top = aliens[i][j].y;
                float alien_bottom = aliens[i][j].y + ALIEN_H;

                //verifica sobreposicao das bounding boxes (AABB collision detection)
                if (nave_left < alien_right &&
                    nave_right > alien_left &&
                    nave_top < alien_bottom &&
                    nave_bottom > alien_top) {
                    return true; //colisao detectada
                }
            }
        }
    }
    return false; //nenhuma colisao
}

//funcao para verificar colisao entre o tiro e qualquer alien
bool check_shot_alien_collision(Shot *shot, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]) {
    if (!shot->is_active) {
        return false; //se o tiro nao esta ativo, nao hA colisao
    }

    //bounding box do tiro
    float shot_left = shot->x - (float)SHOT_W /2;
    float shot_right = shot->x + (float)SHOT_W /2;
    float shot_top = shot->y;
    float shot_bottom = shot->y + SHOT_H;

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                //bounding box do alien
                float alien_left = aliens[i][j].x;
                float alien_right = aliens[i][j].x + ALIEN_W;
                float alien_top = aliens[i][j].y;
                float alien_bottom = aliens[i][j].y + ALIEN_H;

                //verifica sobreposicao das bounding boxes
                if (shot_left < alien_right &&
                    shot_right > alien_left &&
                    shot_top < alien_bottom &&
                    shot_bottom > alien_top) {
                    aliens[i][j].is_alive = false; //alien eliminado
                    shot->is_active = false;//tiro desativado
                    return true; //colisao detectada
                }
            }
        }
    }
    return false; //nenhuma colisao
}