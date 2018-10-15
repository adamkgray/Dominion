#include "randomize.h"

void swap_cards(struct card ** a, struct card ** b) {
    struct card * temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void randomize_cards(struct card * arr[], int n) {
    static int seed_offset = 1;
    int i, j;
    srand(time(NULL));
    for (i = n - 1; i > 0; i--) {
        j = (rand() + (seed_offset++)) % (i + 1);
        swap_cards(arr + i, arr + j);
    }
}

void swap_indeces(int * a, int * b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void randomize_indeces(int arr[], int n) {
    int i, j;
    srand(time(NULL));
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        swap_indeces(arr + i, arr + j);
    }
}
