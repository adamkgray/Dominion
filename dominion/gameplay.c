#include "gameplay.h"

struct table * gameplay(struct table * p_table) {
    static int turn = 1;
    /* Cleanup phase */
    cleanup_phase(p_table);

    /* Pause */
    printf("Turn: %d\n", turn++);
    getchar();

    /* Next turn or game over */
    return (end_conditions(p_table)) ? NULL : gameplay(p_table);
}
