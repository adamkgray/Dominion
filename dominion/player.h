#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>
#include "cards.h"

typedef struct {
    char name[9];
    int8_t victory_points;
    int8_t actions;
    int8_t buys;
    card_stack * deck;
    card_stack * hand;
    card_stack * discard;
    card_stack * play_area;
} player ;

player * new_player(char * name);

#endif
