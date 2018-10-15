#include "cleanup_phase.h"

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
    ++(p_player->actions);
    ++(p_player->buys);

    /* Next turn */
    p_table->turn = (p_table->turn == p_table->player_count - 1) ? 0 : p_table->turn + 1;
}
