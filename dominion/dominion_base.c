#include "dominion_base.h"

card_stack ** base_set() {
    card_stack ** base_set = (card_stack **)malloc(BASE_COUNT * sizeof(card_stack *));
    if (base_set == NULL) { return NULL; }
    card_stack ** p_base_set = base_set;

    int8_t CARD_COUNTS[] = {
        30, 24, 12,     /* Curse, Estate, Duchy */
        12, 60, 40,     /* Province, Copper, Silver */
        30, 10, 10,     /* Gold, Cellar, Chapel */
        10, 10, 10,     /* Moat, Harbinger, Merchant */
        10, 10, 10,     /* Vassal, Village, Workshop */
        10, 12, 10,     /* Bureaucrat, Gardens, Militia */
        10, 10, 10,     /* Moneylender, Poacher, Remodel */
        10, 10, 10,     /* Smithy, Throne Room, Bandit */
        10, 10, 10,     /* Council Room, Festival, Laboratory */
        10, 10, 10,     /* Library, Market, Mine */
        10, 10, 10      /* Sentry, Witch, Artisan */
    }, * p_card_counts = CARD_COUNTS;

    /* Initialize new card stacks */
    int8_t i;
    for (i = 0, p_base_set = base_set, p_card_counts = CARD_COUNTS; i < BASE_COUNT; ++i) {
        *(p_base_set++) = new_card_stack(*(p_card_counts++));
    }

    /* Check for NULL pointers */
    for (i = 0, p_base_set = base_set; i < BASE_COUNT; ++i) {
        if (*(p_base_set++) == NULL) { return NULL; }
    }

    int8_t witch_instr[]           = {PLUS_CARD, PLUS_CARD, EACH_OTHER_PLAYER_GAINS_CURSE};
    int8_t cellar_instr[]          = {PLUS_ACTION};
    int8_t chapel_instr[]          = {TRASH_UP_TO_FOUR_CARDS};
    int8_t moat_instr[]            = {PLUS_CARD, PLUS_CARD};
    int8_t harbinger_instr[]       = {PLUS_CARD, PLUS_ACTION};
    int8_t merchant_instr[]        = {PLUS_CARD, PLUS_ACTION};
    int8_t vassal_instr[]          = {PLUS_COIN, PLUS_COIN};
    int8_t village_instr[]         = {PLUS_CARD, PLUS_ACTION, PLUS_ACTION};
    int8_t workshop_instr[]        = {GAIN_CARD_COSTING_UP_TO_FOUR};
    int8_t bureaucrat_instr[]      = {GAIN_SILVER_TO_DECK};
    int8_t militia_instr[]         = {PLUS_COIN, PLUS_COIN};
    int8_t moneylender_instr[]     = {TRASH_COPPER_FOR_PLUS_THREE};
    int8_t poacher_instr[]         = {PLUS_CARD, PLUS_ACTION, PLUS_COIN, DISCARD_A_CARD_PER_EMPTY_SUPPLY_PILE};
    int8_t remodel_instr[]         = {TRASH_CARD_AND_GAIN_ONE_COASTING_UP_TO_TWO_MORE};
    int8_t smithy_instr[]          = {PLUS_CARD, PLUS_CARD, PLUS_CARD};
    int8_t throne_room_instr[]     = {PLAY_ACTION_CARD_FROM_HAND_TWICE};
    int8_t bandit_instr[]          = {GAIN_GOLD_TO_HAND};
    int8_t council_room_instr[]    = {PLUS_CARD, PLUS_CARD, PLUS_CARD, PLUS_CARD, PLUS_BUY, EACH_OTHER_PLAYER_DRAWS_CARD};

    p_base_set = base_set;

    /*         #cards  type                 name         cost value instructions        place in base_set               */
    if (!add_cards(30, CURSE,               "Curse",        0, -1,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(24, VICTORY,             "Estate",       2,  1,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(12, VICTORY,             "Duchy",        5,  3,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(12, VICTORY,             "Province",     8,  6,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(60, TREASURE,            "Copper",       0,  1,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(40, TREASURE,            "Silver",       3,  2,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(30, TREASURE,            "Gold",         6,  3,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Cellar",       2,  0,  cellar_instr,       *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Chapel",       2,  0,  chapel_instr,       *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION + REACTION,   "Moat",         2,  0,  moat_instr,         *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Harbinger",    3,  0,  harbinger_instr,    *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Merchant",     3,  0,  merchant_instr,     *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Vassal",       3,  0,  vassal_instr,       *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Village",      3,  0,  village_instr,      *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Workshop",     3,  0,  workshop_instr,     *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Bureaucrat",   4,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(12, GARDEN + VICTORY,    "Gardens",      4,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Militia",      4,  0,  militia_instr,      *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Moneylender",  4,  0,  moneylender_instr,  *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Poacher",      4,  0,  poacher_instr,      *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Remodel",      4,  0,  remodel_instr,      *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Smithy",       4,  0,  smithy_instr,       *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Throne Room",  4,  0,  throne_room_instr,  *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Bandit",       5,  0,  bandit_instr,       *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Council Room", 5,  0,  council_room_instr, *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Festival",     5,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Laboratory",   5,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Library",      5,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Market",       5,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Mine",         5,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Sentry",       5,  0,  NULL,               *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Witch",        5,  0,  witch_instr,        *(p_base_set++))) { return NULL; }
    if (!add_cards(10, ACTION,              "Artisan",      6,  0,  NULL,               *(p_base_set)))   { return NULL; }

    return base_set;
}

card_stack ** select_playing_cards(card_stack ** base_set) {
    card_stack ** reduced_base_set = (card_stack **)malloc(SUPPLY_PILES * sizeof(card_stack *));
    if (reduced_base_set == NULL) { return NULL; }
    int8_t action_card_indeces[] = {
        7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
    }, n = N_ELEMS(action_card_indeces), i, j;
    randomize_indeces(action_card_indeces, n);
    for (i = 0; i < 7; ++i) { reduced_base_set[i] = base_set[i]; }
    for (j = 0; j < 10; ++j, ++i) { reduced_base_set[i] = base_set[action_card_indeces[j]]; }
    for (i = 0; i < BASE_COUNT; ++i) { base_set[i] = NULL; }
    free(base_set);
    return reduced_base_set;
}
