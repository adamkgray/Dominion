#ifndef CARD_H_
#define CARD_H_

#include <stdlib.h>

struct card {
    int type;
    char * name;
    int cost;
    int value;
    int * instructions;
};

struct card * new_card(int type, char * name, int cost, int value, int * instructions);

#endif
