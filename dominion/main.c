/* Dominion */
#include "headers.h"

int main(void) {
    /* Gather plyer details */
    int player_count = 2;
    char * names[player_count];
    names[0] = "human";
    names[1] = "cpu";

    /* Create a new table */
    struct table * p_table = new_table(select_playing_cards(base_set()), player_count, names);
    if (p_table == NULL) { fprintf(stderr, "Not enough memory available to play dominion\n"); return 1; }

    /* Each player shuffles their deck of 10 cards */
    int i, j;
    for (i = 0; i < p_table->player_count; ++i) {
        randomize_cards(p_table->players[i]->deck->cards, 10);
    }

    /* Each player draws 5 cards */
    for (i = 0; i < p_table->player_count; ++i) {
        for (j = 0; j < 5; ++j) {
            draw(p_table->players[i]);
        }
    }

    /* Begin the game */
    gameplay(p_table);

    return 0;
}
