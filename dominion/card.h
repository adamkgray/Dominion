#ifndef CARD_H_
#define CARD_H_

#include <stdlib.h>

#define N_ELEMS(arr) (sizeof(arr) / sizeof(arr[0]))

struct card {
    int type;
    char * name;
    int cost;
    int value;
    int * instructions;
};

struct card * new_card(int type, char * name, int cost, int value, int * instructions);

#endif
