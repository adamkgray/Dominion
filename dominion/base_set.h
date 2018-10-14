#ifndef BASE_SET_H_
#define BASE_SET_H_

#include "card_stack.h"
#include "add_cards.h"
#include <stdlib.h>

#define VICTORY      1
#define TREASURE     2
#define ACTION       4
#define CURSE        8
#define SUPPLY_PILES 33

struct card_stack ** base_set();

#endif
