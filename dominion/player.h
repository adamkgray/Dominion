#ifndef PLAYER_H_
#define PLAYER_H_

#include "card_stack.h"

struct player {
    char * name;
    int victory_points;
    struct card_stack * deck;
    struct card_stack * hand;
    struct card_stack * discard;
};

struct player * new_player(char * name);

#endif
