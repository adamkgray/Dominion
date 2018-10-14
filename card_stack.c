#include "card_stack.h"
#include <stdio.h>

struct card_stack * new_card_stack(int limit) {
    struct card_stack * p_card_stack = (struct card_stack *)malloc(sizeof(struct card_stack));
    if (p_card_stack == NULL) {
        return NULL;                    /* Return NULL if not enough memory for new card stack */
    }
    struct card ** new_cards = (struct card **)malloc(limit * sizeof(struct card *));
    if (new_cards == NULL) {
        return NULL;                    /* Return NULL if not enough memory for new card list */
    }
    p_card_stack->limit = limit;        /* Limit is the same as size of cards allocated */
    p_card_stack->card_count = 0;       /* There are initaily no cards in the stack */
    p_card_stack->cards = new_cards;
    return p_card_stack;                /* Return pointer to new card stack */
}
