#ifndef ACTION_PHASE_H_
#define ACTION_PHASE_H_

#include "table.h"
#include "player.h"
#include "execute_instructions.h"

void action_phase(struct table * p_table);
void forfeit_actions(struct player * p_player);

#endif
