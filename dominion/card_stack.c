#include "card_stack.h"

struct card_stack * new_card_stack(int limit) {
    struct card_stack * p_card_stack = (struct card_stack *)malloc(sizeof(struct card_stack));
    if (p_card_stack == NULL) {
        return NULL;                    /* Return NULL if not enough memory for new card stack */
    }
    struct card ** new_cards = (struct card **)malloc(limit * sizeof(struct card *));
    if (new_cards == NULL) {
        return NULL;                    /* Return NULL if not enough memory for new card list */
    }
    p_card_stack->limit = limit;        /* Limit is the same as size of cards allocated */
    p_card_stack->card_count = 0;       /* There are initaily no cards in the stack */
    p_card_stack->cards = new_cards;    /* Set pointer to array of cards */
    return p_card_stack;                /* Return pointer to new card stack */
}

struct card * pop_card(struct card_stack * p_card_stack) {
    if (p_card_stack->card_count == 0) { return NULL; }                     /* Return NULL if 0 cards in card stack */
    --(p_card_stack->card_count);                                           /* Decrement card count */
    struct card * p_card = p_card_stack->cards[p_card_stack->card_count];   /* Get pointer to top card */
    p_card_stack->cards[p_card_stack->card_count] = NULL;                   /* Set top card to NULL */
    return p_card;                                                          /* Return pointer to top card */
}

struct card * pop_card_at(int i, struct card_stack * p_card_stack) {
    if (p_card_stack->card_count == 0) { return NULL; }                     /* Return NULL if 0 cards in card stack */
    if (i > p_card_stack->card_count - 1) { return NULL; }                  /* Return NULL if i is out of index range */
    struct card * p_card = p_card_stack->cards[i];                          /* Get pointer to card at index i */
    int j;
    for (j = i + 1; j < p_card_stack->card_count; ++i, ++j) {               /* Shift all other cards back one index */
        p_card_stack->cards[i] = p_card_stack->cards[j];
    }
    --(p_card_stack->card_count);                                           /* Decrement card count */
    p_card_stack->cards[p_card_stack->card_count] = NULL;                   /* Set final card position to NULL */
    return p_card;                                                          /* Return pointer to card */
}

int push_card(struct card * p_card, struct card_stack * p_card_stack) {
    if (p_card_stack->card_count == p_card_stack->limit) {  /* Used to initialize a stack when there are no other stacks to take from */
        struct card ** new_cards;                           /* Reallocate memory if limit is reached */
        ++(p_card_stack->limit);                            /* Increment limit */
        new_cards = (struct card **)realloc(p_card_stack->cards, (p_card_stack->limit) * sizeof(struct card *));
        if (new_cards == NULL) {                            /* Return NULL if not enough memory */
            return 0;
        }
        p_card_stack->cards = new_cards;                    /* Otherwise set the reallocated pointer */
    }
    p_card_stack->cards[p_card_stack->card_count] = p_card; /* Add the new card to the stack */
    p_card_stack->card_count += 1;                          /* Increment card count */
    return 1;
}

int add_cards(int n, int type, char * name, int cost, int value, int * instructions, struct card_stack * to) {
    int i;                                                          /* Routine which creates a card and adds it to a stack n times */
    struct card * p_card;                                           /* Card pointer to be reused */
    for (i = 0; i < n; ++i) {
        p_card = new_card(type, name, cost, value, instructions);   /* Create the new card */
        if (p_card == NULL) { return 0; }                           /* Return 0 if not enough memory */
        if (!push_card(p_card, to)) { return 0; }                   /* Return zero if the stack could not accept the new card */
    }
    return 1;                                                       /* Return 1 for success */
}

int pop_and_push(struct card_stack * p_to, struct card_stack * p_from) {
    struct card * p_card = pop_card(p_from);    /* Pop card from p_from */
    if (p_card == NULL) { return 0; }           /* Return 0 if pop failed */
    return push_card(p_card, p_to);             /* Return 0 or 1 depending on result of push */
}
