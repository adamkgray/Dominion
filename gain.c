/* Gain a card from the top of one card stack to the top of another */

#include "gain.h"

int gain(struct card_stack * to, struct card_stack * from) {
    if (from->card_count > 0) {                 /* Only move card if there are cards in the 'from' stack */
        if (to->card_count == to->limit) {      /* No more room, reallocate */
            struct card ** new_cards;
            ++(to->limit);                      /* Increment the limit */
            new_cards = (struct card **)realloc(to->cards, (to->limit) * sizeof(struct card *));
            if (new_cards == NULL) {            /* Return 0 if null pointer was returned */
                return 0;
            }
            to->cards = new_cards;              /* Otherwise set the reallocated pointer */
        }
        --(from->card_count);                   /* Decrement 'from' card count */
        to->cards[to->card_count] = from->cards[from->card_count];  /* Push the top card of the 'from' stack onto the 'to' stack */
        ++(to->card_count);                     /* Increment the 'to' card count */
        return 1;                               /* Return successful int */
    }
    return 0;                                   /* 0 cards in the 'from' stack, return 0 */
}
