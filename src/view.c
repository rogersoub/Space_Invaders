#include "view.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas

//----------------------- funcoes de visualização ---------------------------------------

//funcao que gera cenario
void draw_scenario(){

        //colore a tela com uma única cor, formato rgb: vermelho,verde,azul
        al_clear_to_color(al_map_rgb(0,0,0));//fica preto

        //desenhamdo a grama -> tem a allegro funtions primitives
        al_draw_filled_rectangle(0, SCREEN_H - GRASS_H, SCREEN_W, SCREEN_H, al_map_rgb(0,255,0));//cria um retangulo: topo esquerda,  baixo esquerda, topo direita, baixo direita e a cor

}

//funcao que gera a nave
void draw_nave(Nave nave){
	float y_base = SCREEN_H - GRASS_H/2;
	al_draw_filled_triangle(nave.x,  y_base-NAVE_H, nave.x - NAVE_W/2, y_base, nave.x + NAVE_W/2, y_base, nave.cor);

}

//fukcao que desenha o alien
void draw_alien(Alien alien){
	al_draw_filled_rectangle(alien.x, alien.y, alien.x + ALIEN_W ,alien.y + ALIEN_H, alien.cor);
}

