#ifndef SELECT_PLAYING_CARDS_H_
#define SELECT_PLAYING_CARDS_H_

#include "base_set.h"
#include <stdlib.h>
#include <time.h>

#define REDUCED_BASE_SET 17
#define N_ELEMS(arr) (sizeof(arr) / sizeof(arr[0]))

struct card_stack ** select_playing_cards(struct card_stack ** base_set);
void swap(int * a, int * b);
void randomize(int arr[], int n);

#endif
