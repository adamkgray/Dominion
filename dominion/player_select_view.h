#ifndef PLAYER_SELECT_VIEW_H_
#define PLAYER_SELECT_VIEW_H_

#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include "definitions.h"
#include "interface.h"

void player_select_view(interface * p_interface, int8_t * player_count, char * names);
void select_player_count(interface * p_interface, int8_t * player_count);
void draw_selection(interface * p_interface, int8_t opt);

#endif
