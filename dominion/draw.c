#include "draw.h"

void draw(struct player * p_player) {
    /* If the deck is empty, transfer all discard to deck and shuffle */
    if (p_player->deck->card_count == 0) {
        /* Transfer all cards from discard to deck */
        while (p_player->discard->card_count > 0) {
            pop_and_push(p_player->deck, p_player->discard);
        }
        /* Shuffle */
        int n = p_player->deck->card_count;
        randomize_cards(p_player->deck->cards, n);
    }
    /* Move card from deck to hand */
    pop_and_push(p_player->hand, p_player->deck);
}
