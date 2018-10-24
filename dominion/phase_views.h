#ifndef PHASE_VIEWS_H_
#define PHASE_VIEWS_H_

#include <stdint.h>
#include <ncurses.h>
#include "definitions.h"
#include "execute_instructions.h"
#include "interface.h"
#include "table.h"
#include "player.h"

void buy_phase_view(interface * p_interface, table * p_table, player * p_player);
void select_treasure(interface * p_interface, table * p_table, player * p_player, int8_t * opt_x, int8_t * opt_y, int16_t * c);
void action_phase_view(interface * p_interface, table * p_table, player * p_player);
void select_action_card(interface * p_interface, table * p_table, player * p_player, int8_t * opt_y, int16_t * c);
void draw_table(interface * p_interface, table * p_table, player * p_player, int8_t opt_x, int8_t opt_y, char * phase);

#endif
