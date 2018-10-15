#include "buy_phase.h"

void buy_phase(struct table * p_table) {
    struct player * p_player = p_table->players[p_table->turn];
    if (p_player->buys == 0) { return; }    /* If player has no more buys, return */

    /* TODO: UI */
    /* Give player option to end buys
    if (user ends buys) {
        return forfeit_buys(p_player);
    }
    */

    /* TODO: UI */
    /* Player moves treasures to play area */

    /* TODO: UI */
    /* Count up value added to play area */

    /* TODO: UI */
    /* Let player buy stuff */

    /* decrement buys */
    --(p_player->buys);

    /* call self recursively */
    return buy_phase(p_table);
}

void forfeit_buys(struct player * p_player) {
    p_player->buys = 0;
    return;
}
