#include "action_phase.h"

void action_phase(struct table * p_table){
    struct player * p_player = p_table->players[p_table->turn];
    if (p_player->actions == 0) { return; }    /* If player has no more actions, return */

    /* TODO: UI */
    /* Give player option to end actions */

    /* TODO: UI */
    /* Player moves an action card to play area */

    /* decrement actions */
    --(p_player->actions);

    /* call self recursively */
    return action_phase(p_table);
}

void execute_action_card_instructions(struct card * p_action_card, struct table * p_table) {
    int i, * instructions, instruction_count;
    instructions = p_action_card->instructions;
    instruction_count = sizeof(instructions) / sizeof(int);

    for (i = 0; i < instruction_count; ++i) {
        execute_instruction(instructions[i], p_table);
    }
}

void execute_instruction(int instruction, struct table * p_table) {
    struct player * p_player;
    p_player = p_table->players[p_table->turn];
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
        default:
            break;
    }
    return;
}

void forfeit_actions(struct player * p_player) {
    p_player->actions = 0;
    return;
}
