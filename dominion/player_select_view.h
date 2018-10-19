#ifndef PLAYER_SELECT_VIEW_H_
#define PLAYER_SELECT_VIEW_H_

#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <ctype.h>
#include "definitions.h"
#include "interface.h"

void player_select_view(interface * p_interface, int8_t * player_count, int8_t * player_types, char * names);
void select_player_count(interface * p_interface, int8_t * player_count, int8_t option);
void human_or_cpu(interface * p_interface, int8_t player_count, int8_t * player_types, int8_t option);
void enter_names(interface * p_interface, int8_t player_count, int8_t player_types, char * names, int8_t option, int8_t pos);

#endif
