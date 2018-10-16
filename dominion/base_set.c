#include "base_set.h"

struct card_stack ** base_set() {
    struct card_stack ** base_set = (struct card_stack **)malloc(BASE_COUNT * sizeof(struct card_stack *));
    if (base_set == NULL) { return NULL; }
    struct card_stack ** p_base_set = base_set;

    int CARD_COUNTS[] = {
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
    int i;
    for (p_base_set = base_set, p_card_counts = CARD_COUNTS, i = 0; i < BASE_COUNT; ++i) {
        *(p_base_set++) = new_card_stack(*(p_card_counts++));
    }

    /* Check for NULL pointers */
    for (i = 0, p_base_set = base_set; i < BASE_COUNT; ++i) {
        if (*(p_base_set++) == NULL) { return NULL; }
    }

    int witch_instr[]           = {PLUS_CARD, PLUS_CARD, EACH_OTHER_PLAYER_GAINS_CURSE};
    int cellar_instr[]          = {PLUS_ACTION};
    int chapel_instr[]          = {TRASH_UP_TO_FOUR_CARDS};
    int moat_instr[]            = {PLUS_CARD, PLUS_CARD};
    int harbinger_instr[]       = {PLUS_CARD, PLUS_ACTION};
    int merchant_instr[]        = {PLUS_CARD, PLUS_ACTION};
    int vassal_instr[]          = {PLUS_COIN, PLUS_COIN};
    int village_instr[]         = {PLUS_CARD, PLUS_ACTION, PLUS_ACTION};
    int workshop_instr[]        = {GAIN_CARD_COSTING_UP_TO_FOUR};
    int bureaucrat_instr[]      = {GAIN_SILVER_TO_DECK};
    int militia_instr[]         = {PLUS_COIN, PLUS_COIN};
    int moneylender_instr[]     = {TRASH_COPPER_FOR_PLUS_THREE};
    int poacher_instr[]         = {PLUS_CARD, PLUS_ACTION, PLUS_COIN, DISCARD_A_CARD_PER_EMPTY_SUPPLY_PILE};
    int remodel_instr[]         = {TRASH_CARD_AND_GAIN_ONE_COASTING_UP_TO_TWO_MORE};
    int smithy_instr[]          = {PLUS_CARD, PLUS_CARD, PLUS_CARD};
    int throne_room_instr[]     = {PLAY_ACTION_CARD_FROM_HAND_TWICE};
    int bandit_instr[]          = {GAIN_GOLD_TO_HAND};
    int council_room_instr[]    = {PLUS_CARD, PLUS_CARD, PLUS_CARD, PLUS_CARD, PLUS_BUY, EACH_OTHER_PLAYER_DRAWS_CARD};

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
