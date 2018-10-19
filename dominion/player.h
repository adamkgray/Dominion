#ifndef PLAYER_H_
#define PLAYER_H_

#include "cards.h"

struct player {
    char name[9];
    int victory_points;
    int actions;
    int buys;
    struct card_stack * deck;
    struct card_stack * hand;
    struct card_stack * discard;
    struct card_stack * play_area;
};

struct player * new_player(char * name);

#endif
