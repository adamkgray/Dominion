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
    if (p_table == NULL) { fprintf(stderr, "Memory error"); return 1; }

    each_player_shuffles_their_deck_and_draws_five_cards(p_table);

    /* Begin the game */
    gameplay(p_table);

    return 0;
}
