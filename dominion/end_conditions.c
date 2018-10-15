#include "end_conditions.h"

/* Game end conditions:
 * - All of the provinces are gone
 * - Any three supply piles are gone
 */

int end_conditions(struct table * p_table) {
    /* Provinces are gone */
    if (p_table->supply_piles[PROVINCE]->card_count == 0) { return 1; }

    /* Any three supply piles are gone */
    int i, empty_supply_piles = 0;
    for (i = 7; i < SUPPLY_PILES; ++i) {
        empty_supply_piles += (p_table->supply_piles[i]->card_count == 0) ? 1 : 0;
    }
    if (empty_supply_piles >= 3) { return 1; }

    /* The game is not yet over */
    return 0;
}
