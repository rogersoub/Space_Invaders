#ifndef VIEW_H//se nao tiver o view, faz oseguinte código: (igual no model)
#define VIEW_H

#include "src/model/model.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include <allegro5/allegro_image.h>//local das imagens

//----------------------- funcoes de visualização ---------------------------------------

//funcao que gera a nave
void draw_nave(Nave nave);

//fukcao que desenha o alien
void draw_alien(Alien alien);

//funcao que gera cenario
void draw_scenario();

#endif