#ifndef ACTION_PHASE_H_
#define ACTION_PHASE_H_

#include "table.h"
#include "card.h"
#include "card_stack.h"
#include "draw.h"
#include "player.h"
#include "base_set.h"


void action_phase(struct table * p_table);
void execute_action_card_instructions(struct card * action_card, struct table * p_table);
void execute_instruction(int instruction, struct table * p_table);
void forfeit_actions(struct player * p_player);

#endif
