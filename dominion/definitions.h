#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/* Card types */
#define VICTORY      1
#define TREASURE     2
#define ACTION       4
#define CURSE        8
#define REACTION     16
#define GARDEN       32

/* Number of cards */
#define BASE_COUNT   33
#define SUPPLY_PILES 17

/* Permanent indeces of base cards */
#define ESTATE 1
#define PROVINCE 3
#define COPPER 4
#define SILVER 5
#define GOLD 6

/* Action instructions */
#define PLUS_CARD   1                                       /* [x] */
#define PLUS_ACTION 2                                       /* [x] */
#define PLUS_BUY    3                                       /* [x] */
#define PLUS_COIN   4                                       /* [ ] */
#define EACH_OTHER_PLAYER_GAINS_CURSE 5                     /* [x] */
#define GAIN_CARD_COSTING_UP_TO_FOUR  6                     /* [ ] */
#define GAIN_SILVER_TO_DECK 7                               /* [x] */
#define TRASH_COPPER_FOR_PLUS_THREE 8                       /* [ ] */
#define DISCARD_A_CARD_PER_EMPTY_SUPPLY_PILE 9              /* [ ] */
#define TRASH_CARD_AND_GAIN_ONE_COASTING_UP_TO_TWO_MORE 10  /* [ ] */
#define PLAY_ACTION_CARD_FROM_HAND_TWICE 11                 /* [ ] */
#define GAIN_GOLD_TO_HAND 12                                /* [x] */
#define EACH_OTHER_PLAYER_DRAWS_CARD 13                     /* [x] */
#define TRASH_UP_TO_FOUR_CARDS 14                           /* [ ] */

/* Interface color pairs */
#define BLUE_ON_WHITE 1

#endif
