/* Dominion */

#include <ncurses.h>
#include <stdlib.h>

#include "table.h"
#include "add_cards.h"

#define VICTORY  1
#define TREASURE 2
#define ACTION   4
#define CURSE    8

int main(void) {
    int i;
    int * instructions;
    const int SUPPLY_PILES = 33;
    struct card_stack * BASE_SET[SUPPLY_PILES], ** p_base_set = BASE_SET;
    int CARD_COUNTS[] = {
        24, 12, 12,
        60, 40, 30,
        10, 10, 10,
        10, 10, 10,
        10, 10, 10,
        12, 10, 10,
        10, 10, 10,
        10, 10, 10,
        10, 10, 10,
        10, 10, 10,
        10, 10, 30
    }, * p_card_counts = CARD_COUNTS;

    /* Initialize new card stacks */
    for (p_base_set = BASE_SET, p_card_counts = CARD_COUNTS, i = 0; i < SUPPLY_PILES; ++i) {
        *(p_base_set++) = new_card_stack(*(p_card_counts++));
    }

    /* Check for NULL pointers */
    for (i = 0, p_base_set = BASE_SET; i < SUPPLY_PILES; ++i) {
        if (*(p_base_set++) == NULL) {
            return 1;
        }
    }

    p_base_set = BASE_SET;
    if (!add_cards(24, VICTORY,  "Estate",       2, 1, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(12, VICTORY,  "Duchy",        5, 3, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(12, VICTORY,  "Province",     8, 6, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(60, TREASURE, "Copper",       0, 1, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(40, TREASURE, "Silver",       3, 2, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(30, TREASURE, "Gold",         6, 3, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Cellar",       2, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Chapel",       2, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Moat",         2, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Harbinger",    3, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Merchant",     3, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Vassal",       3, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Village",      3, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Workshop",     3, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Bureaucrat",   4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(12, ACTION,   "Gardens",      4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Militia",      4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Moneylender",  4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Poacher",      4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Remodel",      4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Smithy",       4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Throne Room",  4, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Bandit",       5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Council Room", 5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Festival",     5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Laboratory",   5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Library",      5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Market",       5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Mine",         5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Sentry",       5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Witch",        5, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(10, ACTION,   "Artisan",      6, 0, instructions, *(p_base_set++))) { return 1; }
    if (!add_cards(30, CURSE,    "Curse",        0, 0, instructions, *(p_base_set)))   { return 1; }

    printf("Dominion base initialized\n");

    return 0;
}
