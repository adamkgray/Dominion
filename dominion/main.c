/* Dominion */
#include "table.h"
#include "select_playing_cards.h"
#include <stdio.h>

int main(void) {
    int player_count = 2;
    char * names[player_count];
    names[0] = "human";
    names[1] = "cpu";
    struct table * p_table = new_table(select_playing_cards(base_set()), player_count, names);
    if (p_table == NULL) { fprintf(stderr, "Not enough memory available to play dominion\n"); return 1; }
    return 0;
}
