/* Push a card directly onto a card stack */

#ifndef PUSH_H_
#define PUSH_H_

#include <stdlib.h>
#include "card_stack.h"

int push(struct card *, struct card_stack *);
int add_cards(int n, int type, char * name, int cost, int value, int * instructions, struct card_stack * to);

#endif
