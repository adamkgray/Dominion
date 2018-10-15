#ifndef BASE_SET_H_
#define BASE_SET_H_

#include <stdlib.h>
#include "card_stack.h"

#define VICTORY      1
#define TREASURE     2
#define ACTION       4
#define CURSE        8
#define BASE_COUNT   33
#define SUPPLY_PILES 17

struct card_stack ** base_set();

#endif
