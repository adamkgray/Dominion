#ifndef PHASES_H_
#define PHASES_H_

#include "table.h"
#include "cards.h"
#include "player.h"
#include "dominion_base.h"
#include "execute_instructions.h"
#include "draw.h"

void cleanup_phase(struct table * p_table);
void action_phase(struct table * p_table);
void forfeit_actions(struct player * p_player);
void buy_phase(struct table * p_table);
void forfeit_buys(struct player * p_player);

#endif
