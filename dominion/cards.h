#ifndef CARD_H_
#define CARD_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int8_t type;
    char * name;
    int8_t cost;
    int8_t value;
    int32_t instructions;
} card;

typedef struct {
    int8_t card_count;
    int8_t limit;
    card ** cards;
} card_stack;

card * new_card(int8_t type, char * name, int8_t cost, int8_t value, int32_t instructions);
card_stack * new_card_stack(int8_t limit);
card * pop_card(card_stack *);
card * pop_card_at(int8_t i, card_stack *);
int8_t push_card(card * p_card, card_stack * to);
int8_t add_cards(int8_t n, int8_t type, char * name, int8_t cost, int8_t value, int32_t instructions, card_stack * to);
int8_t pop_and_push(card_stack * p_to, card_stack * p_from);

#endif
