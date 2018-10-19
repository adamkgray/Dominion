#ifndef PHASES_H_
#define PHASES_H_

#include <stdint.h>
#include "table.h"
#include "cards.h"
#include "player.h"
#include "execute_instructions.h"
#include "draw.h"
#include "phase_views.h"

void cleanup_phase(table * p_table);
void action_phase(table * p_table);
void forfeit_actions(player * p_player);
void buy_phase(table * p_table);
void forfeit_buys(player * p_player);

#endif
