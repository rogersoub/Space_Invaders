#ifndef CONTROLLER_H//se nao tiver o controller, faz o seguinte código: (igual no model)
#define CONTROLLER_H

#include <allegro5/allegro.h>
#include "model.h"//pega somente o model

// ---------------- Funções de Controle ----------------
void process_event(ALLEGRO_EVENT ev, Nave *nave, Shot *shot, GameState *current_game_state);
void game_loop(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer);

#endif