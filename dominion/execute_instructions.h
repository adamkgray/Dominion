#ifndef EXECUTE_INSTRUCTIONS_H_
#define EXECUTE_INSTRUCTIONS_H_

#include <stdint.h>
#include "definitions.h"
#include "cards.h"
#include "table.h"
#include "draw.h"

void execute_action_card_instructions(card * action_card, table * p_table);
void execute_instruction(int8_t instruction, table * p_table);
void each_other_player_draws_card(table * p_table);
void gain_gold_to_hand(player * p_player, table * p_table);
void gain_silver_to_deck(player * p_player, table * p_table);
void each_other_player_gains_curse(table * p_table);

#endif
