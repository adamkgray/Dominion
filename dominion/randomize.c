#include "randomize.h"

void swap_cards(card ** a, card ** b) {
    card * temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void randomize_cards(card * arr[], int8_t n) {
    static uint8_t seed_offset = 1;
    uint32_t j;
    srand(time(NULL));
    for (int8_t i = n - 1; i > 0; i--) {
        j = (rand() + (seed_offset++)) % (i + 1);
        swap_cards(arr + i, arr + j);
    }
}

void swap_indeces(int8_t * a, int8_t * b) {
    int8_t temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void randomize_indeces(int8_t arr[], int8_t n) {
    static uint8_t seed_offset = 1;
    uint32_t j;
    srand(time(NULL));
    for (int8_t i = n - 1; i > 0; i--) {
        j = (rand() + (seed_offset++)) % (i + 1);
        swap_indeces(arr + i, arr + j);
    }
}
