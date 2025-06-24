#ifndef MODEL_H//se nao tiver o model, adiciona o código desse arquivo:
#define MODEL_H

#include <allegro5/allegro.h>
#include <stdbool.h> //tipos booleanos
//----------------------- variaveis globais ---------------------------------------

extern const int SCREEN_W;//largura da tela em pixels ->
extern const int SCREEN_H;//altura da tela ^
extern const int GRASS_H;//altura da grama

extern const int NAVE_W;//LARGURA DA NAVE
extern const int NAVE_H;//ALTURA DA NAVA

extern const int ALIEN_W;//largura do alien
extern const int ALIEN_H;//altura do alien
extern const int ALIEN_MOVE_INTERVAL;// itervalo para o movimento dos aliens (em ticks do timer)
extern const int NUM_ALIEN_ROWS; //numero de linhas de aliens na matriz
extern const int NUM_ALIEN_COLS; //numero de colunas de aliens na matriz
extern const int ALIEN_MARGIN_LEFT;//margens
extern const int ALIEN_MARGIN_RIGHT;


//dimensoes do sprite do tiro
extern const int SHOT_W;
extern const int SHOT_H;

extern const float FPS;

//----------------------- enums, estados do Jogo ---------------------------------------
typedef enum GameState {
    GAME_RUNNING,
    GAME_OVER,
    GAME_WON
} GameState;

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
	int type;
	bool is_alive;//saber se ta vivo
	ALLEGRO_COLOR cor;
}Alien;

typedef struct Shot {
    float x, y; //posicao do tiro
    float vel; //velocidade do tiro
    bool is_active; //indica se o tiro ta ativo na tela
    ALLEGRO_COLOR cor; //cor
} Shot;

//-----------------------funcoes de inicializacao---------------------------------------

//funcao dos valores da nave
void initNave(Nave *nave);
//funcao que atualiza local da nave
void update_nave(Nave *nave);



//funcao dos valores do alien
void initAlien(Alien alien[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
//funcao que atualiza loca do alien
void update_alien(Alien alien[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
//funcao para verificar se todos os aliens foram eliminados
bool all_aliens_eliminated(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);


//funcao para inicializar o tiro
void initShot(Shot *shot);
//funcao para atualizar a posicao do tiro
void updateShot(Shot *shot);
//funcao para disparar um tiro (se nao houver um ativo)
void fireShot(Shot *shot, Nave nave);


//funcao de colisao
int colisao_alien_solo(Alien alien[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
//funcao para verificar colisao entre a nave e qualquer alien
bool check_ship_alien_collision(Nave nave, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
//funcao para verificar colisao entre o tiro e qualquer alien
bool check_shot_alien_collision(Shot *shot, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);

#endif//finaliza, se nao tiver o codigo