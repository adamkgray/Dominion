#ifndef TABLE_H_
#define TABLE_H_

#include <stdint.h>
#include <stdlib.h>
#include "definitions.h"
#include "cards.h"
#include "player.h"

typedef struct {
    int8_t turn;
    int8_t player_count;
    player ** players;
    card_stack ** supply_piles;
} table;

table * new_table(card_stack ** supply_piles, int8_t player_count, char * names);

#endif
