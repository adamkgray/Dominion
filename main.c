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
    struct card_stack * BASE_SET[33], ** p_base_set = BASE_SET;

    BASE_SET[0]  = new_card_stack(24);     /*  estates */
    BASE_SET[1]  = new_card_stack(12);     /*  duchies */
    BASE_SET[2]  = new_card_stack(12);     /*  provinces */
    BASE_SET[3]  = new_card_stack(60);     /*  coppers */
    BASE_SET[4]  = new_card_stack(40);     /*  silvers */
    BASE_SET[5]  = new_card_stack(30);     /*  golds */
    BASE_SET[6]  = new_card_stack(10);     /*  cellars */
    BASE_SET[7]  = new_card_stack(10);     /*  chapels */
    BASE_SET[8]  = new_card_stack(10);     /*  moats */
    BASE_SET[9]  = new_card_stack(10);     /*  harbingers */
    BASE_SET[10] = new_card_stack(10);     /*  merchants */
    BASE_SET[11] = new_card_stack(10);     /*  vassals */
    BASE_SET[12] = new_card_stack(10);     /*  village */
    BASE_SET[13] = new_card_stack(10);     /*  workshops */
    BASE_SET[14] = new_card_stack(10);     /*  bureaucrats */
    BASE_SET[15] = new_card_stack(12);     /*  gardens */
    BASE_SET[16] = new_card_stack(10);     /*  militias */
    BASE_SET[17] = new_card_stack(10);     /*  moneylenders */
    BASE_SET[18] = new_card_stack(10);     /*  poachers */
    BASE_SET[19] = new_card_stack(10);     /*  remodels */
    BASE_SET[20] = new_card_stack(10);     /*  smithies */
    BASE_SET[21] = new_card_stack(10);     /*  throne_rooms */
    BASE_SET[22] = new_card_stack(10);     /*  bandits */
    BASE_SET[23] = new_card_stack(10);     /*  council_rooms */
    BASE_SET[24] = new_card_stack(10);     /*  festivals */
    BASE_SET[25] = new_card_stack(10);     /*  laboratories */
    BASE_SET[26] = new_card_stack(10);     /*  libraries */
    BASE_SET[27] = new_card_stack(10);     /*  markets */
    BASE_SET[28] = new_card_stack(10);     /*  mines */
    BASE_SET[29] = new_card_stack(10);     /*  sentries */
    BASE_SET[30] = new_card_stack(10);     /*  witches */
    BASE_SET[31] = new_card_stack(10);     /*  artisans */
    BASE_SET[32] = new_card_stack(30);     /*  curses */

    /* Check for NULL pointers */
    for (i = 0; i < SUPPLY_PILES; ++i) {
        if (BASE_SET[i] == NULL) {
            return 1;
        }
    }

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
    if (!add_cards(10, ACTION,   "Gardens",      4, 0, instructions, *(p_base_set++))) { return 1; }
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
    if (!add_cards(10, CURSE,    "Artisan",      0, 0, instructions, *(p_base_set)))   { return 1; }

    printf("Dominion base initialized\n");

    return 0;
}
