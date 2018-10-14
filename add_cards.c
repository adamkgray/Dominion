#include "add_cards.h"
#include <stdio.h>

int push(struct card * new_card, struct card_stack * to) {  /* Routine which pushes a card directly onto a stack */
    if (to->card_count == to->limit) {                      /* Used to initialize a stack when there are no other stacks to take from */
        struct card ** new_cards;                           /* Reallocate memory if limit is reached */
        ++(to->limit);                                      /* Increment limit */
        new_cards = (struct card **)realloc(to->cards, (to->limit) * sizeof(struct card *));
        if (new_cards == NULL) {                            /* Return NULL if not enough memory */
            return 0;
        }
        to->cards = new_cards;                              /* Otherwise set the reallocated pointer */
    }
    to->cards[to->card_count] = new_card;                   /* Add the new card to the stack */
    to->card_count += 1;                                    /* Increment card count */
    return 1;
}

int add_cards(int n, int type, char * name, int cost, int value, int * instructions, struct card_stack * to) {
    int i;                                                          /* Routine which creates a card and adds it to a stack n times */
    struct card * p_card;                                           /* Card pointer to be reused */
    for (i = 0; i < n; ++i) {
        p_card = new_card(type, name, cost, value, instructions);   /* Create the new card */
        if (p_card == NULL) { return 0; }                           /* Return 0 if not enough memory */
        if (!push(p_card, to)) { return 0; }                        /* Return zero if the stack could not accept the new card */
    }
    return 1;                                                       /* Return 1 for success */
}
