#ifndef VIEW_H//se nao tiver o view, faz oseguinte código: (igual no model)
#define VIEW_H

#include "model.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //local das imagens

//----------------------- variaveis apontadas de visualizacao ---------------------------------------

extern ALLEGRO_BITMAP *fundo_sprite;
extern ALLEGRO_BITMAP *nave_sprite;
extern ALLEGRO_BITMAP *alien_sprite;

//----------------------- funcoes de visualização ---------------------------------------

// funcao para carregar a imagem de fundo
int load_fundo(const char *filename);
// funcao para destruir a imagem de fundo e liberar memoria
void destroy_fundo();


// funcao para carregar a imagem da NAVE
int load_nave(const char *filename);
//funcao que desenha a nave
void draw_nave(Nave nave);
// funcao para destruir a imagem de da nave e liberar memoria
void destroy_nave();


// funcao para carregar a imagem DO ALIEN
int load_alien(const char *filename);
//fukcao que desenha o alien
void draw_alien(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]);
// funcao para destruir a imagem de do fundo e liberar memoria
void destroy_alien();

//funcao que gera cenario
void draw_scenario();

#endif