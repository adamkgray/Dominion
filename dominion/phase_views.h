#ifndef PHASE_VIEWS_H_
#define PHASE_VIEWS_H_

#include <stdint.h>
#include <ncurses.h>
#include "table.h"
#include "player.h"

void buy_phase_view(table * p_table, player * p_player, int8_t * p_play_area_value);

#endif
