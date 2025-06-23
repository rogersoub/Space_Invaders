#include "view.h"
#include <stdio.h>
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include <allegro5/allegro_image.h>//local das imagens

//----------------------- variaveis apontadas de visualizacao ---------------------------------------

ALLEGRO_BITMAP *fundo_sprite = NULL;
ALLEGRO_BITMAP *nave_sprite = NULL;
ALLEGRO_BITMAP *alien_sprite = NULL;


//----------------------- funcoes de visualização ---------------------------------------

//funcao para carregar a imagem de fundo
int load_fundo(const char *filename) {
    fundo_sprite = al_load_bitmap(filename);
    if (!fundo_sprite) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo: %s\n", filename);
        return 0; //falha
    }
    return 1; //sucesso
}
//funcao para destruir a imagem de fundo e liberar memória
void destroy_fundo() {
    if (fundo_sprite) {
        al_destroy_bitmap(fundo_sprite);
        fundo_sprite = NULL; //evita usar um ponteiro para a memoria liberada
    }
}


//funcao para carregar a imagem da nave
int load_nave(const char *filename) {
    nave_sprite = al_load_bitmap(filename);
    if (!nave_sprite) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo: %s\n", filename);
        return 0; //falha
    }
    return 1; //sucesso
}
//funcao para destruir a imagem da nave e liberar memória
void destroy_nave() {
    if (nave_sprite) {
        al_destroy_bitmap(nave_sprite);
        nave_sprite = NULL; //evita usar um ponteiro para a memoria liberada
    }
}


//funcao para carregar a imagem do alien
int load_alien(const char *filename) {
    alien_sprite = al_load_bitmap(filename);
    if (!alien_sprite) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo: %s\n", filename);
        return 0; //falha
    }
    return 1; //sucesso
}
//funcao para destruir a imagem ddo alien e liberar memória
void destroy_alien() {
    if (alien_sprite) {
        al_destroy_bitmap(alien_sprite);
        alien_sprite = NULL; //evita usar um ponteiro para a memoria liberada
    }
}


//funcao que gera cenario
void draw_scenario(){

        //colore a tela com uma única cor, formato rgb: vermelho,verde,azul
        if (fundo_sprite){
            al_draw_bitmap(fundo_sprite, 0, 0, 0);
        }else{
            al_clear_to_color(al_map_rgb(0,0,0));//fica preto
            //desenhamdo a grama -> tem a allegro funtions primitives
            al_draw_filled_rectangle(0, SCREEN_H - GRASS_H, SCREEN_W, SCREEN_H, al_map_rgb(0,255,0));//cria um retangulo: topo esquerda,  baixo esquerda, topo direita, baixo direita e a cor   
        }

        
}

//funcao que gera a nave
void draw_nave(Nave nave){
    if(nave_sprite){
        //al_draw_bitmap(nave_sprite, nave.x, drawY, 0);
        float sx = 30; // ou 25 posicao X de inicio do recorte na folha de sprites
        float sy = 23; //ou 23 posicao Y de inicio do recorte na folha de sprites
        float sw = NAVE_W; //lrgura do sprite individual
        float sh = NAVE_H; //altura do sprite individual
        float drawX = nave.x - (float)NAVE_W/2;//posicao ao centro
        float drawY = SCREEN_H - GRASS_H - NAVE_H;
        al_draw_bitmap_region(nave_sprite, sx, sy, sw, sh, drawX, drawY, 0);//desenha a regiAo do bitmap na posicao do alien na tela
    }else{   
	    float y_base = SCREEN_H - GRASS_H/2;
	    al_draw_filled_triangle(nave.x,  y_base-NAVE_H, nave.x - NAVE_W/2, y_base, nave.x + NAVE_W/2, y_base, nave.cor);
    }

}

//fukcao que desenha o alien
void draw_alien(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS]){
    if (!alien_sprite) {
        // Fallback se a folha de sprites não carregou
        for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
            for (int j = 0; j < NUM_ALIEN_COLS; j++) {
                if (aliens[i][j].is_alive) {
                    al_draw_filled_rectangle(aliens[i][j].x, aliens[i][j].y, 
                                             aliens[i][j].x + ALIEN_W, aliens[i][j].y + ALIEN_H, 
                                             aliens[i][j].cor);
                }
            }
        }
        return;
    }

    // Coordenadas de recorte na folha de sprites para um alien genérico
    // Se a folha de sprites tem vários tipos, isso precisaria ser dinâmico com base em alien.type
    float sx_alien = 48;  // Posição X de início do recorte na folha de sprites (de acordo com seu código anterior)
    float sy_alien = 33; // Posição Y de início do recorte na folha de sprites (de acordo com seu código anterior)
    float sw_alien = ALIEN_W; // Largura do sprite individual (do model)
    float sh_alien = ALIEN_H; // Altura do sprite individual (do model)

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                // Desenha a região do bitmap na posição do alien na tela
                al_draw_bitmap_region(alien_sprite, sx_alien, sy_alien, sw_alien, sh_alien, 
                                      aliens[i][j].x, aliens[i][j].y, 0);
            }
        }
    }
	
}

