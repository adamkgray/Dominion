#include "table.h"

struct table * new_table(struct card_stack ** supply_piles, int player_count, char ** names) {
    int i, j;

    if (supply_piles == NULL) { return NULL; }  /* If the supply piles didn't initialize, return NULL */

    struct table * p_table = (struct table *)malloc(sizeof(struct table));  /* Create new table */
    if (p_table == NULL) { return NULL; }

    struct player ** p_players = (struct player **)malloc(player_count * sizeof(struct player *));  /* Create players array */
    if (p_players == NULL) { return NULL; }

    for (i = 0; i < player_count; ++i) {        /* Create new players */
        p_players[i] = new_player(names[i]);
        if (p_players[i] == NULL) { return NULL; }
        /* No need to check for enough memory because supply piles and player decks are intiailized with enough space */
        for (j = 0; j < 7; ++j) { pop_and_push(p_players[i]->deck, supply_piles[COPPER]); } /* 7 coppers */
        for (j = 0; j < 3; ++j) { pop_and_push(p_players[i]->deck, supply_piles[ESTATE]); } /* 3 estates */
    }

    p_table->players = p_players;               /* Set players in player array */
    p_table->player_count = player_count;       /* Set player count */
    p_table->turn = 0;                          /* Player 0 goes first */
    p_table->supply_piles = supply_piles;       /* Set supply piles */

    return p_table;
}
