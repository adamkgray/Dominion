#ifndef PHASES_H_
#define PHASES_H_

#include <stdint.h>
#include "interface.h"
#include "table.h"
#include "cards.h"
#include "player.h"
#include "draw.h"
#include "phase_views.h"

void cleanup_phase(interface * p_interface, table * p_table);
void action_phase(interface * p_interface, table * p_table);
void buy_phase(interface * p_interface, table * p_table);

#endif
