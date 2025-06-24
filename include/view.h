#ifndef VIEW_H//se nao tiver o view, faz oseguinte código: (igual no model)
#define VIEW_H

#include "model.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>//local das imagens
#include <allegro5/allegro_font.h>//fonte
#include <allegro5/allegro_ttf.h>//fontes tbm
#include <allegro5/bitmap.h>

//----------------------- variaveis apontadas de visualizacao ---------------------------------------

extern ALLEGRO_BITMAP *fundo_sprite;
extern ALLEGRO_BITMAP *nave_sprite;
extern ALLEGRO_BITMAP *alien_sprite;
extern ALLEGRO_BITMAP *shot_sprite; //Sprite do tiro

// Variável global para a fonte
extern ALLEGRO_FONT *game_font;

//----------------------- funcoes carregar, visualização e deletar da mamoria ---------------------------------------

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


//funcao para carregar o sprite do tiro
int load_shot(const char *filename);
//funcao que desenha o tiro
void draw_shot(Shot shot);
//funcao para destruir o sprite do tiro
void destroy_shot();


//funcao para carregar a fonte do jogo
int load_game_font(const char *filename, int size);
//funcao que desenha a tela de Game Over
void draw_game_over_screen(GameState game_state);
//funcao para destruir a fonte do jogo
void destroy_game_font();

//funcao que gera cenario
void draw_scenario();

#endif