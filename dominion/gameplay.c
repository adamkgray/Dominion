#include "gameplay.h"

struct table * gameplay(struct table * p_table) {
    static int turn = 1;
    static int nc = 7;

    if (nc == 16) {
        nc = 7;
    } else {
        ++nc;
    }

    gain(p_table->players[p_table->turn]->discard, p_table->supply_piles[nc]);

    for (int i = 0; i < 5; ++i) {
        printf("%s\t", p_table->players[p_table->turn]->hand->cards[i]->name);
    }
    printf("\n");

    /* Cleanup phase */
    cleanup_phase(p_table);

    /* Pause */

    /* Next turn or game over */
    return (end_conditions(p_table)) ? NULL : gameplay(p_table);
}
