#ifndef TABLE_H_
#define TABLE_H_

#include "card_stack.h"
#include "player.h"

#define COPPER 4
#define ESTATE 1

struct table {
    int turn;
    int player_count;
    struct player ** players;
    struct card_stack ** supply_piles;
};

struct table * new_table(struct card_stack ** supply_piles, int player_count, char ** names);

#endif
