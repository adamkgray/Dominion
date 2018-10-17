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

struct card_stack {
    int card_count;         /* Number of cards currently in the stack */
    int limit;              /* Max number of cards that have been in this stack at one time */
    struct card ** cards;   /* Array of cards */
};

struct card * new_card(int type, char * name, int cost, int value, int * instructions);
struct card_stack * new_card_stack(int limit);
struct card * pop_card(struct card_stack *);
struct card * pop_card_at(int i, struct card_stack *);
int push_card(struct card * p_card, struct card_stack * to);
int add_cards(int n, int type, char * name, int cost, int value, int * instructions, struct card_stack * to);
int pop_and_push(struct card_stack * p_to, struct card_stack * p_from);

#endif
