#ifndef BUY_PHASE_H_
#define BUY_PHASE_H_

#include "table.h"
#include "card_stack.h"
#include "player.h"
#include "base_set.h"

void buy_phase(struct table * p_table);
void forfeit_buys(struct player * p_player);

#endif
