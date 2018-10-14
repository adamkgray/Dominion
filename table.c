#include "table.h"

struct table * new_table(int player_count, char ** names) {
    int i;
    struct table * p_table = (struct table *)malloc(sizeof(struct table));  /* Create new table */
    if (p_table == NULL) { return NULL; }
    struct player ** p_players = (struct player **)malloc(player_count * sizeof(struct player *));  /* Create players array */
    if (p_players == NULL) { return NULL; }
    for (i = 0; i < player_count; ++i) {        /* Create new players */
        p_players[i] = new_player(names[i]);
        if (p_players[i] == NULL) { return NULL; }
    }
    p_table->players = p_players;               /* Set players in player array */
    p_table->player_count = player_count;       /* Set player count */
    p_table->turn = 0;                          /* Player 0 goes first */
    return p_table;
}
