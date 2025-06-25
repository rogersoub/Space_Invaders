#include <stdio.h>
#include <stdlib.h>//origem do rand
#include <time.h> //para srand e time
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
const int NUM_ALIEN_COLS = 12; //numero de colunas de aliens na matriz
const int ALIEN_MARGIN_LEFT = 30;//margens, valores estao em pixel
const int ALIEN_MARGIN_RIGHT = 30;
const int ALIEN_ANIMATION_SPEED = 100; //altera o frame da animacao a cada 100 ticks (1 segundo em 100fps)

//globais para controlar o movimento do grupo de aliens
static float global_alien_x_vel = 1.0; //velocidade horizontal do grupo
static float alien_drop_amount = 20.0; //wuantidade que os aliens descem quando atingem a bordia
static int alien_move_timer = 0; //temporizador para controlar o movimento passo a passo
static int alien_animation_timer = 0; //temporizador para controlar a animacao dos aliens
//tiro doa aliens
const int ALIEN_SHOT_W = 5; //largura do tiro do alien
const int ALIEN_SHOT_H = 10; //altura do tiro do alien
const float ALIEN_SHOT_VEL = 1.5; //velocidade do tiro do alien

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

    srand(time(NULL)); //inicializa o gerador de numeros aleatorios com o tempo

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            aliens[i][j].x = start_x + j * spacing_x;
            aliens[i][j].y = start_y + i * spacing_y;
            aliens[i][j].cor = al_map_rgb(rand() % 256, rand() % 256, rand() % 256); //cor reserva
            aliens[i][j].type = rand() % 2; //aleattoriedade futura, 0 ou 1 para diferentes tipos de alien
            aliens[i][j].is_alive = true; //todos os aliens tem que comecar vivos

            //atribui tipo e pontuacao baseados na linha
            if (i < 2) { //duas primeiras linhas (0, 1)
                aliens[i][j].type = 0;
                aliens[i][j].score_value = 40;
            } else if (i < 4) { //duas proximas linhas (2, 3)
                aliens[i][j].type = 1;
                aliens[i][j].score_value = 10;
            } else { //ultimas linhas (4, 5)
                aliens[i][j].type = 2;
                aliens[i][j].score_value = 5;
            }

        }
    }
    global_alien_x_vel = 2.0; //reseta a velocidade global dos aliens
	alien_move_timer = 0; //tem que resetar o temporizador de movimento do alien
    alien_animation_timer = 0; //reseta o temporizador da animacao
}

//----------------------- funcao de alien ---------------------------------------

//funcao que atualiza a posicao de todos os aliens na matriz
void update_alien(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], int *current_animation_frame){
    //incrementa o temporizador de movimento. Se nao for hora de mover, apenas retorna.
    alien_move_timer++;
    if (alien_move_timer < ALIEN_MOVE_INTERVAL) {
        // atualiza o frame de animacao mesmo sem mover o grupo
        alien_animation_timer++;
        if (alien_animation_timer >= ALIEN_ANIMATION_SPEED) {
            *current_animation_frame = 1 - *current_animation_frame; //alterna entre 0 e 1
            alien_animation_timer = 0;
        }
        return;
    }
    alien_move_timer = 0; //reseta o temporizador apos o movimento

    // atualiza o frame de animacao
    alien_animation_timer++;
    if (alien_animation_timer >= ALIEN_ANIMATION_SPEED) {
        *current_animation_frame = 1 - *current_animation_frame; //alterna entre 0 e 1
        alien_animation_timer = 0;
    }

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


//funcao para inicializar os tiros dos aliens
void initAlienShots(AlienShot alien_shots[], int num_alien_shots) {
    for (int i = 0; i < num_alien_shots; i++) {
        alien_shots[i].x = 0;
        alien_shots[i].y = 0;
        alien_shots[i].vel = ALIEN_SHOT_VEL;
        alien_shots[i].is_active = false;
        alien_shots[i].cor = al_map_rgb(255, 0, 0); //cor de fallback (vermelho)
    }
}

//funcao para atualizar a posicao de um tiro de alien
void updateAlienShot(AlienShot *alien_shot) {
    if (alien_shot->is_active) {
        alien_shot->y += alien_shot->vel; //move o tiro para baixo
        //se o tiro sair da tela, desativa-o
        if (alien_shot->y > SCREEN_H) {
            alien_shot->is_active = false;
        }
    }
}

//funcao para disparar um tiro de alien (aleatoriamente)
void fireAlienShot(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], AlienShot alien_shots[], int num_alien_shots) {
    //encontra um slot de tiro de alien inativo
    int shot_index = -1;
    for (int i = 0; i < num_alien_shots; i++) {
        if (!alien_shots[i].is_active) {
            shot_index = i;
            break;
        }
    }

    if (shot_index == -1) { //nenhum slot de tiro disponivel
        return;
    }

    //encontra a coluna mais baixa com um alien vivo para atirar
    int lowest_alien_per_col[NUM_ALIEN_COLS];
    for (int j = 0; j < NUM_ALIEN_COLS; j++) {
        lowest_alien_per_col[j] = -1; //nenhum alien vivo na coluna
        for (int i = NUM_ALIEN_ROWS - 1; i >= 0; i--) { //comeca de baixo para cima
            if (aliens[i][j].is_alive) {
                lowest_alien_per_col[j] = i;
                break;
            }
        }
    }

    //seleciona aleatoriamente uma coluna com um alien vivo
    int available_cols[NUM_ALIEN_COLS];
    int count_available_cols = 0;
    for (int j = 0; j < NUM_ALIEN_COLS; j++) {
        if (lowest_alien_per_col[j] != -1) {
            available_cols[count_available_cols++] = j;
        }
    }

    if (count_available_cols > 0) {
        int random_col_index = rand() % count_available_cols;
        int col_to_shoot = available_cols[random_col_index];
        int row_to_shoot = lowest_alien_per_col[col_to_shoot];

        alien_shots[shot_index].x = aliens[row_to_shoot][col_to_shoot].x + ALIEN_W / 2;
        alien_shots[shot_index].y = aliens[row_to_shoot][col_to_shoot].y + ALIEN_H;
        alien_shots[shot_index].is_active = true;
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
bool check_shot_alien_collision(Shot *shot, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], int *score_ptr) {
    if (!shot->is_active) {
        return false; //se o tiro nao esta ativo, nao hA colisao
    }

    //bounding box do tiro
    float shot_left = shot->x - (float)SHOT_W /2;
    float shot_right = shot->x + (float)SHOT_W /2;
    float shot_top = shot->y - (float)SHOT_H /2;
    float shot_bottom = shot->y + (float)SHOT_H;

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                //bounding box do alien
                float alien_left = aliens[i][j].x - (float)ALIEN_W / 2;
                float alien_right = aliens[i][j].x + (float)ALIEN_W / 2;
                float alien_top = aliens[i][j].y - (float)ALIEN_H / 2;
                float alien_bottom = aliens[i][j].y + (float)ALIEN_H / 2;

                //verifica sobreposicao das bounding boxes
                if (shot_left < alien_right &&
                    shot_right > alien_left &&
                    shot_top < alien_bottom &&
                    shot_bottom > alien_top) {
                    aliens[i][j].is_alive = false; //alien eliminado
                    shot->is_active = false;//tiro desativado
                    (*score_ptr) += aliens[i][j].score_value;//adiciona valor do alien, se naop der, deixa 10
                    return true; // Colisão detectada
                }
            }
        }
    }
    return false; //nenhuma colisao
}


//funcao para verificar colisao entre o tiro do alien e a nave
bool check_alien_shot_nave_collision(AlienShot *alien_shot, Nave nave, int *lives) {
    if (!alien_shot->is_active) {
        return false; //se o tiro nao esta ativo, nao ha colisao
    }

    //bounding box do tiro do alien
    float alien_shot_left = alien_shot->x - (float)ALIEN_SHOT_W / 2;
    float alien_shot_right = alien_shot->x + (float)ALIEN_SHOT_W / 2;
    float alien_shot_top = alien_shot->y;
    float alien_shot_bottom = alien_shot->y + ALIEN_SHOT_H;

    //bounding box da nave
    float nave_left = nave.x - (float)NAVE_W / 2;
    float nave_right = nave.x + (float)NAVE_W / 2;
    float nave_top = SCREEN_H - GRASS_H - NAVE_H;
    float nave_bottom = SCREEN_H - GRASS_H;

    //verifica sobreposicao das bounding boxes
    if (alien_shot_left < nave_right &&
        alien_shot_right > nave_left &&
        alien_shot_top < nave_bottom &&
        alien_shot_bottom > nave_top) {
        alien_shot->is_active = false; //tiro do alien desativado
        (*lives)--; //diminui uma vida
        return true; //colisao detectada
    }
    return false; //nenhuma colisao
}

//----------------------- funcoes de pontuacao e vidas ---------------------------------------

//funcao para salvar o recorde em um arquivo
void save_high_score(int score) {
    FILE *file = fopen("Assets/document/record.txt", "w");
    if (file) {
        fprintf(file, "%d", score);
        fclose(file);
    } else {
        fprintf(stderr, "erro ao salvar o recorde.\n");
    }
}

//funcao para carregar o recorde de um arquivo
int load_high_score() {
    FILE *file = fopen("Assets/document/record.txt", "r");
    int high_score = 0;
    if (file) {
        fscanf(file, "%d", &high_score);
        fclose(file);
    } else {
        //se o arquivo nao existe, cria um novo ou retorna 0
        fprintf(stderr, "arquivo de recorde nao encontrado. criando um novo ou usando 0.\n");
        save_high_score(0); //cria o arquivo com 0 se nao existir
    }
    return high_score;
}