#ifndef VIEW_H//se nao tiver o view, faz oseguinte código: (igual no model)
#define VIEW_H

#include "model.h"
#include <allegro5/allegro.h>

//----------------------- funcoes de visualização ---------------------------------------

//funcao que gera a nave
void draw_nave(Nave nave);

//fukcao que desenha o alien
void draw_alien(Alien alien);

//funcao que gera cenario
void draw_scenario();

#endif