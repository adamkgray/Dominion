#include "gameplay.h"

table * gameplay(interface * p_interface, table * p_table) {
    /* Action phase */
    /* Turn off action phase for dev */
    //action_phase(p_table);

    /* Buy phase */
    buy_phase(p_table);

    /* Cleanup phase */
    cleanup_phase(p_table);

    /* Next turn or game over */
    return (end_conditions(p_table)) ? NULL : gameplay(p_interface, p_table);
}

/* Game end conditions:
 * - All of the provinces are gone
 * - Any three supply piles are gone
 */

int8_t end_conditions(table * p_table) {
    /* Provinces are gone */
    if (p_table->supply_piles[PROVINCE]->card_count == 0) { return 1; }

    /* Any three supply piles are gone */
    int8_t empty_supply_piles = 0;
    for (int8_t i = 7; i < SUPPLY_PILES; ++i) {
        empty_supply_piles += (p_table->supply_piles[i]->card_count == 0) ? 1 : 0;
    }
    if (empty_supply_piles >= 3) { return 1; }

    /* The game is not yet over */
    return 0;
}
