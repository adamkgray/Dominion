#include "phases.h"

void cleanup_phase(interface * p_interface, table * p_table) {
    /* Get pointer to player whose turn it is */
    player * p_player = p_table->players[p_table->turn];

    clear_play_area(p_interface, p_player);

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

void action_phase(interface * p_interface, table * p_table){
    player * p_player = p_table->players[p_table->turn];
    while (p_player->actions > 0) {
        action_phase_view(p_interface, p_table, p_player);
    }
    return;
}

void buy_phase(interface * p_interface, table * p_table) {
    player * p_player = p_table->players[p_table->turn];
    while (p_player->buys > 0) {
        buy_phase_view(p_interface, p_table, p_player);
    }
    return;
}
