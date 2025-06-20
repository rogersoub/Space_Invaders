#ifndef CONTROLLER_H//se nao tiver o controller, faz o seguinte código: (igual no model)
#define CONTROLLER_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>//origem do rand
#include <allegro5/allegro_primitives.h>//local que vem as primitivas
#include "src/model/model.h"//pega somente o model

// ---------------- Funções de Controle ----------------
void process_event(ALLEGRO_EVENT ev, Nave *nave, int *playing);
void game_loop(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer);

#endif