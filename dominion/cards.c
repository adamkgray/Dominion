#include "cards.h"

card * new_card(int8_t type, char * name, int8_t cost, int32_t value) {
    card * p_card = (card *)malloc(sizeof(card));
    if (p_card == NULL) { return NULL; }        /* Return NULL if not enough memory */
    p_card->type = type;                        /* Type is a power of 2 */
    p_card->name = name;                        /* String representing the actual name of the card */
    p_card->cost = cost;                        /* Cost of the card */
    p_card->value = value;                      /* Value of the card, represent both VP and G (0 if Action) */
    return p_card;
}

card_stack * new_card_stack(int8_t limit) {
    card_stack * p_card_stack = (card_stack *)malloc(sizeof(card_stack));
    if (p_card_stack == NULL) {
        return NULL;                    /* Return NULL if not enough memory for new card stack */
    }
    card ** new_cards = (card **)malloc(limit * sizeof(card *));
    if (new_cards == NULL) {
        return NULL;                    /* Return NULL if not enough memory for new card list */
    }
    p_card_stack->limit = limit;        /* Limit is the same as size of cards allocated */
    p_card_stack->card_count = 0;       /* There are initaily no cards in the stack */
    p_card_stack->cards = new_cards;    /* Set pointer to array of cards */
    return p_card_stack;                /* Return pointer to new card stack */
}

card * pop_card(card_stack * p_card_stack) {
    if (p_card_stack->card_count == 0) { return NULL; }                     /* Return NULL if 0 cards in card stack */
    --(p_card_stack->card_count);                                           /* Decrement card count */
    card * p_card = p_card_stack->cards[p_card_stack->card_count];          /* Get pointer to top card */
    p_card_stack->cards[p_card_stack->card_count] = NULL;                   /* Set top card to NULL */
    return p_card;                                                          /* Return pointer to top card */
}

card * pop_card_at(int8_t i, card_stack * p_card_stack) {
    if (p_card_stack->card_count == 0) { return NULL; }              /* Return NULL if 0 cards in card stack */
    if (i > p_card_stack->card_count - 1) { return NULL; }           /* Return NULL if i is out of index range */
    card * p_card = p_card_stack->cards[i];                          /* Get pointer to card at index i */
    for (int8_t j = i + 1; j < p_card_stack->card_count; ++i, ++j) { /* Shift all other cards back one index */
        p_card_stack->cards[i] = p_card_stack->cards[j];
    }
    --(p_card_stack->card_count);                                     /* Decrement card count */
    p_card_stack->cards[p_card_stack->card_count] = NULL;             /* Set final card position to NULL */
    return p_card;                                                    /* Return pointer to card */
}

int8_t push_card(card * p_card, card_stack * p_card_stack) {
    if (p_card_stack->card_count == p_card_stack->limit) {
        card ** new_cards;         /* Reallocate memory if limit is reached */
        ++(p_card_stack->limit);   /* Increment limit */
        new_cards = (card **)realloc(p_card_stack->cards, (p_card_stack->limit) * sizeof(card *));
        if (new_cards == NULL) {   /* Return NULL if not enough memory */
            return 0;
        }
        p_card_stack->cards = new_cards;                    /* Otherwise set the reallocated pointer */
    }
    p_card_stack->cards[p_card_stack->card_count] = p_card; /* Add the new card to the stack */
    p_card_stack->card_count += 1;                          /* Increment card count */
    return 1;
}

int8_t add_cards(int8_t n, int8_t type, char * name, int8_t cost, int32_t value, card_stack * to) {
    int8_t i;                                       /* Routine which creates a card and adds it to a stack n times */
    card * p_card;                                  /* Card pointer to be reused */
    for (i = 0; i < n; ++i) {
        p_card = new_card(type, name, cost, value); /* Create the new card */
        if (p_card == NULL) { return 0; }           /* Return 0 if not enough memory */
        if (!push_card(p_card, to)) { return 0; }   /* Return zero if the stack could not accept the new card */
    }
    return 1;                                       /* Return 1 for success */
}

int8_t pop_and_push(card_stack * p_to, card_stack * p_from) {
    card * p_card = pop_card(p_from);  /* Pop card from p_from */
    if (p_card == NULL) { return 0; }  /* Return 0 if pop failed */
    return push_card(p_card, p_to);    /* Return 0 or 1 depending on result of push */
}
