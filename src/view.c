#include "view.h"
#include <stdio.h>
#include <allegro5/allegro.h>//tudo do allero
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include <allegro5/allegro_image.h>//local das imagens
#include <allegro5/bitmap.h>//para deixar transparente
#include <allegro5/allegro_audio.h>//para audio
#include <allegro5/allegro_acodec.h>//para audio

//----------------------- variaveis apontadas de visualizacao ---------------------------------------

ALLEGRO_BITMAP *fundo_sprite = NULL;
ALLEGRO_BITMAP *nave_sprite = NULL;
ALLEGRO_BITMAP *alien_sprite = NULL;
ALLEGRO_BITMAP *shot_sprite = NULL; //Sprite do tiro
ALLEGRO_BITMAP *alien_shot_sprite = NULL; //sprite do tiro do alien

// variaveis globais para sons
ALLEGRO_SAMPLE *fase_sound = NULL;
ALLEGRO_SAMPLE *hit_sound = NULL;
ALLEGRO_SAMPLE *morto_sound = NULL;
ALLEGRO_SAMPLE *tiro_sound = NULL;

// Variável global para a fonte
ALLEGRO_FONT *game_font = NULL;
ALLEGRO_FONT *score_font = NULL;

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


//funcao para carregar o sprite do tiro do alien
int load_alien_shot(const char *filename) {
    alien_shot_sprite = al_load_bitmap(filename); //a imagem do alien pode conter o sprite do tiro
    if (!alien_shot_sprite) {
        fprintf(stderr, "falha ao carregar o sprite do tiro do alien: %s\n", filename);
        return 0;
    }
    // define magenta (255, 0, 255) como cor transparente para o tiro do alien
    al_convert_mask_to_alpha(alien_shot_sprite, al_map_rgb(255, 0, 255));
    return 1;
}
//funcao para destruir o sprite do tiro do alien
void destroy_alien_shot() {
    if (alien_shot_sprite) {
        al_destroy_bitmap(alien_shot_sprite);
        alien_shot_sprite = NULL;
    }
}


//funcao para carregar sons
int load_sounds() {
    fase_sound = al_load_sample("Assets/audio/fase.wav");
    if (!fase_sound) {
        fprintf(stderr, "falha ao carregar fase.wav\n"); return 0;
    }
    hit_sound = al_load_sample("Assets/audio/hit.wav");
    if (!hit_sound) {
        fprintf(stderr, "falha ao carregar hit.wav\n"); return 0;
    }
    morto_sound = al_load_sample("Assets/audio/morto.wav");
    if (!morto_sound) {
        fprintf(stderr, "falha ao carregar morto.wav\n"); return 0;
    }
    tiro_sound = al_load_sample("Assets/audio/tiro.wav");
    if (!tiro_sound) {
        fprintf(stderr, "falha ao carregar tiro.wav\n"); return 0;
    }
    return 1;
}
//funcao para destruir sons
void destroy_sounds() {
    if (fase_sound) al_destroy_sample(fase_sound);
    if (hit_sound) al_destroy_sample(hit_sound);
    if (morto_sound) al_destroy_sample(morto_sound);
    if (tiro_sound) al_destroy_sample(tiro_sound);
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
//funcao para carregar a fonte da pontuacao
int load_score_font(const char *filename, int size) {
    score_font = al_load_font(filename, size, 0);
    if (!score_font) {
        fprintf(stderr, "falha ao carregar a fonte da pontuacao: %s\n", filename);
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
//funcao para destruir a fonte da pontuacao
void destroy_score_font() {
    if (score_font) {
        al_destroy_font(score_font);
        score_font = NULL;
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
            
        }
        al_draw_filled_rectangle(0, SCREEN_H - GRASS_H, SCREEN_W, SCREEN_H, al_map_rgb(0,255,0));//cria um retangulo: topo esquerda,  baixo esquerda, topo direita, baixo direita e a cor 
        
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
void draw_alien(Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], int current_animation_frame){
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

    //coordenadas de recorte na folha de sprites para os diferentes tipos de alien
    //baseadas na imagem image_4ee8fb.png
    float alien_sprite_coords[3][2][2] = { // [type][frame][x,y]
        {{48, 33}, {83, 32}},   // type 0 (top row)
        {{48, 58}, {83, 58}}, // type 1 (middle row)
        {{48, 86}, {84, 86}}  // type 2 (bottom row)
    };

    float sw_alien = ALIEN_W; //largura do sprite individual
    float sh_alien = ALIEN_H; //altura do sprite individual

   for (int i = 0; i < NUM_ALIEN_ROWS; i++) {
        for (int j = 0; j < NUM_ALIEN_COLS; j++) {
            if (aliens[i][j].is_alive) {
                // garante que o tipo do alien e o frame de animacao sao validos
                int type = aliens[i][j].type;
                if (type < 0 || type >= 3) type = 0; //fallback para tipo 0
                int frame = current_animation_frame;
                if (frame < 0 || frame >= 2) frame = 0; //fallback para frame 0

                float sx_alien = alien_sprite_coords[type][frame][0];
                float sy_alien = alien_sprite_coords[type][frame][1];

                // desenha a regiao do bitmap na posicao do alien na tela
                al_draw_bitmap_region(alien_sprite, sx_alien, sy_alien, sw_alien, sh_alien, aliens[i][j].x, aliens[i][j].y, 0);
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


//funcao que desenha o tiro do alien
void draw_alien_shot(AlienShot alien_shot) {
    if (alien_shot.is_active) {
        if (alien_shot_sprite) {
            // assume que o tiro do alien esta em uma regiao especifica da alienp.bmp ou outra imagem
            // exemplo: um pequeno retangulo 5x10 px (ALIEN_SHOT_W x ALIEN_SHOT_H)
            float sx_alien_shot = 4; //posicao x de inicio do recorte (ajuste conforme sua spritesheet)
            float sy_alien_shot = 4; //posicao y de inicio do recorte (ajuste conforme sua spritesheet)
            float sw_alien_shot = ALIEN_SHOT_W; //largura do sprite do tiro do alien
            float sh_alien_shot = ALIEN_SHOT_H; //altura do sprite do tiro do alien

            al_draw_bitmap_region(alien_shot_sprite, sx_alien_shot, sy_alien_shot, sw_alien_shot, sh_alien_shot,
                                  alien_shot.x - (float)ALIEN_SHOT_W / 2, alien_shot.y, 0);
        } else {
            // fallback se o sprite nao carregou: desenha um retangulo para o tiro do alien
            al_draw_filled_rectangle(alien_shot.x - (float)ALIEN_SHOT_W / 2, alien_shot.y,
                                     alien_shot.x + (float)ALIEN_SHOT_W / 2, alien_shot.y + ALIEN_SHOT_H,
                                     alien_shot.cor);
        }
    }
}

//funcao que desenha a pontuacao e as vidas na tela
void draw_score_lives(int score, int lives, int high_score) {
    if (score_font) {
        ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255); //branco

        //desenha pontuacao atual
        char score_text[50];
        sprintf(score_text, "pontuacao: %d", score);
        al_draw_text(score_font, text_color, 10, 10, ALLEGRO_ALIGN_LEFT, score_text);

        //desenha vidas
        char lives_text[50];
        sprintf(lives_text, "vidas: %d", lives);
        al_draw_text(score_font, text_color, SCREEN_W - 10, 10, ALLEGRO_ALIGN_RIGHT, lives_text);

        //desenha recorde
        char high_score_text[50];
        sprintf(high_score_text, "recorde: %d", high_score);
        al_draw_text(score_font, text_color, SCREEN_W / 2, 10, ALLEGRO_ALIGN_CENTER, high_score_text);
    }
}


//funcao que desenha a tela de Game Over/Vitória
void draw_game_over_screen(GameState game_state, int final_score, int high_score) {
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

        //desenha pontuacao final
        char final_score_text[50];
        sprintf(final_score_text, "sua pontuacao: %d", final_score);
        al_draw_text(game_font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 - 30,
                     ALLEGRO_ALIGN_CENTER, final_score_text);

        //desenha recorde
        char high_score_text[50];
        sprintf(high_score_text, "recorde: %d", high_score);
        al_draw_text(game_font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 20,
                     ALLEGRO_ALIGN_CENTER, high_score_text);
        
        //desenha a mensagem para reiniciar
        al_draw_text(game_font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 70,
                     ALLEGRO_ALIGN_CENTER, "pressione r para reiniciar ou esc para sair");
        
    } else {
        //fallback se a fonte não carregou
        fprintf(stderr, "Fonte não carregada para tela final.\n");
    }
    al_flip_display(); //atualiza a tela
}

