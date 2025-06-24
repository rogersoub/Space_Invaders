#ifndef CONTROLLER_H//se nao tiver o controller, faz o seguinte código: (igual no model)
#define CONTROLLER_H

#include <allegro5/allegro.h>
#include "model.h"//pega somente o model
#include "view.h" //pega a view

//----------------------- variaveis globais de controle de jogo ---------------------------------------
extern int score;
extern int lives;
extern int high_score;
extern int current_alien_animation_frame;

// ---------------- Funções de Controle ----------------
void process_event(ALLEGRO_EVENT ev, Nave *nave, Shot *shot, AlienShot alien_shots[], int num_alien_shots, GameState *current_game_state);

void game_loop(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer);

void reset_game(Nave *nave, Alien aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS], Shot *shot, AlienShot alien_shots[], int num_alien_shots);

#endif