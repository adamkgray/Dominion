#ifndef RENDER_H_
#define RENDER_H_

#include <ncurses.h>
#include "interface.h"
#include "player.h"
#include "table.h"
#include "cards.h"

void render_title(interface * p_interface);
void render_hand(interface * p_interface, player * p_player, int8_t opt_y);
void render_supply_piles(interface * p_interface, table * p_table, int8_t opt_y);
void render_play_area(interface * p_interface, player * p_player);
void clear_play_area(interface * p_interface, player * p_player);
void render_status(interface * p_interface, table * p_table, player * p_player, char * phase);
void render_discard(interface * p_interface, player * p_player, int8_t opt_y);
void render_table(interface * p_interface, table * p_table, player * p_player, char * phase);

#endif
