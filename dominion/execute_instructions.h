#ifndef EXECUTE_INSTRUCTIONS_H_
#define EXECUTE_INSTRUCTIONS_H_

#include <stdint.h>
#include <ncurses.h>
#include "interface.h"
#include "definitions.h"
#include "cards.h"
#include "table.h"
#include "draw.h"

void execute_action_card_instructions(interface * p_interface, int32_t instructions, table * p_table);
void execute_instruction(interface * p_interface, int8_t instruction, table * p_table);
void each_other_player_draws_card(table * p_table);
int8_t gain_gold(player * p_player, table * p_table);
int8_t gain_silver_to_deck(player * p_player, table * p_table);
void each_other_player_gains_curse(table * p_table);
void trash_up_to_four_cards(interface * p_interface, player * p_player, int8_t opt_y, int8_t trashes);
void gain_card_costing_up_to_four(interface * p_interface, table * p_table, player * p_player, int8_t opt_y);
void trash_copper_for_plus_three(interface * p_interface, table * p_table, player * p_player, int8_t opt_y);
void trash_card_and_gain_one_costing_up_to_two_more(interface * p_interface, table * p_table, player * p_player, int8_t opt_x, int8_t opt_y);

#endif
