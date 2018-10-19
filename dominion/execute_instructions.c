#include "execute_instructions.h"

void execute_action_card_instructions(card * p_action_card, table * p_table) {
    int8_t * instructions, instruction_count;
    instructions = p_action_card->instructions;
    instruction_count = sizeof(instructions) / sizeof(int8_t);

    for (int8_t i = 0; i < instruction_count; ++i) {
        execute_instruction(instructions[i], p_table);
    }
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
        case GAIN_GOLD_TO_HAND:
            gain_gold_to_hand(p_player, p_table);
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

void gain_gold_to_hand(player * p_player, table * p_table) {
    pop_and_push(p_player->hand, p_table->supply_piles[GOLD]);
}

void gain_silver_to_deck(player * p_player, table * p_table) {
    pop_and_push(p_player->deck, p_table->supply_piles[SILVER]);
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
