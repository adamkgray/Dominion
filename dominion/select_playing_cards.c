#include "select_playing_cards.h"
#include <stdio.h>

struct card_stack ** select_playing_cards(struct card_stack ** base_set) {
    struct card_stack ** reduced_base_set = (struct card_stack **)malloc(REDUCED_BASE_SET * sizeof(struct card_stack *));
    if (reduced_base_set == NULL) { return NULL; }
    int action_card_indeces[] = {
        7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
    }, n = N_ELEMS(action_card_indeces), i, j;
    randomize(action_card_indeces, n);
    for (i = 0; i < 7; ++i) { reduced_base_set[i] = base_set[i]; }
    for (j = 0; j < 10; ++j, ++i) { reduced_base_set[i] = base_set[action_card_indeces[j]]; }
    for (i = 0; i < SUPPLY_PILES; ++i) { base_set[i] = NULL; }
    free(base_set);
    return reduced_base_set;
}

void swap(int * a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize(int arr[], int n) {
    int i, j;
    srand(time(NULL));
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        swap(arr + i, arr + j);
    }
}
