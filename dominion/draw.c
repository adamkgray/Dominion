#include "draw.h"

void draw(struct player * p_player) {
    /* If the deck is empty, transfer all discard to deck and shuffle */
    if (p_player->deck->card_count == 0) {


        /* Transfer all cards from discard to deck */
        while (p_player->discard->card_count > 0) {
            gain(p_player->deck, p_player->discard);
        }

        int n = p_player->deck->card_count;
        randomize_cards(p_player->deck->cards, n);
    }

    /* Gain a card from deck to hand */
    gain(p_player->hand, p_player->deck);
}
