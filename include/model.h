#ifndef MODEL_H//se não tiver o model, adiciona o código desse arquivo:
#define MODEL_H


#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
//----------------------- variaveis globais ---------------------------------------

extern const int SCREEN_W;//largura da tela em pixels ->
extern const int SCREEN_H;//altura da tela ^
extern const int GRASS_H;//altura da grama

extern const int NAVE_W;//LARGURA DA NAVE
extern const int NAVE_H;//ALTURA DA NAVA

extern const int ALIEN_W;//largura do alien
extern const int ALIEN_H;//altura do alien

extern const float FPS;

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

//----------------------- funcoes de inicialização---------------------------------------

//funcao dos valores da nave
void initNave(Nave *nave);
//funcao que atualiza local da nave
void update_nave(Nave *nave);



//funcao dos valores do alien
void initAlien(Alien *alien);
//funcao que atualiza loca do alien
void update_alien(Alien *alien);

//funcao de colisao
int colisao_alien_solo(Alien alien);

#endif//finaliza, se nao tiver o codigo