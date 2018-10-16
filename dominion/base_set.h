#ifndef BASE_SET_H_
#define BASE_SET_H_

#include <stdlib.h>
#include "card_stack.h"

#define VICTORY      1
#define TREASURE     2
#define ACTION       4
#define CURSE        8
#define REACTION     16
#define GARDEN       32

#define BASE_COUNT   33
#define SUPPLY_PILES 17

#define PLUS_CARD   1
#define PLUS_ACTION 2
#define PLUS_BUY    3
#define PLUS_COIN   4
#define EACH_OTHER_PLAYER_GAINS_A_CURSE 5
#define GAIN_A_CARD_COSTING_UP_TO_FOUR  6
#define GAIN_SILVER_TO_DECK 7
#define TRASH_COPPER_FOR_PLUS_THREE 8
#define DISCARD_A_CARD_PER_EMPTY_SUPPLY_PILE 9
#define TRASH_CARD_AND_GAIN_ONE_COASTING_UP_TO_TWO_MORE 10
#define PLAY_ACTION_CARD_FROM_HAND_TWICE 11
#define GAIN_A_GOLD 12
#define EACH_OTHER_PLAYER_DRAWS_A_CARD 13
#define TRASH_UP_TO_FOUR_CARDS 14

struct card_stack ** base_set();

#endif
