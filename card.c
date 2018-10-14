#include "card.h"
#include <stdio.h>

struct card * new_card(int type, char * name, int cost, int value, int * instructions) {
    struct card * p_card = (struct card *)malloc(sizeof(struct card));
    if (p_card == NULL) { return NULL; }        /* Return NULL if not enough memory */
    p_card->type = type;                        /* Type is a power of 2 */
    p_card->name = name;                        /* String representing the actual name of the card */
    p_card->cost = cost;                        /* Cost of the card */
    p_card->value = value;                      /* Value of the card, represent both VP and G (0 if Action) */
    p_card->instructions = instructions;        /* An array of integers representing the directions of an action card */
    return p_card;
}
