#include "each_player_shuffles_their_deck_and_draws_five_cards.h"

void each_player_shuffles_their_deck_and_draws_five_cards(struct table * p_table) {
    int i, j;
    /* Shuffle decks */
    for (i = 0; i < p_table->player_count; ++i) {
        randomize_cards(p_table->players[i]->deck->cards, 10);
    }
    /* Draw five cards */
    for (i = 0; i < p_table->player_count; ++i) {
        for (j = 0; j < 5; ++j) {
            draw(p_table->players[i]);
        }
    }
}
