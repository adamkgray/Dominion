#include "phases.h"

void cleanup_phase(struct table * p_table) {
    /* Get pointer to player whose turn it is */
    struct player * p_player = p_table->players[p_table->turn];

    /* Transfer all cards in hand to discard pile */
    while (p_player->hand->card_count > 0) {
        pop_and_push(p_player->discard, p_player->hand);
    }

    /* Tranfer all cards in play area to discard pile */
    while (p_player->play_area->card_count > 0) {
        pop_and_push(p_player->discard, p_player->play_area);
    }

    /* Draw 5 new cards */
    while (p_player->hand->card_count < 5) {
        draw(p_player);
    }

    /* Player gets 1 action and 1 buy */
    p_player->actions = 1;
    p_player->buys = 1;

    /* Next turn */
    p_table->turn = (p_table->turn == p_table->player_count - 1) ? 0 : p_table->turn + 1;
}

void action_phase(struct table * p_table){
    struct player * p_player = p_table->players[p_table->turn];
    if (p_player->actions == 0) { return; }    /* If player has no more actions, return */

    /* TODO: UI */
    /* Give player option to end actions */

    /* TODO: UI */
    /* Player moves an action card to play area */

    /* decrement actions */
    --(p_player->actions);

    /* call self recursively */
    return action_phase(p_table);
}

void forfeit_actions(struct player * p_player) {
    p_player->actions = 0;
    return;
}

void buy_phase(struct table * p_table) {
    struct player * p_player = p_table->players[p_table->turn];
    if (p_player->buys == 0) { return; }    /* If player has no more buys, return */

    /* TODO: UI */
    /* Give player option to end buys */

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
