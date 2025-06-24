#include "view.h"
#include <stdio.h>
#include <allegro5/allegro.h>//tudo do allero
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include <allegro5/allegro_image.h>//local das imagens
#include <allegro5/bitmap.h>//para deixar transparente

//----------------------- variaveis apontadas de visualizacao ---------------------------------------

ALLEGRO_BITMAP *fundo_sprite = NULL;
ALLEGRO_BITMAP *nave_sprite = NULL;
ALLEGRO_BITMAP *alien_sprite = NULL;
ALLEGRO_BITMAP *shot_sprite = NULL; //Sprite do tiro

// Variável global para a fonte
ALLEGRO_FONT *game_font = NULL;


//----------------------- funcoes de carregamento e destruicao ---------------------------------------

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
    
    al_convert_mask_to_alpha(nave_sprite, al_map_rgb(255, 0, 255));// define magenta (255, 0, 255) como cor transparente para a nave  
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
    
    al_convert_mask_to_alpha(alien_sprite, al_map_rgb(255, 0, 255));// define magenta (255, 0, 255) como cor transparente para a nave
    return 1; //sucesso
}
//funcao para destruir a imagem ddo alien e liberar memória
void destroy_alien() {
    if (alien_sprite) {
        al_destroy_bitmap(alien_sprite);
        alien_sprite = NULL; //evita usar um ponteiro para a memoria liberada
    }
}

//funcao para carregar o sprite do tiro
int load_shot(const char *filename) {
    shot_sprite = al_load_bitmap(filename);
    if (!shot_sprite) {
        fprintf(stderr, "Falha ao carregar o sprite do tiro: %s\n", filename);
        return 0;
    }
        
    al_convert_mask_to_alpha(shot_sprite, al_map_rgb(255, 0, 255));// define magenta (255, 0, 255) como cor transparente para a nave
    return 1;
}

//funcao para destruir o sprite do tiro
void destroy_shot() {
    if (shot_sprite) {
        al_destroy_bitmap(shot_sprite);
        shot_sprite = NULL;
    }
}


//funcao para carregar a fonte do jogo
int load_game_font(const char *filename, int size) {
    game_font = al_load_font(filename, size, 0);
    if (!game_font) {
        fprintf(stderr, "Falha ao carregar a fonte: %s\n", filename);
        return 0;
    }
    return 1;
}

//funcao para destruir a fonte do jogo
void destroy_game_font() {
    if (game_font) {
        al_destroy_font(game_font);
        game_font = NULL;
    }
}

//----------------------- funcoes de visualização ---------------------------------------


//funcao que gera cenario
void draw_scenario(){

        
        if (fundo_sprite){
            al_draw_bitmap(fundo_sprite, 0, 0, 0);//coloca o fundo como o sprite de fundo
        }else{
            al_clear_to_color(al_map_rgb(0,0,0));//colore a tela com uma única cor, formato rgb: vermelho,verde,azul (fica preto)
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
        float drawY = SCREEN_H - GRASS_H /2 - NAVE_H;
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
    float sx_alien = 49;  // Posição X de início do recorte na folha de sprites (de acordo com seu código anterior)
    float sy_alien = 34; // Posição Y de início do recorte na folha de sprites (de acordo com seu código anterior)
    float sw_alien = ALIEN_W; // Largura do sprite individual (do model)
    float sh_alien = ALIEN_H; // Altura do sprite individual (do model)

    for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                // Desenha a região do bitmap na posição do alien na tela
                // SE DER ERRO, TIRA OS sx_alien+j*35 | sy_alien+1*10 | sw_alien+1*10
                al_draw_bitmap_region(alien_sprite, sx_alien, sy_alien, sw_alien, sh_alien, 
                                      aliens[i][j].x, aliens[i][j].y, 0);
            }
        }
    }
	
}

//funcao que desenha o tiro
void draw_shot(Shot shot) {
    if (shot.is_active) {
        if (shot_sprite) {
            //desenha o sprite do tiro (se houver um)

            float sx_shot = 8; //posicao x de inicio do recorte
            float sy_shot = 10; //posicao y de inicio do recorte
            float sw_shot = SHOT_W; //latgura do sprite do tiro
            float sh_shot = SHOT_H; //altura do sprite do tiro

            // centraliza o tiro no x da sua posicao
            al_draw_bitmap_region(shot_sprite, sx_shot, sy_shot, sw_shot, sh_shot,
                                  shot.x - (float)SHOT_W / 2, shot.y, 0);
            
                            
        }else{
            //se o sprite nao carregou, coloca um retangulo para o tiro
            al_draw_filled_rectangle(shot.x - (float)SHOT_W / 2, shot.y,
                                     shot.x + (float)SHOT_W / 2, shot.y + SHOT_H,
                                     shot.cor);
        }
    }
}

//funcao que desenha a tela de Game Over/Vitória
void draw_game_over_screen(GameState game_state) {
    al_clear_to_color(al_map_rgb(0, 0, 0)); //limpa a tela para preto
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255); //cor do texto (branco)
    const char *message = "";

    if (game_font) {
        if (game_state == GAME_OVER) {
            message = "GAME OVER!";
            text_color = al_map_rgb(255, 0, 0); //vermelho para Game Over
        } else if (game_state == GAME_WON) {
            message = "VOCE VENCEU!";
            text_color = al_map_rgb(0, 255, 0); //verde para vitoria
        }

        //sesenha a mensagem principal
        al_draw_text(game_font, text_color, SCREEN_W / 2, SCREEN_H / 2 - 50,
                     ALLEGRO_ALIGN_CENTER, message);
        
        //desenha a mensagem para reiniciar
        al_draw_text(game_font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 50,
                     ALLEGRO_ALIGN_CENTER, "Pressione ESC para sair");
        
    } else {
        //fallback se a fonte não carregou
        fprintf(stderr, "Fonte não carregada para tela final.\n");
    }
    al_flip_display(); //atualiza a tela
}

