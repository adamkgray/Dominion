#ifndef EXECUTE_INSTRUCTIONS_H_
#define EXECUTE_INSTRUCTIONS_H_

#include "definitions.h"
#include "cards.h"
#include "table.h"
#include "draw.h"

void execute_action_card_instructions(struct card * action_card, struct table * p_table);
void execute_instruction(int instruction, struct table * p_table);
void each_other_player_draws_card(struct table * p_table);
void gain_gold_to_hand(struct player * p_player, struct table * p_table);
void gain_silver_to_deck(struct player * p_player, struct table * p_table);
void each_other_player_gains_curse(struct table * p_table);

#endif
