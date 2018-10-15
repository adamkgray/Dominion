#include "action_phase.h"

void action_phase(struct table * p_table){
    struct player * p_player = p_table->players[p_table->turn];
    if (p_player->actions == 0) { return; }    /* If player has no more actions, return */

    /* TODO: UI */
    /* Give player option to end actions
    if (user ends actions) {
        return forfeit_actions(p_player);
    }
    */

    /* TODO: UI */
    /* Player moves actions to play area */

    /* Do action card instructions */

    /* decrement actions */
    --(p_player->actions);

    /* call self recursively */
    return action_phase(p_table);
}

void forfeit_actions(struct player * p_player){
    p_player->actions = 0;
    return;
}
