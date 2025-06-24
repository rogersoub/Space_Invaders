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
extern const int ALIEN_ANIMATION_SPEED;//velocidade por tic de times da animacao
//tiro dos aliens
extern const int ALIEN_SHOT_W;
extern const int ALIEN_SHOT_H;
extern const float ALIEN_SHOT_VEL;

//dimensoes do sprite do tiro da nave
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
	int score_value;//pontos dele
	bool is_alive;//saber se ta vivo
	ALLEGRO_COLOR cor;
}Alien;

typedef struct Shot {
    float x, y; //posicao do tiro
    float vel; //velocidade do tiro
    bool is_active; //indica se o tiro ta ativo na tela
    ALLEGRO_COLOR cor; //cor
} Shot;

typedef struct AlienShot
{
	float x,y;
	float vel;
	bool is_active;
	ALLEGRO_COLOR cor;
} AlienShot ;


//-----------------------funcoes de inicializacao---------------------------------------

//funcao dos valores da nave
void initNave(Nave *nave);
//funcao que atualiza local da nave
void update_nave(Nave *nave);



//funcao dos valores do alien
void initAlien(Alien alien[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
//funcao que atualiza loca do alien
void update_alien(Alien alien[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], int *current_animation_frame);
//funcao para verificar se todos os aliens foram eliminados
bool all_aliens_eliminated(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);


//funcao para inicializar o tiro
void initShot(Shot *shot);
//funcao para atualizar a posicao do tiro
void updateShot(Shot *shot);
//funcao para disparar um tiro (se nao houver um ativo)
void fireShot(Shot *shot, Nave nave);

//funcao para inicializar o tiro DO ALIEN
void initAlienShots(AlienShot alien_shotS[], int num_alien_shots);
//funcao para atualizar a posicao do tiro ALIEN
void updateAlienShot(AlienShot *shot);
//funcao para disparar um tiro DO ALIEN (se nao houver um ativo)
void fireAlienShot(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], AlienShot alien_shots[], int num_alien_shots);


//funcao de colisao
int colisao_alien_solo(Alien alien[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
//funcao para verificar colisao entre a nave e qualquer alien
bool check_ship_alien_collision(Nave nave, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
//funcao para verificar colisao entre o tiro e qualquer alien
bool check_shot_alien_collision(Shot *shot, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], int *score_ptr);
//funcao para verificar o tiro dos aliens na nave
bool check_alien_shot_nave_collision(AlienShot *alien_shot, Nave nave, int *lives);

//----------------------- funcoes de pontuacao e vidas ---------------------------------------
void save_high_score(int score);
int load_high_score();

#endif//finaliza, se nao tiver o codigo