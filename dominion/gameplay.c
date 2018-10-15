#include "gameplay.h"

struct table * gameplay(struct table * p_table) {
    /* Simulate gameplay */
    static int turn = 1;
    static int nc = 7;

    if (nc == 16) {
        nc = 7;
    } else {
        ++nc;
    }

    pop_and_push(p_table->players[p_table->turn]->discard, p_table->supply_piles[nc]);

    for (int i = 0; i < 5; ++i) {
        printf("%s\t", p_table->players[p_table->turn]->hand->cards[i]->name);
    }
    printf("\nTURN: %d\n", turn);
    ++turn;
    /* end simuate gameplay */


    /* Action phase */
    action_phase(p_table);

    /* Buy phase */
    buy_phase(p_table);

    /* Cleanup phase */
    cleanup_phase(p_table);

    /* Next turn or game over */
    return (end_conditions(p_table)) ? NULL : gameplay(p_table);
}
