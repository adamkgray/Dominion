#include "table.h"

table * new_table(card_stack ** supply_piles, int8_t player_count, char * names) {
    if (supply_piles == NULL) { return NULL; }  /* If the supply piles didn't initialize, return NULL */

    table * p_table = (table *)malloc(sizeof(table));  /* Create new table */
    if (p_table == NULL) { return NULL; }

    player ** p_players = (player **)malloc(player_count * sizeof(player *));  /* Create players array */
    if (p_players == NULL) { return NULL; }

    for (int8_t i = 0; i < player_count; ++i) {        /* Create new players */
        p_players[i] = new_player(names + (8 * i));
        if (p_players[i] == NULL) { return NULL; }

        for (int8_t j = 0; j < 7; ++j) { /* 7 coppers */
            pop_and_push(p_players[i]->deck, supply_piles[COPPER]);
        }

        for (int8_t j = 0; j < 3; ++j) { /* 3 estates */
            pop_and_push(p_players[i]->deck, supply_piles[ESTATE]);
        }
    }

    /* Reallocate memory for fewer coppers */
    card ** coppers = (card **)realloc(supply_piles[COPPER]->cards, supply_piles[COPPER]->card_count * sizeof(card *));
    if (coppers == NULL) {
        return NULL;
    } else {
        supply_piles[COPPER]->cards = coppers;
    }

    /* Reallocate memory for fewer estates */
    card ** estates = (card **)realloc(supply_piles[ESTATE]->cards, supply_piles[ESTATE]->card_count * sizeof(card *));
    if (estates == NULL) {
        return NULL;
    } else {
        supply_piles[ESTATE]->cards = estates;
    }

    p_table->players = p_players;         /* Set players in player array */
    p_table->player_count = player_count; /* Set player count */
    p_table->turn = 0;                    /* Player 0 goes first */
    p_table->play_area_value = 0;         /* Play area starts with no coin */
    p_table->supply_piles = supply_piles; /* Set supply piles */

    return p_table;
}
