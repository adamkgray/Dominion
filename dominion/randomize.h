#ifndef RANDOMIZE_H_
#define RANDOMIZE_H_

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "cards.h"


void swap_cards(card ** a, card ** b);
void randomize_cards(card ** arr, int8_t n);

void swap_indeces(int8_t * a, int8_t * b);
void randomize_indeces(int8_t arr[], int8_t n);

#endif
