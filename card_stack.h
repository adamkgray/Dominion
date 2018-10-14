#ifndef CARD_STACK_H_
#define CARD_STACK_H_

#include <stdlib.h>
#include "card.h"

struct card_stack {
    int card_count;         /* Number of cards currently in the stack */
    int limit;              /* Max number of cards that have been in this stack at one time */
    struct card ** cards;   /* Array of cards */
};

struct card_stack * new_card_stack(int limit);

#endif
