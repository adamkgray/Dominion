#include "gameplay.h"

struct table * gameplay(struct table * p_table) {
    /* Simulate gameplay */
    pop_and_push(p_table->players[p_table->turn]->discard, p_table->supply_piles[3]);

    /* Action phase */
    action_phase(p_table);

    /* Buy phase */
    buy_phase(p_table);

    /* Cleanup phase */
    cleanup_phase(p_table);

    /* Next turn or game over */
    return (end_conditions(p_table)) ? NULL : gameplay(p_table);
}

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
