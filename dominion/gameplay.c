#include "gameplay.h"

struct table * gameplay(struct table * p_table) {
    /* Simulate gameplay */
    static int turn_counter = 1;
    printf("%d\n", turn_counter);
    pop_and_push(p_table->players[p_table->turn]->discard, p_table->supply_piles[3]);
    ++turn_counter;

    /* Action phase */
    action_phase(p_table);

    /* Buy phase */
    buy_phase(p_table);

    /* Cleanup phase */
    cleanup_phase(p_table);

    /* Next turn or game over */
    return (end_conditions(p_table)) ? NULL : gameplay(p_table);
}
