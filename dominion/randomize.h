#ifndef RANDOMIZE_H_
#define RANDOMIZE_H_

#include <time.h>
#include <stdlib.h>
#include "card.h"
#include "card_stack.h"


void swap_cards(struct card ** a, struct card ** b);
void randomize_cards(struct card ** arr, int n);

void swap_indeces(int * a, int * b);
void randomize_indeces(int arr[], int n);

#endif
