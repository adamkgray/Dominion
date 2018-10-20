#include "execute_instructions.h"

void execute_action_card_instructions(int32_t instructions, table * p_table) {
    /* Each instruction is an integer that can be represented by 5 bits (max 6 instructions per card, i.e. 30 bits )
     * To get the next instruction, we 'AND' the instruction integer with 31 (11111)
     * If it's 0 stop, otherwise execute it
     */
    if (instructions & 31) {
        execute_instruction(instructions & 31, p_table);
        /* Bitshift 5 to the right to get the next instruction */
        return execute_action_card_instructions(instructions >> 5, p_table);
    }
    return;
}


void execute_instruction(int8_t instruction, table * p_table) {
    player * p_player = p_table->players[p_table->turn];
    switch (instruction) {
        case PLUS_CARD:
            draw(p_player);
            break;
        case PLUS_ACTION:
            ++(p_player->actions);
            break;
        case PLUS_BUY:
            ++(p_player->buys);
            break;
        case PLUS_COIN:
            break;
        case EACH_OTHER_PLAYER_GAINS_CURSE:
            each_other_player_gains_curse(p_table);
            break;
        case EACH_OTHER_PLAYER_DRAWS_CARD:
            each_other_player_draws_card(p_table);
        case GAIN_SILVER_TO_DECK:
            gain_silver_to_deck(p_player, p_table);
            break;
        case GAIN_GOLD:
            gain_gold(p_player, p_table);
        default:
            break;
    }
    return;
}

void each_other_player_draws_card(table * p_table) {
    for (int8_t i = 0; i < p_table->player_count; ++i) {   /* For each player, */
        if (i != p_table->turn) {                   /* whose turn it is not ... */
            draw(p_table->players[i]);              /* ... draw a card */
        }
    }
}

int8_t gain_gold(player * p_player, table * p_table) {
    pop_and_push(p_player->discard, p_table->supply_piles[GOLD]);
    card ** golds = (card **)realloc(p_table->supply_piles[GOLD]->cards, p_table->supply_piles[GOLD]->card_count * sizeof(card *));
    if (golds == NULL) {
        return 0;
    } else {
        p_table->supply_piles[GOLD]->cards = golds;
        return 1;
    }
}

int8_t gain_silver_to_deck(player * p_player, table * p_table) {
    pop_and_push(p_player->deck, p_table->supply_piles[SILVER]);
    card ** silvers = (card **)realloc(p_table->supply_piles[SILVER]->cards, p_table->supply_piles[SILVER]->card_count * sizeof(card *));
    if (silvers == NULL) {
        return 0;
    } else {
        p_table->supply_piles[SILVER]->cards = silvers;
        return 1;
    }
}

/* TODO: In the case that there are 3 players, someone plays a witch,
 * and there is only one curse left, who should get it?
 */
void each_other_player_gains_curse(table * p_table) {
    for (int8_t i = 0; i < p_table->player_count; ++i) {                                       /* For each player, */
        if (i != p_table->turn) {                                                       /* whose turn it is not ... */
            pop_and_push(p_table->players[i]->discard, p_table->supply_piles[0]);       /* ... give them a curse (0) */
        }
    }
}
